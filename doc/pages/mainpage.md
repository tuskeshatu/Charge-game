\mainpage Documentation
\subpage tutorial
\subpage dev_guide
\tableofcontents

# Charge Game

## Description

This is a repository for the Charge Game project. This project was created as a university finals project at **Budapest University of Technology and Economics**
for the course **Basics of Programming 2 (BMEVIAUAA01)** by **Levente Kovacs**.

This game lets the player place different charges around the 2D plane and interact with them through the player entity. The physical simulation uses the Euler method, which just means "we assume everything is linear if you look at it from close enough" in fancy terms. Basically the program just calculates the forces between the player and every object very fast and adds them together, thus getting a surprisingly accurate simulation.

You can play around, explore the electric fields of different shapes of charges, be they small or big.

The main idea behind the project was to learn the basics of creating a physics simulation and to learn more about graphical visualizations with the SFML library.
The code is written with object-oriented design patterns in mind, but where I found it unnecessary to use classes I just used basic global functions and global variables.

## Tutorial for players

\ref tutorial

## Developers' guide

\ref dev_guide

## Demo picture

![Demo screenshot](doc/images/demo_pic.PNG)