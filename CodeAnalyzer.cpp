#include "CodeAnalyzer.h"

#include <sstream>
#include <cwctype>

CodeAnalyzer::CodeAnalyzer()
	: m_text()
	, m_blank_lines(0)
	, m_comment_lines(0)
	, m_code_lines(0)
	, m_physical_lines(0)
{}

CodeAnalyzer::CodeAnalyzer(const std::wstring& text)
	: m_text(text)
	, m_blank_lines(0)
	, m_comment_lines(0)
	, m_code_lines(0)
	, m_physical_lines(0)
{}

void CodeAnalyzer::StartFullAnalysis()
{
	CountPhysicalLines();
	CountCommentLines();
	CountBlankLines();
	CountCodeLines();
}

void CodeAnalyzer::CountBlankLines()
{
	// empty line definition:
	// empty line is a line with at least one whitespace character and it has
	// only whitespace characters.

	std::wstring line;

	int ch = EOF;
	for (size_t i = 0; i < m_text.size(); i++)
	{
		// read next line:
		ch = m_text[i];
		while (ch != '\n' && ch != EOF && i < m_text.size())
		{
			line.push_back(ch);

			if (++i < m_text.size())
				ch = m_text[i];
		}

		// check if the is empty:
		bool is_empty_line = true;
		for (size_t j = 0; j < line.size(); j++)
		{
			if (!std::iswspace(line[j]))
			{
				is_empty_line = false;
				break;
			}
		}

		if (is_empty_line)
			m_blank_lines++;

		line.clear();
	}
}

void CodeAnalyzer::CountCommentLines()
{
	bool isRowCommentStarted = false;
	bool isBlockCommentStarted = false;
	bool isStringLiteralStarted = false;
	bool isCharLiteralStarted = false;
	int previousCharacter = EOF;

	for (size_t i = 0; i < m_text.size(); i++)
	{
		if (!isRowCommentStarted && !isBlockCommentStarted &&              // any comment is not started
			m_text[i] == '\"')                                             // and we found '\"'
		{
			isStringLiteralStarted = (isStringLiteralStarted ? false : true);
		}
		else if (previousCharacter == '/' && m_text[i] == '/' &&           // we found "//"
			!isRowCommentStarted && !isBlockCommentStarted &&              // and any comment is not started
			!isStringLiteralStarted && !isCharLiteralStarted)              // and any string/char literal is not started
		{
			isRowCommentStarted = true;
			m_comment_lines++;
		}
		else if (!isRowCommentStarted && !isBlockCommentStarted &&         // any comment is not started
			m_text[i] == '\'')                                             // and we found '\''
		{
			isCharLiteralStarted = (isCharLiteralStarted ? false : true);
		}
		else if (previousCharacter == '/' && m_text[i] == '*' &&           // we found "/*"
			!isRowCommentStarted && !isBlockCommentStarted &&              // and any comment is not started
			!isStringLiteralStarted && !isCharLiteralStarted)              // and any string/char literal is not started
		{
			isBlockCommentStarted = true;
			m_comment_lines++;
		}
		else if (isRowCommentStarted && m_text[i] == '\n')                 // row comment started and finished by '\n'
		{
			isRowCommentStarted = false;
		}
		else if (isBlockCommentStarted && previousCharacter == '\n')       // block comment started and we found '\n'
		{
			m_comment_lines++;
		}
		else if (isBlockCommentStarted &&                                  // row comment started   
			previousCharacter == '*' && m_text[i] == '/')                  // and finished by "*/"
		{
			isBlockCommentStarted = false;
		}

		previousCharacter = m_text[i];
	}
}

void CodeAnalyzer::CountCodeLines()
{
	bool isRowCommentStarted = false;
	bool isBlockCommentStarted = false;
	bool isStringLiteralStarted = false;
	bool isCharLiteralStarted = false;
	bool isCodeLineStarted = false;
	int previousCharacter = EOF;

	for (size_t i = 0; i < m_text.size(); i++)
	{
		if (!isRowCommentStarted && !isBlockCommentStarted &&              // any comment is not started
			m_text[i] == '\"')                                             // and we found '\"'
		{
			isStringLiteralStarted = (isStringLiteralStarted ? false : true);
		}
		else if (previousCharacter == '/' && m_text[i] == '/' &&           // we found "//"
			!isRowCommentStarted && !isBlockCommentStarted &&              // and any comment is not started
			!isStringLiteralStarted && !isCharLiteralStarted)              // and any string/char literal is not started
		{
			isRowCommentStarted = true;
		}
		else if (!isRowCommentStarted && !isBlockCommentStarted &&         // any comment is not started
			m_text[i] == '\'')                                             // and we found '\''
		{
			isCharLiteralStarted = (isCharLiteralStarted ? false : true);
		}
		else if (previousCharacter == '/' && m_text[i] == '*' &&           // we found "/*"
			!isRowCommentStarted && !isBlockCommentStarted &&              // and any comment is not started
			!isStringLiteralStarted && !isCharLiteralStarted)              // and any string/char literal is not started
		{
			isBlockCommentStarted = true;
		}
		else if (isRowCommentStarted && m_text[i] == '\n')                 // row comment started and finished by '\n'
		{
			isRowCommentStarted = false;
		}
		else if (isBlockCommentStarted &&                                  // row comment started   
			previousCharacter == '*' && m_text[i] == '/')                  // and finished by "*/"
		{
			isBlockCommentStarted = false;
		}
		else if (!isBlockCommentStarted && !isRowCommentStarted &&         // any comment is not started
				 !isCodeLineStarted &&                                     // and code is not started
			     m_text[i] != '\n' &&                                      // and we didn't find '\n'
			     (i == m_text.size() - 1 || i + 1 < m_text.size() &&       // and it's our last character or pre-last character
				 ((m_text[i] != '/' && m_text[i + 1] != '/') ||            // and it's not the beggining of line comment
				 (m_text[i] != '/' && m_text[i + 1] != '/*'))))            // or it's not the beggining of block comment
		{
			isCodeLineStarted = true;
			m_code_lines++;
		}
		else if (!isBlockCommentStarted && !isRowCommentStarted &&         // any comment is not started
			m_text[i] == '\n')                                             // and code line finished by '\n'
		{
			isCodeLineStarted = false;
		}

		previousCharacter = m_text[i];
	}
}

void CodeAnalyzer::CountPhysicalLines()
{
	int previousCharacter = EOF;

	for (size_t i = 0; i < m_text.size(); i++)
	{
		if (m_text[i] == '\n')
			m_physical_lines++;

		previousCharacter = m_text[i];
	}

	// After last line of code file might not have new-line character. In that case
	// algorithm above doesn't calculate the last line of code. That's why we need another
	// variable 'prev' to keep previous character and check it if that's our case.
	if (previousCharacter != '\n')
		m_physical_lines++;
}

void CodeAnalyzer::Reset()
{
	m_blank_lines = 0;
	m_comment_lines = 0;
	m_code_lines = 0;
	m_physical_lines = 0;
}

void CodeAnalyzer::set_text(const std::wstring& text)
{
	m_text = text;

	Reset();
}

int CodeAnalyzer::get_blank_lines() const
{
	return m_blank_lines;
}

int CodeAnalyzer::get_comment_lines() const
{
	return m_comment_lines;
}

int CodeAnalyzer::get_code_lines() const
{
	return m_code_lines;
}

int CodeAnalyzer::get_physical_lines() const
{
	return m_physical_lines;
}

const std::wstring& CodeAnalyzer::get_text() const
{
	return m_text;
}
