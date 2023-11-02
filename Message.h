#pragma once
#include <string>
//#include "SaveRestor.h"
class Message
{
public:
	Message();
	Message(const std::string &timeSend, const std::string &userName, const std::string &message);
	Message(std::string&& timeSend, std::string&& userName, std::string&& message);
	Message(const Message&);
	Message(Message&&);
	~Message();

	void printMessage() const;

	std::string getTimeSend() const;
	std::string getUserLogin() const;
	std::string getMessageText() const;

	// friend std::string SaveRestor::saveMessage(Message& message);

private:
	std::string _timeSend;
	std::string _userName;
	std::string _message;
};

