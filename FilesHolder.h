#pragma once

#include <vector>
#include <string>
#include <filesystem>

class FilesHolder
{
public:
	FilesHolder();
	FilesHolder(const std::wstring& root_directory, const std::initializer_list<std::wstring>& extensions_for_search);
	void StartSearching();
	void set_root_directory(const std::wstring& root_directory);
	void set_extensions_for_search(const std::initializer_list<std::wstring>& extensions_for_search);
	const std::wstring& get_root_directory() const;
	const std::vector<std::wstring>& get_special_files() const;
	const std::vector<std::wstring>& get_extensions_for_search() const;

private:
	std::vector<std::wstring> m_special_files;
	std::wstring m_root_directory;
	std::vector<std::wstring> m_extensions_for_search;
};