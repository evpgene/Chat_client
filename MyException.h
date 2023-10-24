#pragma once
#include <exception>
#include <iostream>
#include <string>
class MyException : public std::exception
{
private:
	std::string reason;
public:
	MyException(const char* why) : reason(why) {}
	virtual const char* what() const noexcept
	{
		return reason.c_str();
	}
};

