import numpy as np
import matplotlib.pyplot as plt
import matplotlib
import pandas as pd

# Importing the data. Their could be a nicer way but I haven't worked with pandas really much so this will do.
data = pd.read_csv("data.csv").astype(float).to_numpy()
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
    :param number_of_time_steps: Number of time steps for which the
    :return:
    """
    current_density = initial_density

    def update_and_save(den):
        """

        :param den:
        :return:
        """
        nonlocal current_density
        current_density = update_density(den)
        return current_density

    return np.array([update_and_save(current_density) for _ in range(number_of_time_steps)])


# -------------------------------------------------
# Plotting the simulation results against the model
# -------------------------------------------------

x_coord = range(time_steps)

fig, ax = plt.subplots(1, 1)

ax.set_yscale("log")
ax.set_yticks([0.03, 0.1, 0.3, 0.5])
ax.get_yaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())

ax.set_xlabel("time step")
ax.set_ylabel("density")

ax.grid(True)

ax.plot(x_coord, data)
ax.plot(x_coord, evolve_modeled_density(0.5, time_steps))

plt.tight_layout()
plt.show()
