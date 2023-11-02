#include "Message.h"
#include <iostream>

Message::Message(){}

Message::Message(const std::string &timeSend, const std::string &userName, const std::string &message) : 
	_timeSend(timeSend),
	_userName(userName),
	_message(message) {
}

Message::Message(std::string &&timeSend, std::string &&userName, std::string &&message) : 
	_timeSend(std::move(timeSend)),
	_userName(std::move(userName)),
	_message(std::move(message)) {
}

Message::Message(const Message& other)
{
	if (this != &other)
	{
		_timeSend = other._timeSend;
		_userName = other._userName;
		_message = other._message;
	}
}

Message::Message(Message&& other)
{
	if (this != &other)
	{
		_timeSend = std::move(other._timeSend);
		_userName = std::move(other._userName);
		_message = std::move(other._message);
	}
}

Message::~Message()
{
}

std::string Message::getTimeSend() const
{
	return _timeSend;
}
std::string Message::getUserLogin() const
{
	return _userName;
}
std::string Message::getMessageText() const
{
	return _message;
}

void Message::printMessage() const
{
	std::cout << _timeSend << _userName << ": " << _message << std::endl;
}
