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

The resulting dynamic can be seen in the Gif below. The initial state was created by using a probability of 1/2 for a
cell to either be alive or dead. The grid contains 200 cells in x- and y-direction. 

<br>
<br>
<p align="center">
<img src=/images_and_gifs/game_of_life.gif>
</p>
