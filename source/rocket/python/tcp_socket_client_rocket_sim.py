import matplotlib.pyplot    as plt
import matplotlib.animation as animation
import socket
import struct
import threading
import time
import queue

command_queue = queue.Queue()
data_queue    = queue.Queue()

#######################################################################################################################
# THREAD: Get user keyboard commands
#######################################################################################################################

def GetUserKeyboardCommand():
    while True:
        command_string = input("Waiting keyboard command...\n")
        power_command_values = command_string.split(";")
        power_x_kW = float(power_command_values[0])
        power_y_kW = float(power_command_values[1])
        command_queue.put((power_x_kW, power_y_kW))

# Create and start the thread
wait_keyboard_thread = threading.Thread(target=GetUserKeyboardCommand, daemon=True)
wait_keyboard_thread.start()


#######################################################################################################################
# THREAD: Send and receive data from TCP Socket
#######################################################################################################################

ip_address = "localhost"
port_tcp_socket = 1234
size_rocket_data_bytes = 16

# Connect TCP socket with configured settings
socket_rocket_sim = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket_rocket_sim.connect((ip_address, port_tcp_socket))

def ReceiveDataFromTcpSocket():
    while True:
        # Receive data rocket simulation
        data_received_raw = socket_rocket_sim.recv(size_rocket_data_bytes)

        # Convert received raw bits to actual Python data type values
        data_converted_tuple = struct.unpack("<2d", data_received_raw)
        data_converted_list  = list(data_converted_tuple)
        print(data_converted_list)

        # Place the converted data into the queue for real-time plotting
        data_queue.put(data_converted_list)

# Create and start the thread
receive_feedback_thread = threading.Thread(target=ReceiveDataFromTcpSocket, daemon=True)
receive_feedback_thread.start()

def SendDataToTcpSocket():
    while True:
        if (not command_queue.empty()):
            power_command_values = command_queue.get()
            command_frame = struct.pack("<2d", power_command_values[0], power_command_values[1])
            socket_rocket_sim.sendall(command_frame)
        else:
            time.sleep(0.1)

send_command_thread = threading.Thread(target=SendDataToTcpSocket, daemon=True)
send_command_thread.start()

#######################################################################################################################
# MAIN THREAD 
#######################################################################################################################

# Trap the main thread here
while True:
    time.sleep(1.0)
