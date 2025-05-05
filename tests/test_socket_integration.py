import socket
import struct
import subprocess
import time
import pytest

@pytest.fixture
def rocket_path(request):
    path_to_rocket = request.config.getoption("--rocket-path")
    return path_to_rocket


def start_rocket(exe_path) -> None:
    return subprocess.Popen(
        [exe_path],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )

def test_rocket_socket_integration(rocket_path):
    
    rocket = start_rocket(rocket_path)
    time.sleep(1)

    try:
        port_tcp_socket = 1234
        tcp_socket_sim = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        tcp_socket_sim.connect(("localhost", port_tcp_socket))

        data_send_raw = struct.pack("<2d", 5.0, 15.0)
        tcp_socket_sim.sendall(data_send_raw)

        data_received_raw = tcp_socket_sim.recv(16)
        data_converted = struct.unpack("<2d", data_received_raw)
        print("Got back from Rocket:", data_converted)

        assert len(data_converted) == 2
        assert all(isinstance(i, float) for i in data_converted)

    finally:
        tcp_socket_sim.close()
        subprocess.call(["taskkill", "/F", "/T", "/PID", str(rocket.pid)])
