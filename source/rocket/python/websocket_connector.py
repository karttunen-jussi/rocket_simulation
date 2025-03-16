import socket
import struct
import threading
import time
import queue
from websockets.sync.server import serve

# Queues to handle exchanging data between threads
queue_power_command = queue.Queue()
queue_position_feedback = queue.Queue()

#######################################################################################################################
# TCP socket connection with the Rocket simulator
#######################################################################################################################

# Connect TCP socket with the Rocket simulator
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
        # Place the converted data into the queue for real-time plotting
        queue_position_feedback.put(data_converted)

# Create and start the thread
tcp_socket_receive_thread = threading.Thread(target=TcpSocketReceive, daemon=True)
tcp_socket_receive_thread.start()

def TcpSocketSend():
    while True:
        if (not queue_power_command.empty()):
            power_commands = queue_power_command.get()
            data_send_raw = struct.pack("<2d", power_commands[0], power_commands[1])
            tcp_socket_sim.sendall(data_send_raw)
        else:
            time.sleep(0.1)

tcp_socket_send_thread = threading.Thread(target=TcpSocketSend, daemon=True)
tcp_socket_send_thread.start()


#######################################################################################################################
# Websocket connection with the Rocket UI
#######################################################################################################################

def WebSocketHandler(websocket):
    
    # Handle received rocket power commands from UI
    for message in websocket:
        print(message)
        # Process message and put it into command queue
        # ...
        # ...

        # Below is just hardcoded test value
        queue_power_command.put((10.0, 10.0))

    # Handle sending rocket position feedback to UI     
    while (not queue_position_feedback.empty()):
        position_x_m, position_y_m = queue_position_feedback.get()
        message = str(str(position_x_m) + ";" + str(position_y_m))
        websocket.send(message)

# Connect Websocket with the Rocket UI
port_websocket = 8765
with serve(WebSocketHandler, "localhost", port_websocket) as server:
    server.serve_forever()
