#include "Client.h"

#include "TCP_client.h"

Client::Client() {}

Client::~Client() {}

void Client::main(void) {


}

User_t Client::inputUser() {
  std::string login, password;
  std::cout << "Введите ваше логин" << std::endl;  // login
  std::cin >> login;
  std::cout << "Введите пароль: " << std::endl;
  std::cin >> password;
  return make_shared<User>(User(std::move(login), std::move(password)));
}

Message_t Client::inputMessage(const User_t user) {
  std::string message;
  std::cout << "Введите ваше сообщение: ";
  cin.ignore();
  std::getline(std::cin, message);
  time_t now = time(0);  // текущие дата/время основываясь на текущей системе
  char dt[26];
  ctime_r(&now, dt);
  dt[24] = ' ';  // убираем перенос строки
  return make_shared<Message>(Message(std::move(std::string(dt)),
                                      user->getLogin(), std::move(message)));
}

const std::string Client::getLogonString(const User_t user) {
  return key.itLogon + key.sep + key.log + key.sep + user->getLogin() +
         key.sep + key.pas + key.sep + user->getPass();
};



const std::string Client::getLogoutString() {
  return key.itLogout;
};

const std::string Client::getExitString() {
  return key.itExit;
};


const std::string Client::getMessageString(const Message_t message) {
  return key.itMessage + key.sep + key.timesend + key.sep +
         message->getTimeSend() + key.sep + key.name + key.sep +
         message->getUserLogin() + key.sep + key.mess + key.sep +
         message->getMessageText();
}

const std::string Client::getRegistrationString(const User_t user) {
  return key.itRegistration + key.sep + key.log + key.sep + user->getLogin() +
         key.sep + key.pas + key.sep + user->getPass();
}

const std::string Client::getGetUsernamesString() { return key.itGetUsernames  + key.sep; }

const std::string Client::getContinueUsernamesString() { return key.itContinueUsernames + key.sep; }

const std::string Client::getGetMessagesString() { return key.itGetMessages + key.sep; }

const std::string Client::getContinueMessagesString() { return key.itContinueMassages + key.sep; }

const std::string Client::getCompanionString(const std::string& companion) { return key.itCompName + key.sep + companion; }

ReceivedData Client::interpretString(const std::string& str) {
  std::string_view str_view{str};
  std::string_view first_word{str_view.substr(0, str_view.find(key.sep))};

  if (first_word == key.itUsernames) {
    str_view.remove_prefix(key.itUsernames.size() + key.sep.size());
    return ReceivedData(ReceivedType(USERNAMES), str_view);
  };

  if (first_word == key.itUsernamesEnd) {
    str_view.remove_prefix(key.itUsernamesEnd.size() + key.sep.size());
    return ReceivedData(ReceivedType(USERNAMES_END), str_view);
  };

  if (first_word == key.itMessages) {
    str_view.remove_prefix(key.itMessages.size() + key.sep.size());
    return ReceivedData(ReceivedType(MESSAGES), str_view);
  };

  if (first_word == key.itMessagesEnd) {
    str_view.remove_prefix(key.itMessagesEnd.size() + key.sep.size());
    return ReceivedData(ReceivedType(MESSAGES_END), str_view);
  };

  return ReceivedData(ReceivedType(ANY), str_view);  

}