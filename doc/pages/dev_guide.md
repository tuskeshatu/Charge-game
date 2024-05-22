\page dev_guide Developers' guide

# Developers' guide

## Prerequisites

### SFML

To build the project, first you need to install the great and holy [SFML library](https://www.sfml-dev.org/index.php). For this project I used [SFML 2.6.1](https://www.sfml-dev.org/download/sfml/2.6.1/). You can download SFML through their [official website](https://www.sfml-dev.org/download.php), though I **strongly advise** against it. Either you should install SFML through your beloved package manager (pacman with [mysys](https://packages.msys2.org/package/) if you're on windows and apt if youre on linux) **OR** compile it yourself from their [official source code](https://github.com/SFML/SFML) to prevent compiler version incompatibilities.

Friendly reminder if using mysys and pacman: make sure to download the version for the correct toolchain you want to use (choose the repository at the top left corner on the mysys website).

### nlohmann JSON Library

In this project, I used the nlohmann JSON library to handle JSON data. It provides a simple interface for parsing and generating JSON data.

To use the nlohmann JSON library in your project, you need to include the nlohmann header files and link against the nlohmann library. You can find the library and header files on the [nlohmann GitHub repository](https://github.com/nlohmann/nlohmann-JSON).

You can again either get it via a package manager, *(which I suggest to avoid the pain I had to go through,)* or compile it yourself.

## Build

There is a makefile template in the repository. Use it to make the project with mingw32-make. To have the program to compile specify the path of the SFML precompiled libraries at LDFLAGS.

If you are not using gcc you should update CXX and CXXFLAGS too.

After these steps you should be able to just run mingw-32make (or just make on UNIX systems) and the program should be compiled corectly without warnings. The binary can be found as ./bin/charge.exe.

## OOP in Charge-game

### OOP in Charge-game

The Charge-game project follows an Object-Oriented Programming (OOP) approach to design and implement its components. OOP allows for better organization, modularity, and reusability of code.

The project is structured around various classes and objects, each representing a specific entity or functionality within the game. These classes include:

- `Charge`: Represents a charged object. Stores it's electric charge and provides virtual interface for derived classes. Fully abstract class.

- `Player`: Represents the player character in the game. It contains attributes such as velocity, position and body, as well as methods for movement and interaction with other game objects.

- `Obstacle`: Represents the obstacles in the game. It includes attributes like position and body, along with methods for getting attributes.

- `Level`: Represents a level in the game. Stores the obstacles in the game as well as level specific attributes, such as size and level name.

- `LevelManager`: Singleton class representing the level manager. Includes attributes, such as possible loadable levels and methods for interacting (loading, saving, deleting) with levels.

By using OOP principles, the project achieves a modular and maintainable codebase, making it easier to add new features, fix bugs, and improve overall code quality.

### UML Diagram

To generate the UML diagram I used [hpp2puml](https://github.com/thibaultmarin/hpp2plantuml) to parse the header files and automatically create a [plantuml](https://plantuml.com/) file, from which I can generate a png file automatically.

![UML Diagram of Charge-game](uml/ChargeUML.PNG)