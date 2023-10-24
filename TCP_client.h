
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

//using namespace std;

#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
#define PORT 7777           // Будем использовать этот номер порта

class TCP_client
{
private:
    int socket_file_descriptor, connection;
    struct sockaddr_in serveraddress, client;
    char message[MESSAGE_LENGTH];

public:
    TCP_client(/* args */);
    ~TCP_client();
    void configureConnection();
    void openConnection();
    void closeConnection();
    bool send(const std::string& str);
    bool receive(std::string& str);
};




