#include "ProjectAnalyzer.h"

#include "Wexception.h"

ProjectAnalyzer::ProjectAnalyzer()
	: m_project_path()
	, m_files_holder()
	, m_full_statistic()
	, m_processed_files(0)
	, m_threads(std::thread::hardware_concurrency())
{}

ProjectAnalyzer::ProjectAnalyzer(const std::wstring& project_path, const std::initializer_list<std::wstring>& extensions_for_search)
	: m_project_path(project_path)
	, m_files_holder(project_path, extensions_for_search)
	, m_full_statistic()
	, m_processed_files(0)
	, m_threads(std::thread::hardware_concurrency())
{}

void ProjectAnalyzer::AnalyzeProject()
{
	if (!std::filesystem::exists(m_project_path))
		throw Wexception((L"Folder '" + m_project_path + L"' doesn't exist").c_str());

	ResetAmounts();

	m_files_holder.StartSearching();

	if (!m_threads.empty())
	{
		for (const std::wstring& file_path : m_files_holder.get_special_files())
			m_threads.push_back(std::thread{ &ProjectAnalyzer::ProcessFile, this, std::cref(file_path) });

		for (std::thread& thread : m_threads)
			if (thread.joinable())
				thread.join();
	}
	else
	{
		for (const std::wstring& file_path : m_files_holder.get_special_files())
			ProcessFile(file_path);
	}
}

void ProjectAnalyzer::ResetAmounts()
{
	m_full_statistic.blank_lines = 0;
	m_full_statistic.comment_lines = 0;
	m_full_statistic.code_lines = 0;
	m_full_statistic.physical_lines = 0;
	m_processed_files = 0;
}

int ProjectAnalyzer::get_processed_files() const
{
	return m_processed_files;
}

int ProjectAnalyzer::get_blank_lines() const
{
	return m_full_statistic.blank_lines;
}

int ProjectAnalyzer::get_comment_lines() const
{
	return m_full_statistic.comment_lines;
}

int ProjectAnalyzer::get_code_lines() const
{
	return m_full_statistic.code_lines;
}

int ProjectAnalyzer::get_physical_lines() const
{
	return m_full_statistic.physical_lines;
}

const std::wstring& ProjectAnalyzer::get_project_path() const
{
	return m_project_path;
}

void ProjectAnalyzer::set_project_path(const std::wstring& project_path)
{
	ResetAmounts();

	m_project_path = project_path;

	m_files_holder.set_root_directory(project_path);
}

void ProjectAnalyzer::set_extensions_for_search(const std::initializer_list<std::wstring>& extensions_for_search)
{
	m_files_holder.set_extensions_for_search(extensions_for_search);
}

void ProjectAnalyzer::ProcessFile(const std::wstring& file_path)
{
	FileReader fileReader{ file_path };
	fileReader.StartReading();

	CodeAnalyzer codeAnalyzer{ fileReader.get_read_information() };
	codeAnalyzer.StartFullAnalysis();

	m_files_statistics.push_back(FileStatistic{
		codeAnalyzer.get_blank_lines(),
		codeAnalyzer.get_comment_lines(),
		codeAnalyzer.get_code_lines(),
		codeAnalyzer.get_physical_lines()
		});

	m_full_statistic.blank_lines += codeAnalyzer.get_blank_lines();
	m_full_statistic.comment_lines += codeAnalyzer.get_comment_lines();
	m_full_statistic.code_lines += codeAnalyzer.get_code_lines();
	m_full_statistic.physical_lines += codeAnalyzer.get_physical_lines();

	m_processed_files++;
}

std::wostream& operator<<(std::wostream& out, const ProjectAnalyzer& analyzer)
{
	out << "----------------------------------------------\n";
	out << L"Full Statistic:\n";
	out << L"Comment Lines    = " << analyzer.get_comment_lines() << std::endl;
	out << L"Blank Lines      = " << analyzer.get_blank_lines() << std::endl;
	out << L"Code Lines       = " << analyzer.get_code_lines() << std::endl;
	out << L"Physical Lines   = " << analyzer.get_physical_lines() << std::endl;
	out << L"Proccessed Files = " << analyzer.get_processed_files() << std::endl;
	out << "----------------------------------------------\n\n";

	for (size_t i = 0; i < analyzer.m_files_holder.get_special_files().size(); i++)
	{
		out << L"File '" << analyzer.m_files_holder.get_special_files()[i] << "':\n";
		out << L"Comment Lines    = " << analyzer.m_files_statistics[i].comment_lines << std::endl;
		out << L"Blank Lines      = " << analyzer.m_files_statistics[i].blank_lines << std::endl;
		out << L"Code Lines       = " << analyzer.m_files_statistics[i].code_lines << std::endl;
		out << L"Physical Lines   = " << analyzer.m_files_statistics[i].physical_lines << "\n\n";
	}

	return out;
}