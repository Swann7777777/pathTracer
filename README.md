# Ray Tracer from scratch

This is my **ongoing** project is to create a ray tracer only using the standard C++ library.

This ray tracer currently only supports *Wavefront* ( .obj and .mtl ) files.


## How to use

### Run


Clone the repository :

`git clone https://github.com/Swann7777777/pathTracer`

Change your directory to the cloned repository :

`cd pathTracer`

Create a build directory and change your path to it :

`mkdir build && cd build`

Build the project using CMake :

`cmake ..`

Build the code :

`make`

Run the executable :

`./main`


### Edit the render

Open `src/main.cpp`.
At the beggining of the `main()` function, edit :

`renderWidth` with the desired width of your render image.\
`renderHeight` with the desired height of your render image.\
`cameraPosition` with the camera position x y z coordinates.\
`cameraFieldOfView` with the desired camera field of view.\
`target` with the camera target x y z coordinates (where it's gonna be aiming).\
`modelDirectory` with the folder containing your model.\
`modelFileName` with the name of your model to render.\
`textureFileName` with the name of your texture file or leave blank if the model contains a .mtl file.



## TO-DO

- Implement secondary rays
- Add support for transparency
- Implement light sources