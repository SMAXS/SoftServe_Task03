#pragma once

#include <string>
#include <thread>
#include <vector>
#include <mutex>

#include "CodeAnalyzer.h"
#include "FileReader.h"
#include "FilesHolder.h"

class ProjectAnalyzer
{
private:
	struct FileStatistic
	{
		int blank_lines;
		int comment_lines;
		int code_lines;
		int physical_lines;
	};

public:
	ProjectAnalyzer();
	ProjectAnalyzer(const std::wstring& project_path, const std::initializer_list<std::wstring>& extensions_for_search);
	void AnalyzeProject();
	void ResetAmounts();
	int get_processed_files() const;
	int get_blank_lines() const;
	int get_comment_lines() const;
	int get_code_lines() const;
	int get_physical_lines() const;
	const std::wstring& get_project_path() const;
	void set_project_path(const std::wstring& project_path);
	void set_extensions_for_search(const std::initializer_list<std::wstring>& extensions_for_search);

private:	
	std::vector<std::thread> m_threads;
	std::wstring m_project_path;
	FilesHolder m_files_holder;
	std::vector<FileStatistic> m_files_statistics;
	FileStatistic m_full_statistic;
	int m_processed_files;

	void ProcessFile(const std::wstring& file_path);

	friend std::wostream& operator<<(std::wostream& out, const ProjectAnalyzer& analyzer);
};
