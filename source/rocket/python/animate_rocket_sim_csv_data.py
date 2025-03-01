import matplotlib.animation as animation
import matplotlib.pyplot as plt
import pandas as pd

# Specify CSV file name and location
csv_file_path = "rocket_sim_data_points.csv"

# Read the CSV file
data = pd.read_csv(csv_file_path)

# Set "Time[s]" as the x-axis data for the figure
data.set_index("Time[s]", inplace=True)

number_of_subplots = len(data.columns)
fig, axes = plt.subplots(number_of_subplots, 1, sharex=True)
fig.set_tight_layout(True)

plt.xlabel("Time[s]")

all_plot_line_objects = []
for n in range(number_of_subplots):
    axis_of_subplot = axes[n]
    line_object = axis_of_subplot.plot([], [])
    all_plot_line_objects.append(line_object)
    axis_of_subplot.set_ylabel(data.columns[n])
    axis_of_subplot.grid()

# Update function for animation
def UpdateAnimation(frame_number):
    count_plotted_points = (frame_number + 1) * 100
    for n in range(number_of_subplots):
        line_object = all_plot_line_objects[n]
        signal_data = data.iloc[0:count_plotted_points, n]
        time_data   = data.index[0:count_plotted_points]
        line_object[0].set_data(time_data, signal_data)

    for k in range(number_of_subplots):
        axis_of_subplot = axes[k]
        axis_of_subplot.relim()
        axis_of_subplot.autoscale_view()
        axis_of_subplot.set_xlim(time_data[0], time_data[-1])

    return all_plot_line_objects

# Animate the plot
ani = animation.FuncAnimation(fig, UpdateAnimation, blit=False, interval=100, cache_frame_data=False)

# Display the plot
plt.show()
