# Physics Engine

This library is intended to serve as a resource for applications utilizing 
complex physics equations and collision detection/response. At this time, only 
circular particles are supported.

The overall project layout is inspired by the [Boost project][1], and was 
developed in a Docker Dev Container with VS Code.
[Nic Holthaus' C++ units library][2] is used heavily throughout, and provides 
an extra layer of security for the underlying mathematical equations.

## Project Goals

The goals of this project were to experiment an existing units library 
and to make use of the features provided by C++20 for designing systems with 
a more generic, functional paradigm. I also wanted to learn more about 
designing libraries intended to be used by other developers.

Mostly, though, I just wanted to learn more about how physics engines were 
implemented. There's something incredibly satisfying about watching a bunch of 
particles fly into each other and bounce all over the place.

## Usage

### Units

This repository wraps [Nic Holthaus' C++ units library][2] under the namespace 
`physics::units`. For a more detailed look at what operations are available, 
as well as how to create new, custom units, see the project's github page.

### Creating a Particle

_TODO_

### Stepping the Simulation

_TODO_

## Development

The following sections outline the process for setting up the and using the 
development environment.

### Prerequisites

The following instructions assume that Docker, VSCode and Git are installed on 
the host computer. The VSCode extension Remote Development 
(ms-vscode-remote.vscode-remote-extensionpack) is required to open the project 
in a Dev Container. 

### Setting Up The Development Environment

1) Clone the repository onto the host computer with the following command:
   ```
    git clone https://github.com/hayesHowYaDoin/physics_backend.git
   ```
2) Open the folder in VSCode. In the Command Palette (Ctrl+Shift+P), execute 
the command "Dev Containers: Open Folder In Container..."

And... that's it!

### Future Plans

If I find the time to do so, there are quite a bit of features I would like to 
add to this repository.

For one, it would be much easier from a user standpoint  if there were a 
"simulation" class which handles the aggregation, creation, and destruction of 
particles, as well as the stepping of the simulation. However, I consider this 
to be more "icing" than anything.

The real next task will be to optimize collision detection and response. At 
this time, collision resolution operates in $O(n^2)$ time, as each particle is 
compared directly to each other particle in the simulation. There are a 
plethora of cool and interesting ways to get around this, and I hope to spend 
time on them soon.

For the initial release, I attempted to create pybind11 bindings for this 
library. This was cut to reduce the scope of this initial effort, but I still 
think that this would be a valuable exercise.

[1]: https://github.com/boostorg/boost
[2]: https://github.com/nholthaus/units
