#pragma once

#include <string>

class CodeAnalyzer
{
public:
	CodeAnalyzer();
	CodeAnalyzer(const std::wstring& text);
	void StartFullAnalysis();
	void CountBlankLines();
	void CountCommentLines();
	void CountCodeLines();
	void CountPhysicalLines();
	void Reset();
	void set_text(const std::wstring& text);
	int get_blank_lines() const;
	int get_comment_lines() const;
	int get_code_lines() const;
	int get_physical_lines() const;
	const std::wstring& get_text() const;

private:
	std::wstring m_text;
	int m_blank_lines;
	int m_comment_lines;
	int m_code_lines;
	int m_physical_lines;
};