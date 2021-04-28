import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy.optimize import fsolve

##############################################################################################################
# Importing the data. Their could be a nicer way but I haven't worked with pandas really much so this will do.
##############################################################################################################

data = pd.read_csv("data.csv").astype(float).to_numpy(dtype=float)
max_time_step = len(data)
data = data.reshape(max_time_step)


###################################
# Define functions that are needed.
###################################

def update_density(density: float) -> float:
    """
    This function describes the modeled evolution of the density of living cells in Conway's game of life from one
    time step to the next.

    :param density: Density at time step t
    :return: Density at tim step t+1.
    """
    return 28 * density ** 3 * (1 - density) ** 5 * (3 - density)


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

    return np.array([initial_density]+[update_and_save_density(current_density) for _ in range(number_of_time_steps-1)])


#######################################
# Find the steady states of the system.
#######################################

# Print the predicted solutions.
print("Predicted solutions:\n", set([round(fsolve(lambda x: update_density(x) - x, np.array([init_dens]))[0], 3)
                                     for init_dens in np.arange(0, 1, 0.05)]))


# ===============================================================
# Plotting the simulation results and the prediction of the model
# ===============================================================

######################
# Make the first plot.
######################

# A list with all the tim steps.
time_steps = range(max_time_step)

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
ax1.plot(time_steps, data, label="Simulation")
ax1.plot(time_steps, evolve_modeled_density(0.5, max_time_step), label="Model")
# Place the upper right corner of the legend at (1, 1.0005).
ax1.legend(loc="upper right", bbox_to_anchor=(1, 1.005))

fig1.tight_layout()


#######################
# Make the second plot.
#######################

# Number of time steeps used by the model.
number_of_time_steps_model = 15

# List of all the time steps.
time_steps = range(number_of_time_steps_model)
# Starting densities which will be fed to the model.
initial_densities = np.linspace(0, 1, num=100)
# Resulting time evolutions.
densities_time_evolution = np.array([evolve_modeled_density(density, number_of_time_steps_model)
                                     for density in initial_densities])

# Make with the second plot.
fig2 = plt.figure(2)
ax2 = plt.axes()

# Set labels.
ax2.set_xlabel("time step")
ax2.set_ylabel("modeled density of living cells")
ax2.grid(True)

# Add all the modeled data to the plot.
for density_data in densities_time_evolution:
    ax2.plot(time_steps, density_data)

fig2.tight_layout()


######################
# Make the third plot.
######################

resulting_densities = [density_evolution[-1] for density_evolution in densities_time_evolution]

# Initialize the third figure.
fig3 = plt.figure(3)
ax3 = plt.axes()

# Set labels.
ax3.set_xlabel("initial densities")
ax3.set_ylabel("modeled resulting densities")
ax3.grid(True)

# Plot the initial densities against the final densities.
ax3.plot(initial_densities, resulting_densities)

fig3.tight_layout()


#####################
# Show all the plots.
#####################

plt.show()
