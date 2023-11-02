#include "Client.h"

#ifdef __linux__
    #include "TCP_client.h"
#elif _WIN32
    #include "TCP_client_w.h"
#endif

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
#ifdef __linux__
  ctime_r(&now, dt);
#elif _WIN32
  ctime_s(dt, sizeof(dt), &now);
#endif
  
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

void Client::run(void)
{
    bool firstcycle{ true };
    bool usernames_package{ false };
    bool messages_package{ false };

    User_t user;
    std::string cmd_input;
    int cmd{ 0 };

    TCP_client tcp_client;
    tcp_client.configureConnection();
    tcp_client.openConnection();

    std::vector<std::string> usernames;
    std::vector<std::string> messages;

    std::string string_to_send{ "Привет от клиента!" };
    std::string string_for_receive;

    while (true) {
        // (начало цикла)
        if (!firstcycle) {
            do {
                tcp_client.send_data(string_to_send);
                tcp_client.receive_data(string_for_receive);

                ReceivedData receivedData(interpretString(string_for_receive));
                switch (receivedData._type) {
                case ANY:
                    std::cout << string_for_receive << std::endl;
                    // тут мэйнменю
                    break;

                case USERNAMES:
                    if (!usernames_package) {
                        usernames.clear();
                    };
                    usernames.emplace_back(receivedData._str_view);
                    string_to_send = getContinueUsernamesString();
                    usernames_package = true;

                    break;

                case USERNAMES_END: {
                    usernames_package = false;
                    int numb{ 0 };
                    for (auto username : usernames) {
                        std::cout << ++numb << ": " << username << std::endl;
                    }

                } break;

                case MESSAGES:
                    //std::cout << "messages step " << std::endl; // раскоментировать для диагностики
                    messages.emplace_back(receivedData._str_view);
                    //std::cout << "one message emplase " << std::endl; // раскоментировать для диагностики
                    string_to_send = getContinueMessagesString();
                    messages_package = true;
                    break;

                case MESSAGES_END:
                    //std::cout << "messages end step " << std::endl; // раскоментировать для диагностики
                    for (auto message : messages) {
                        std::cout << message << std::endl;
                    }
                    messages.clear();
                    messages_package = false;
                    break;

                default:
                    string_to_send = "Неизвестная команда";  // что это??
                    break;
                }
            } while (usernames_package || messages_package);
        }
        firstcycle = false;
        std::cout << "Введите комманду (0 - помощ)" << std::endl;
        std::cin >> cmd_input;

        // проверяем корректность ввода
        try {
            cmd = std::stoi(cmd_input);
        }
        catch (exception& except) {
            cout << endl << except.what() << endl;
            cmd = 0;
        }

        try  // обработка исключений
        {
            switch (cmd) {
            case 0:
                std::cout << "0 - помощь" << std::endl;
                std::cout << "1 - вывести данные текущего пользователя" << std::endl;
                std::cout << "2 - авторизоваться" << std::endl;
                std::cout << "3 - написать сообщение" << std::endl;
                std::cout << "4 - регистрация пользователя" << std::endl;
                std::cout << "5 - вывести имена пользователей" << std::endl;
                std::cout << "6 - выбрать пользователя для чата" << std::endl;
                std::cout << "7 - прочитать сообщения" << std::endl;
                std::cout << "8 - выйти из учётной записи" << std::endl;
                std::cout << "9 - выйти из программы" << std::endl;
                std::cout << "Имя пользователя должно состоять из одного слова"
                    << std::endl;
                break;

            case 1:  // выводим  данные текущего пользователя
                if (user) {
                    //std::cout << "Пользователь: " << user->getLogin() << std::endl;
                    string_to_send = "Пользователь: " + user->getLogin();
                }
                else {
                    //std::cout << "Вы не ввели данные пользователя" << std::endl;
                    string_to_send = "Вы не ввели данные пользователя";
                }
                break;
            case 2:  // User logon
                user = inputUser();
                if (user) {
                    string_to_send = getLogonString(user);
                }
                else {
                    std::cout << "Вы не ввели данные пользователя" << std::endl;
                }
                break;
            case 3:  // Написать пользователю
                if (user) {
                    string_to_send = getMessageString(inputMessage(user));
                }
                else {
                    //std::cout << "Вы не ввели данные пользователя" << std::endl;
                    string_to_send = "Вы не ввели данные пользователя";
                }
                break;
            case 4:  // User registration
                user = inputUser();
                if (user) {
                    string_to_send = getRegistrationString(user);
                }
                else {
                    //std::cout << "Вы не ввели данные пользователя" << std::endl;
                    string_to_send = "Вы не ввели данные пользователя";
                }
                break;

            case 5:  // Вывод имён зфрегистрированных пользователей
                string_to_send = getGetUsernamesString();
                break;

            case 6: {
                if (!usernames.size()) {
                    //std::cout << "Сначала запросите имена пользователей" << std::endl;
                    string_to_send = "Сначала запросите имена пользователей";
                    break;
                }
                std::string id_input;
                std::cout << "Выберите пользователя для чата (введите номер) от 1 до "
                    << usernames.size() << std::endl;
                std::cin >> id_input;
                // проверяем корректность ввода - лучше бы тут конечно использовать
                // функцию ограничения диапапзона вместо исключения, но я об этом знаю
                string_to_send = "Видимо ввод был неудачный";
                try {
                    string_to_send = getCompanionString(
                        usernames.at(std::stoi(id_input) - 1));
                }
                catch (const std::exception& e) {
                    cout << endl << e.what() << endl;
                }
                // далее раскоментировать для диагностики, если потребуется
                // std::cout << "string to send at usernames end step" << string_to_send
                //           << std::endl;
            } break;

            case 7:
                string_to_send = getGetMessagesString();
                break;

            case 8:  // logoff
                string_to_send = getLogoutString();
                user = nullptr;
                break;
            case 9:  // Выход из программы
                string_to_send = getExitString();
                return;
                break;
            default:
                std::cout << "Нет такой команды: " << cmd << std::endl;
                break;
            }
        }
        catch (exception& except) {
            cout << endl << except.what() << endl;
        }
    }
}
