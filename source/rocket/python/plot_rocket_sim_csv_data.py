import matplotlib.pyplot as plt
import pandas as pd

# Specify CSV file name and location
csv_file_path = "rocket_sim_data_points.csv"

# Read the CSV file
data = pd.read_csv(csv_file_path)

# Set "Time[s]" as the x-axis data for the figure
data.set_index("Time[s]", inplace=True)

fig, axes = plt.subplots(2, 1, sharex=True)
fig.set_tight_layout(True)

for i, signal in enumerate(data.columns):
    data.plot(ax=axes[i], y=signal)

# Plot the data into figure
plt.show()
