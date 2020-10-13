#pragma once

#include <string>	

class FileReader
{
public:
	FileReader();
	FileReader(const std::wstring& file_path);
	void StartReading();
	void Reset();
	void set_file_path(const std::wstring& file_path);
	const std::wstring& get_read_information() const;
	const std::wstring& get_file_path() const;

private:
	std::wstring m_file_path;
	std::wstring m_read_information;
};