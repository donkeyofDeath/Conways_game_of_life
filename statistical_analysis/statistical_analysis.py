import numpy as np
import matplotlib.pyplot as plt
import matplotlib
import pandas as pd

# Importing the data. Their could be a nicer way but I haven't worked with pandas really much so this will do.
data = pd.read_csv("data.csv").astype(float).to_numpy()
time_steps = len(data)
data = data.reshape(time_steps)


def update_func(density):
    """

    :param density:
    :return:
    """
    return 28 * density**3 * (1 - density)**5 * (3 - density)


def model(initial_density, number_of_time_steps):
    """

    :param initial_density:
    :param number_of_time_steps:
    :return:
    """
    current_density = initial_density

    def density_update(den):
        """

        :param den:
        :return:
        """
        nonlocal current_density
        current_density = update_func(den)
        return current_density

    return np.array([density_update(current_density) for _ in range(number_of_time_steps)])


x_coord = range(time_steps)

fig, ax = plt.subplots(1, 1)

ax.set_yscale("log")
ax.set_yticks([0.03, 0.1, 0.3, 0.5])
ax.get_yaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())

ax.set_xlabel("time step")
ax.set_ylabel("density")

ax.grid(True)

ax.plot(x_coord, data)
ax.plot(x_coord, model(0.5, time_steps))

plt.tight_layout()
plt.show()
