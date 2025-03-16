//---------------------------------------------------------------------------------------------------------------------
// TCP socket server for the rocket simulation
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

#include "rocket.hpp"

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <windows.h>

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE (STATIC) FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

static SOCKET ConnectSocket()
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

    return socket_connected;
}

//---------------------------------------------------------------------------------------------------------------------
// EXECUTABLE MAIN FUNCTION DEFINITION
//---------------------------------------------------------------------------------------------------------------------

int main()
{
    // Rocket simulation parameters
    constexpr double time_step_s    = 1.0e-3;
    constexpr double mass_rocket_kg = 1000.0;

    // Create the instance of the rocket
    Rocket_t rocket{
        {.time_step_s    = time_step_s,
         .mass_rocket_kg = mass_rocket_kg}
    };

    const SOCKET socket = ConnectSocket();

    while (true)
    {
        XyVector_t power_command_kW;
        const int count_recv_bytes = recv(socket,
                                          reinterpret_cast<char*>(&power_command_kW),
                                          sizeof(XyVector_t),
                                          0);

        if (count_recv_bytes > 0)
        {
            std::cout << "Power x-axis: " << power_command_kW.x_axis << " kW" << std::endl;
            std::cout << "Power y-axis: " << power_command_kW.y_axis << " kW" << std::endl;

            rocket.UpdateState(power_command_kW);
            const XyVector_t position_m = {12.3, 34.5}; //rocket.GetPosition_m();

            send(socket,
                reinterpret_cast<const char*>(&position_m),
                sizeof(XyVector_t),
                0);
        }
        else if (count_recv_bytes == 0)
        {
            std::cout << "Connection closed!" << std::endl;
            break;
        }
    }

    return 0;
}
