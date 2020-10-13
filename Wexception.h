#pragma once

#include <string>

class Wexception
{
public:
	explicit Wexception(const wchar_t* message)
		: m_message(message)
	{}

	virtual ~Wexception() noexcept
	{}

	virtual const wchar_t* what() const noexcept
	{
		return m_message.c_str();
	}

private:
	std::wstring m_message;
};