import matplotlib.animation as animation
import matplotlib.pyplot as plt
import pandas as pd

# Specify CSV file name and location
csv_file_path = "rocket_sim_data_points.csv"

# Read the CSV file
data = pd.read_csv(csv_file_path)

time_step_data_ms           = 1.0
time_interval_animation_ms  = 100.0
count_data_points_per_frame = int(time_interval_animation_ms / time_step_data_ms)

x_axis_signal = "Position_x[m]"
y_axis_signal = "Position_y[m]"

x_axis_data = data[x_axis_signal]
y_axis_data = data[y_axis_signal]

fig, axis = plt.subplots(1, 1)
fig.set_tight_layout(True)
line_object = axis.plot([], [])

plot_margin = 10.0
axis.set_xlim(min(x_axis_data) - plot_margin, max(x_axis_data) + plot_margin)
axis.set_ylim(min(y_axis_data) - plot_margin, max(y_axis_data) + plot_margin)
axis.grid()

plt.xlabel(x_axis_signal)
plt.ylabel(y_axis_signal)

# Update function for animation
def UpdateAnimation(frame_number):
    count_plotted_points = (frame_number + 1) * count_data_points_per_frame

    x_axis_plot_data = x_axis_data[0:count_plotted_points]
    y_axis_plot_data = y_axis_data[0:count_plotted_points]
    line_object[0].set_data(x_axis_plot_data, y_axis_plot_data)

    return line_object

# Animate the plot
ani = animation.FuncAnimation(fig      = fig,
                              func     = UpdateAnimation,
                              interval = int(time_interval_animation_ms),
                              blit     = False,
                              cache_frame_data = False)

# Display the plot
plt.show()
