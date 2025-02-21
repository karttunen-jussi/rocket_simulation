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

# for i, signal in enumerate(data.columns):
#    data.plot(ax=axes[i], y=signal)

# ------------------------------------------------------------------------------------
plt.xlabel("Time[s]")

all_plot_line_objects = []
for n in range(number_of_subplots):
    axis_of_subplot = axes[n]
    line_object_for_signal = axis_of_subplot.plot([], [])
    all_plot_line_objects.append(line_object_for_signal)
    # axis_of_subplot.set_ylabel(ylabel_names_for_subplots[n])
    # axis_of_subplot.legend(signal_names_in_subplot, loc='lower left')
    axis_of_subplot.grid()


# Update function for animation
def UpdateAnimation(frame_number):
    for n in range(number_of_subplots):
        line_object_for_signal = all_plot_line_objects[n]
        signal_data = data[n][:frame_number * 10]
        time_data = data.index[:frame_number * 10]
        line_object_for_signal[0].set_data(time_data, signal_data)

    for k in range(number_of_subplots):
        axis_of_subplot = axes[k]
        axis_of_subplot.relim()
        axis_of_subplot.autoscale_view()
        axis_of_subplot.set_xlim(time_data[0], time_data[-1])

    return all_plot_line_objects


# Animate the plot
ani = animation.FuncAnimation(fig, UpdateAnimation, blit=False, interval=300)

# Display the plot
plt.show()
