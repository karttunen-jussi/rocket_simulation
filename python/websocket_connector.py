import asyncio
import socket
import struct
import threading
import time
import queue
from websockets.asyncio.server import serve

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
 
async def ReceiveHandler(websocket):
    async for message in websocket:
        power_command_values = message.split(";")
        power_x_kW = float(power_command_values[0])
        power_y_kW = float(power_command_values[1])
        queue_power_command.put((power_x_kW, power_y_kW))

async def SendHandler(websocket):
    while True:
        if (not queue_position_feedback.empty()):
            position_x_m, position_y_m = queue_position_feedback.get()
            message = str(str(position_x_m) + ";" + str(position_y_m))
            await websocket.send(message)
            await asyncio.sleep(0.01)

async def WebSocketHandler(websocket):
    await asyncio.gather(
        ReceiveHandler(websocket),
        SendHandler(websocket),
    )

async def main():
    async with serve(WebSocketHandler, "localhost", 8765) as server:
        await server.serve_forever()

asyncio.run(main())
