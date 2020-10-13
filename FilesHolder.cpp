#include "FilesHolder.h"

#include <algorithm>

#include "Wexception.h"

FilesHolder::FilesHolder()
	: m_root_directory()
	, m_special_files()
	, m_extensions_for_search()
{}

FilesHolder::FilesHolder(const std::wstring& root_directory, const std::initializer_list<std::wstring>& extensions_for_search)
	: m_root_directory(root_directory)
	, m_special_files()
	, m_extensions_for_search(extensions_for_search)
{}

void FilesHolder::StartSearching()
{
	if (!std::filesystem::exists(m_root_directory))
		throw Wexception((L"Folder '" + m_root_directory + L"' doesn't exist").c_str());

	for (const auto& entry : std::filesystem::recursive_directory_iterator(m_root_directory))
	{
		if (!entry.is_directory())
		{
			std::filesystem::path fileExtension = entry.path().extension();

			if (std::find(m_extensions_for_search.cbegin(), m_extensions_for_search.cend(), fileExtension) != m_extensions_for_search.cend())
				m_special_files.push_back(entry.path().wstring());
		}
	}
}

void FilesHolder::set_root_directory(const std::wstring& root_directory)
{
	m_special_files.clear();

	m_root_directory = root_directory;
}

void FilesHolder::set_extensions_for_search(const std::initializer_list<std::wstring>& extensions_for_search)
{
	m_special_files.clear();

	m_extensions_for_search = extensions_for_search;
}

const std::wstring& FilesHolder::get_root_directory() const
{
	return m_root_directory;
}

const std::vector<std::wstring>& FilesHolder::get_special_files() const
{
	return m_special_files;
}

const std::vector<std::wstring>& FilesHolder::get_extensions_for_search() const
{
	return m_extensions_for_search;
}