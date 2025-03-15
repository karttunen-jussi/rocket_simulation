//---------------------------------------------------------------------------------------------------------------------
// TCP socket server for the rocket simulation
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <windows.h>

//---------------------------------------------------------------------------------------------------------------------
// EXECUTABLE MAIN FUNCTION DEFINITION
//---------------------------------------------------------------------------------------------------------------------

int main()
{
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    const SOCKET socket_listen = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address;
    address.sin_family      = AF_INET;
    address.sin_port        = htons(1'234);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(socket_listen, reinterpret_cast<sockaddr*>(&address), sizeof(address));
    listen(socket_listen, 1);

    const SOCKET socket_connected = accept(socket_listen, nullptr, nullptr);

    while (true)
    {
        char buffer[48] = {};

        const int count_recv_bytes = recv(socket_connected, buffer, sizeof(buffer), 0);

        if (count_recv_bytes > 0)
        {
            std::cout << "Received message: " << buffer << std::endl;
        }
        else if (count_recv_bytes == 0)
        {
            std::cout << "Connection closed!" << std::endl;
            break;
        }
    }

    return 0;
}
