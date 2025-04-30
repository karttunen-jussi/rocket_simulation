//---------------------------------------------------------------------------------------------------------------------
// TCP socket server for the rocket simulation
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

// Own
#include "rocket.hpp"

// STD
#include <chrono>
#include <thread>
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

    sockaddr_in address = {};
    address.sin_family      = AF_INET;
    address.sin_port        = htons(1'234);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(socket_listen, reinterpret_cast<sockaddr*>(&address), sizeof(address)); // NOLINT(*unused-return-value)
    listen(socket_listen, 1);

    const SOCKET socket_connected = accept(socket_listen, nullptr, nullptr);

    // Set the socket non-blocking
    unsigned long mode = 1;
    ioctlsocket(socket_connected, static_cast<long>(FIONBIO), &mode);

    return socket_connected;
}

static XyVector_t SimulateRocketNextPosition(XyVector_t power_command_kW)
{
    // Rocket simulation parameters
    constexpr double time_step_s          = 1.0e-3;
    constexpr double time_update_period_s = 100.0e-3;
    constexpr double mass_rocket_kg       = 1000.0;

    static Rocket_t rocket{
        {.time_step_s    = time_step_s,
         .mass_rocket_kg = mass_rocket_kg}
    };

    double time_elapsed_s = 0.0;
    while (time_elapsed_s <= time_update_period_s)
    {
        rocket.UpdateState(power_command_kW);
        time_elapsed_s += time_step_s;
    }

    return rocket.GetPosition_m();
}

//---------------------------------------------------------------------------------------------------------------------
// EXECUTABLE MAIN FUNCTION DEFINITION
//---------------------------------------------------------------------------------------------------------------------

int main()
{
    const SOCKET socket = ConnectSocket();

    // Infinite loop for the periodic task (100ms period)
    auto time_point_next_period = std::chrono::steady_clock::now();
    while (true)
    {
        XyVector_t power_command_recv_kW = {};
        const int count_recv_bytes = recv(socket,
                                          reinterpret_cast<char*>(&power_command_recv_kW),
                                          sizeof(XyVector_t),
                                          0);

        static XyVector_t power_command_kW;
        if (count_recv_bytes == sizeof(XyVector_t))
        {
            power_command_kW = power_command_recv_kW;
        }

        const XyVector_t position_m = SimulateRocketNextPosition(power_command_kW);

        send(socket,
             reinterpret_cast<const char*>(&position_m),
             sizeof(XyVector_t),
             0);

        using std::chrono::operator""ms;
        time_point_next_period += 100ms;
        std::this_thread::sleep_until(time_point_next_period);
    }
}
