# Introduction to Fiducial Markers

Welcome to the project repository on exploring fiducial markers, specifically using Aruco markers. This project aims to provide an introductory guide to fiducial markers and their applications in computer vision using OpenCV and Ovis. It is designed for those who are interested in learning how to detect, estimate poses, and utilize fiducial markers for augmented reality applications.

## Table of Contents

1. [Introduction](#introduction)
2. [Prerequisites](#prerequisites)
3. [Installation](#installation)
4. [Executables](#executables)
5. [Usage](#usage)
6. [Markers Print](#markers-print)
7. [Resources](#resources)
8. [Contributing](#contributing)
9. [License](#license)

## Introduction

The objective of this project is to gain insights into the functioning of fiducial markers, explore their possibilities and limitations, and define example applications using the OpenCV library and the Ovis module. The core concepts covered in this project include:

- Understanding the detection of Aruco fiducial markers.
- Computing the homography using detections and applying a patch.
- Estimating pose using detections and reprojecting a 3D object.
- Utilizing the Ovis package to set a 3D object in the scene, which rotates and translates according to the marker's pose.

## Prerequisites

To run this project, the following tools and libraries are required:

- **OpenCV 4.5.5** with `opencv_contrib` and `nonfree` modules.
- **Ogre 13.3.3** (Ovis module dependencies included).
- **Visual Studio Code** as the development environment.
- **Ubuntu 20.04.4 LTS** as the operating system.
- A camera for marker detection and printed Aruco markers.

### Required Dependencies

- `libgles2-mesa-dev`
- `libvulkan-dev`
- `glslang-dev`
- `libxrandr-dev`
- `libsdl2-dev`
- `libxt-dev`
- `libxaw7-dev`
- `doxygen`

Make sure to enable the `OGRE_BUILD_DEPENDENCIES` CMake variable when configuring Ogre.

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/repositoryname.git
    ```
2. Install the necessary dependencies:
    ```bash
    sudo apt-get install libgles2-mesa-dev libvulkan-dev glslang-dev libxrandr-dev
    sudo apt-get install libsdl2-dev libxt-dev libxaw7-dev doxygen
    ```
3. Build the project using CMake with the appropriate configurations.

## Executables

The project is divided into auxiliary and main executables:

### Auxiliary Executables

1. **Aruco Markers Printing**: Allows you to print your own Aruco markers using OpenCV.
2. **Ovis Installation Test**: Verifies the correctness of the Ovis installation.

### Main Executables

1. **Main Application**: Demonstrates various fiducial marker applications.
    - **Marker 1**: Estimates pose and reprojects a pyramid onto the marker.
    - **Marker 2**: Custom detection drawing is performed.
    - **Marker 3**: Computes homography and applies a patch onto the marker.
2. **Main Application + Ovis**: Adds 3D object manipulation using the Ovis module, where a 3D object is translated and rotated according to the marker's estimated pose.

## Usage

1. Print the Aruco markers from the `markers` directory.
2. Run the main executable to explore different marker applications.
3. Use the Ovis version to experience 3D object integration.

## Markers Print

You can find the printable Aruco markers in the `markers` directory. These markers are essential for testing and using the application effectively.

## Resources

- [University of Córdoba Research Group](https://www.uco.es/investiga/grupos/ava/)
- [OpenCV 4.5.5 Release](https://github.com/opencv/opencv/releases/tag/4.5.5)
- [OGRE 13.3.3 Release](https://github.com/OGRECave/ogre/releases/tag/v1.12.13)

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request or create an Issue for any suggestions or improvements.

## License

This project is licensed under the MIT License.

---

For more information, please refer to the detailed report available in the repository.
