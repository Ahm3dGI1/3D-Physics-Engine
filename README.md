# 3D Physics Engine

## Overview

This project is a 3D physics engine that simulates 3D physics using rigid bodies and integrates a simple cloth simulation. The engine is built using C++ and OpenGL, and it showcases various physics concepts such as spring forces, rigid body dynamics, and collision detection.

## Features

- **Real-Time Rendering:** Utilizes OpenGL for real-time rendering of 3D objects.
- **Rigid Body Dynamics:** Simulation of rigid bodies, including collision detection and response.
- **Collision Detection:** Detect and respond to collisions between different rigid bodies (Boxes, Spheres, Planes, and Particles).
- **Cloth Simulation: Ba**sic cloth simulation using particles connected by springs.
- **Camera Controls:** Allows for user interaction with the simulation, including the ability to manipulate objects and adjust physics parameters.
- **Custom Math Library:** Includes custom implementations of matrix and vector operations.
- **Extensible Framework:** Modular design that allows for easy extension and customization.
- **Rendering: Real-time** rendering using OpenGL.

## Demos

## Getting Started
### Prerequisites

- C++ compiler (e.g., g++, clang++)
- OpenGL
- CMake
- GLFW

### Build Instructions
I'm working on adding a GUI that allows for a sandbox mode so that the user can experiment with whatever they want and run demos easily, but it's not available yet. So, to build custom scenes you can edit the main.cpp file in the src folder using functions and datatypes mentioned in the next section.

## Usage
### Controls
 
 - W/A/S/D: Move the camera
 - Mouse: Rotate the camera
 - Space: Apply a force to the selected object (in specific demos)
 - R: Reset the simulation

### Building Scenes 
- To build custom scenes, you can modify the main.cpp file. The current main.cpp is an example of how to set up a basic scene with physics objects, camera controls, and collision handling.

- To add new physics objects, use the PhysicsObject class and specify the shape, position, mass, and restitution coefficient. For example:

```
                                    // Box Shape        // position      // Mass and damping
objects.push_back(PhysicsObject(make_unique<Box>(), Vec3(0.0f, 10.0f, 0.0f), 5.0f, .7f));
                // Sphere of radius 1 and 3 subdivisions        // Position    // Mass and Damping
objects.push_back(PhysicsObject(make_unique<Sphere>(1.0, 3), Vec3(5.0f, 10.0f, 0.0f), 5.0f, .7f));
```

- Or you can add cloth or spring objects using:
```
Cloth cloth(10, 10, 3.0f, 1.0f, 1.0f, Vec3(0.0f, 0.0f, 0.0f));
Spring spring(object[0], object[1], 2.0f, 1.0f)
```

- To modify inputs 

- The math library includes custom implementations of common mathematical operations and data structures, such as vectors and matrices.


## Contributing
Contributions are welcome! Please fork the repository and submit a pull request with your changes.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.

## Contact
For any questions or inquiries, please contact me at ahmedgouda797@gmail.com.