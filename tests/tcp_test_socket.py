
import socket
import struct
import threading
import time




port_tcp_socket = 1234
tcp_socket_sim = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcp_socket_sim.connect(("localhost", port_tcp_socket))

def TcpSocketReceive():
    while True:
        # Receive data from rocket simulation
        size_rocket_data_bytes = 16
        data_received_raw = tcp_socket_sim.recv(size_rocket_data_bytes)
        # Convert received raw bits to actual Python data type values
        data_converted = struct.unpack("<2d", data_received_raw)
        # Print the converted data into console
        print(data_converted)

# Create and start the thread
tcp_socket_receive_thread = threading.Thread(target=TcpSocketReceive, daemon=True)
tcp_socket_receive_thread.start()

def TcpSocketSend():
    while True: 
            data_send_raw = struct.pack("<2d", 5.0, 15.0)
            tcp_socket_sim.sendall(data_send_raw)
            time.sleep(0.1)

tcp_socket_send_thread = threading.Thread(target=TcpSocketSend, daemon=True)
tcp_socket_send_thread.start()

while True:
     pass