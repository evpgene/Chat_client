#include "Message.h"
#include "User.h"
#include <iostream>
#include <string>
#include <sstream>
#include "ReceivedData.h"
#include "Keywords.h"

//using keyword_t = const std::string;
using User_t = std::shared_ptr<User>;  // указатель на юзера
using Message_t = std::shared_ptr<Message>;  // указатель на чат

class Client
{
private:

public:
    Client();
    ~Client();
    const Keywords key;

    void main(void);
    
    User_t inputUser();
    Message_t inputMessage(const User_t user);
    const std::string getLogonString(const User_t user);
    const std::string getLogoutString();
    const std::string getExitString();
    const std::string getMessageString(const Message_t message);
    const std::string getRegistrationString(const User_t user);
    const std::string getCompanionString(const std::string& companion);


    // to server
    const std::string getGetUsernamesString();
    const std::string getContinueUsernamesString();
    const std::string getGetMessagesString();
    const std::string getContinueMessagesString();

    ReceivedData interpretString(const std::string& str);

    void run(void);

    // void logout();
    // void sendUser();
    // void sendMessage();
    // void receivMessage();
    // keywords


    



};


