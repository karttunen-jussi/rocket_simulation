import matplotlib.pyplot as plt
import pandas as pd

# Specify CSV file name and location
csv_file_path = "rocket_sim_data_points.csv"

# Read the CSV file
data = pd.read_csv(csv_file_path)

# Assume "Time[s]" is the x-axis data for the figure
data.set_index("Time[s]", inplace=True)

# Plot the data into figure
data.plot()
plt.show()
