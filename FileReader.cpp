#include "FileReader.h"

#include <fstream>

#include "Wexception.h"

FileReader::FileReader()
	: m_file_path()
	, m_read_information()
{}

FileReader::FileReader(const std::wstring& file_path)
	: m_file_path(file_path)
	, m_read_information()
{}

void FileReader::StartReading()
{
	if (m_file_path.empty())
		throw Wexception{ L"File path is incorrect" };

	std::ifstream input_file_stream{ m_file_path };

	if (!input_file_stream)
		throw Wexception{ (L"File '" + m_file_path + L"' doesn't exist").c_str() };

	int ch = input_file_stream.get();
	while (ch != EOF)
	{
		m_read_information.push_back(ch);
		ch = input_file_stream.get();
	}

	input_file_stream.close();
}

void FileReader::Reset()
{
	m_file_path.clear();
	m_read_information.clear();
}

void FileReader::set_file_path(const std::wstring& file_path)
{
	Reset();

	m_file_path = file_path;
}

const std::wstring& FileReader::get_read_information() const
{
	return m_read_information;
}

const std::wstring& FileReader::get_file_path() const
{
	return m_file_path;
}