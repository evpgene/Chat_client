#ifdef __linux__

#include "TCP_client.h"

TCP_client::TCP_client(/* args */)
{
}

TCP_client::~TCP_client()
{
}

void TCP_client::configureConnection()
{
    // Создадим сокет
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1)
    {
        std::cout << "Creation of Socket failed!" << std::endl;
        exit(1);
    }

    // Установим адрес сервера
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Зададим номер порта
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
};

void TCP_client::openConnection()
{
    connection = connect(socket_file_descriptor, (struct sockaddr *)&serveraddress, sizeof(serveraddress));
    if (connection == -1)
    {
        std::cout << "Connection with the server failed.!" << std::endl;
        exit(1);
    }
}

bool TCP_client::send(const std::string& str)
{
    bzero(message, sizeof(message));
    // std::cout << "Enter the message you want to send to the server: " << std::endl;
    // std::cin >> message;
    strncpy(message, str.c_str(), sizeof(message)/* sizeof(str) > sizeof(message) ? sizeof(message) : sizeof(str) */);
    // if ((strncmp(message, "end", 3)) == 0)
    // {
    //     write(socket_file_descriptor, message, sizeof(message));
    //     std::cout << "Client Exit." << std::endl;
    //     // break;
    // }


    ssize_t bytes = write(socket_file_descriptor, message, sizeof(message));
    // Если передали >= 0  байт, значит пересылка прошла успешно
    if (bytes >= 0)
    {
        //тут далее раскоментировать для диагностики, если потребуется
        // //std::cout << "Data send to the server successfully.!" << std::endl;
        // std::cout << "sent to server message start " << std::endl;
        // std::cout << message << std::endl;
        // std::cout << " sent to server message end" << std::endl;
        return true;
    }
    return false;
}
bool TCP_client::receive(std::string& str)
{
    // Ждем ответа от сервера
    bool retval = read(socket_file_descriptor, message, sizeof(message));
    //тут далее раскоментировать для диагностики, если потребуется
    // //std::cout << "Data received from server: " << message << std::endl;
    // std::cout << "received from server message start " << std::endl;
    // std::cout << message << std::endl;
    // std::cout << " received from server message end" << std::endl;
    str = std::string(message);
    return retval;
}

void TCP_client::closeConnection()
{
    // закрываем сокет, завершаем соединение
    close(socket_file_descriptor);
}


#endif
