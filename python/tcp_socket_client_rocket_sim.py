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
        data_converted = struct.unpack("<2d", data_received_raw)

        # Place the converted data into the queue for real-time plotting
        data_queue.put(data_converted)

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
# PLOTTING
#######################################################################################################################

fig, axis = plt.subplots(1, 1)
fig.set_tight_layout(True)
line_object = axis.plot([], [])
axis.grid()

plt.xlabel("Position_x[m]")
plt.ylabel("Position_y[m]")

x_axis_data = []
y_axis_data = []

# Update function for animation
def UpdateAnimation(frame_number):
    while (not data_queue.empty()):
        position_x_m, position_y_m = data_queue.get()
        x_axis_data.append(position_x_m)
        y_axis_data.append(position_y_m)

    line_object[0].set_data(x_axis_data, y_axis_data)
    plot_margin = 50.0
    axis.set_xlim(min(x_axis_data) - plot_margin, max(x_axis_data) + plot_margin)
    axis.set_ylim(min(y_axis_data) - plot_margin, max(y_axis_data) + plot_margin)

    return line_object

# Animate the plot
ani = animation.FuncAnimation(fig      = fig,
                              func     = UpdateAnimation,
                              interval = 100,
                              blit     = False,
                              cache_frame_data = False)

# Display the plot
plt.show()
