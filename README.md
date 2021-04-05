[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]

## softbody-sim-cpp

### About The Project

This is a pressure-based softbody dynamics simulator. This model works on a spring-mass system: Every vertex has a mass and is connected to the next vertex by a spring which has default resing length. Firstly, we apply "pressure" which is basically a force on every vertex vectoring outwards from the center. This way we get the ball-shaped softbody which cannot deform, the pressure continuously applies force on the vertices. The springs help us calculate the accumalated force on every vertex.

Then we can apply external forces and see what happens!

### Prerequisites

Must have installed:
* SFML V2+
* make
* cmake
* C++ compiler

### Installation

Building:
```
mkdir build
cd build
cmake ..
make
```
Running:
```
./SoftbodySim
```

### Usage

```Left Mouse Click``` Place object

```Space```            Start simulation

```Left Mouse Press``` Dragging object

To be implemented: walls and boundries.

### Sources

* https://www.youtube.com/watch?v=5HTqYYPAzqA
* http://panoramx.ift.uni.wroc.pl/~maq/soft2d/howtosoftbody.pdf
* https://research.ncl.ac.uk/game/research/publications/Real-Time%20Deformable%20Soft-Body%20Simulation.pdf


[stars-shield]: https://img.shields.io/github/stars/Levako/softbody-sim-cpp.svg?style=for-the-badge
[stars-url]: https://github.com/Levako/softbody-sim-cpp/stargazers
[issues-shield]: https://img.shields.io/github/issues/Levako/softbody-sim-cpp.svg?style=for-the-badge
[issues-url]: https://github.com/Levako/softbody-sim-cpp/issues
