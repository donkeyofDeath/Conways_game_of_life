import numpy as np
import matplotlib.pyplot as plt
import matplotlib
import pandas as pd

# Importing the data. Their could be a nicer way but I haven't worked with pandas really much so this will do.
data = pd.read_csv("data.csv").astype(float).to_numpy(dtype=float)
time_steps = len(data)
data = data.reshape(time_steps)


def update_density(density: float) -> float:
    """
    This function describes the modeled evolution of the density of living cells in Conway's game of life from one
    time step to the next.

    :param density: Density at time step t
    :return: Density at tim step t+1.
    """
    return 28 * density**3 * (1 - density)**5 * (3 - density)


def evolve_modeled_density(initial_density: float, number_of_time_steps: int) -> np.ndarray:
    """
    This function evolves an initial density of living cells according to the model described in the function
    update_density and returns the result for each time step.

    :param initial_density: Initial density, a value between 0 and 1.
    :param number_of_time_steps: Number of time steps for which the model is observed.
    :return:
    """
    current_density = initial_density

    def update_and_save_density(den: float) -> float:
        """
        This function updates the density and saves the result in the non local variable current_density
        :param den: Starting density
        :return: Density of the following time step.
        """
        nonlocal current_density
        current_density = update_density(den)
        return current_density

    return np.array([update_and_save_density(current_density) for _ in range(number_of_time_steps)])


# ---------------------------------------------------------------
# Plotting the simulation results and the prediction of the model
# ---------------------------------------------------------------

x_coord = range(time_steps)

########################################################################################################################
# Make the first plot.

fig1 = plt.figure(1)
ax1 = plt.axes()
# Set axis scale and ticks.
ax1.set_yscale("log")
y_ticks = [0.03, 0.1, 0.3, 0.5]
ax1.set_yticks(y_ticks)
# ax1.set_major_formatter(matplotlib.ticker.ScalarFormatter())
ax1.set_yticklabels([f"{y:.2f}" for y in y_ticks])

# Set labels.
ax1.set_xlabel("time step")
ax1.set_ylabel("density of living cells")

ax1.grid(True)

# Plot the simulation and the model.
ax1.plot(x_coord, data, label="Simulation")
ax1.plot(x_coord, evolve_modeled_density(0.5, time_steps), label="Model")
# place the upper right corner of the legend at (1, 1.0005).
ax1.legend(loc="upper right", bbox_to_anchor=(1, 1.005))

fig1.tight_layout()

########################################################################################################################
# Make the second figure.

fig2 = plt.figure(2)
ax2 = plt.axes()
# Set axis scale and ticks.
ax2.set_yscale("log")
y_ticks = [0.03, 0.1, 0.3, 0.5]
ax2.set_yticks(y_ticks)
# ax1.set_major_formatter(matplotlib.ticker.ScalarFormatter())
ax2.set_yticklabels([f"{y:.2f}" for y in y_ticks])

# Set labels.
ax2.set_xlabel("time step")
ax2.set_ylabel("density of living cells")

ax2.grid(True)

# Plot the simulation and the model.
ax2.plot(x_coord, data, label="Simulation")
ax2.plot(x_coord, evolve_modeled_density(0.5, time_steps), label="Model")
# place the upper right corner of the legend at (1, 1.0005).
ax2.legend(loc="upper right", bbox_to_anchor=(1, 1.005))

fig2.tight_layout()

########################################################################################################################
# Plot everything.
plt.show()
