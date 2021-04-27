# Conway's game of life

This is a simple program simulating Conway's game of life in C++ using SDL. The game of life has several
different interpretations ranging from biological and physical ones to the study of cellular automata. News surrounding
this topic can be looked up [here](https://www.conwaylife.com/). Further the YouTube channel Numberphile has released
an interesting [video](https://www.youtube.com/watch?v=R9Plq-D1gEk) discussing the game of life with its creator John
Conway.

## Game rules

Conway's game of life is an easy to understand simulation of cells. These cells live on a 2D grid and can either be
alive (true) or dead (false). The flow of time is discretized into steps. If a cell dies or gets born from one time
step to another is decided by the state of its neighbouring cells and follows three simple rules:

1. A dead cell with exactly three living neighbours begins to live.
2. A living cell with exactly two or three living neighbors continues living.
3. All other cells die due to overpopulation or isolation.

These three simple rules can produce a rather complex behaviour with structures that can move across the grid, pulse
periodically or shoot living cells.

## Results

An example of resulting dynamic can be seen in the Gif below. The initial state was created by using a probability of
1/2 for a cell to either be alive or dead. The living cells are colored green and dead cells black.
The grid contains 200 cells in x- and y-direction. 

<br>
    <br>
        <p align="center">
            <img src=/doc/game_of_life.gif>
        </p>

## Statistical analysis

I am physicist and because of this I have to find the fix points of this system and try to predict the ratio/density
of living cells using a model. A very simple model can obtained by thinking of the living cells from one time step to
another. The density of living cells from one time step to another can be calculated by taking into account all
scenarios in which a cell is born. Further, it is assumed that the neighbouring cells behave according te the binomial
distribution. This means that the density of living cells from one time step to another can be calculated by
<br>
    <br>
        <p align="center">
            <img src=/doc/binomial_model.jpeg>
        </p>
In an equilibrium the density doesn't change and it thus given by solving the following equation
<br>
    <br>
        <p align="center">
            <img src=/doc/equilibrium_equation.jpeg>
        </p>
Solving this equation leads to the following results
<br>
    <br>
        <p align="center">
            <img src=/doc/density_solutions.jpeg>
        </p>
Examining the time evolution of this model for different initial densities makes it clear that only two of the three
values for the equilibrium densities appear, namely 0 and 0.370. The time evolutions in the image below were taken from
initial densities ranging from 0 to 1 in 0.005-steps.
<br>
    <br>
        <p align="center">
            <img src=/doc/timestep_density_plot.jpeg>
    </p>
Plotting the initial against the final density makes it clear that initial densities between 0.19 and 0.56 result in
a final density of 0.37 while all other result in a final density of 0.
<br>
    <br>
        <p align="center">
            <img src=/doc/predicted_densities.jpeg>
        </p>
Finally, the behavior of the model can be compared to the behavior of the simulation. This will be done for an initial
density of 0.5.
<br>
    <br>
        <p align="center">
            <img src=/doc/timestep_vs_density.jpeg>
        </p>
As one can see the prediction of the model does not coincide very well with the actual behavior of the game of life.
The simulation settles into equilibrium at a density of roughly 0.03, which means that the predicted density is
off by a factor of 10 (really much). This is partly due to the fact that I disregarded correlations between the cells
and oversimplified my model. The results published in [1] further support this. At the beginning of the before mentioned
paper a similar approach is taken which results in the same faulty prediction as my model.

## Sources

[1]     L. S. Schulman, P. E. Seiden, Statistical Mechanics of a Dynamical System Based on Conway's Game of Life,
Journal of Statistical Physics 19, 293 (1978).
