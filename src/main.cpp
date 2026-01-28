#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <cmath>
#include <array>
#include <limits>
#include "../include/classes.hpp"
#include "../include/modelFileHandler.hpp"
#include "../include/imageFileHandler.hpp"
#include "../include/triangle.hpp"
#include "../include/camera.hpp"
#include "../include/ray.hpp"

int main() {
    int constexpr width = 100;
    int constexpr height = 100;
    vector3 constexpr cameraPosition = {55, -150, 55};
    int constexpr cameraFieldOfView = 60;
    float viewportDistance = 1;
    vector3 target = {0, 0, 70};
    vector3 v = {0, 1, 0};
    const std::string imageFileName = "../renders/render.bmp";
    const std::string modelFileName = "../models/farquaad.obj";
    cameraClass camera(cameraPosition, cameraFieldOfView, viewportDistance, v);
    



    modelFileClass modelFile;
    modelFile.loadModel(modelFileName);
    modelFile.file.close();
    
    
    
    std::vector<triangleClass> triangleVector = triangleClass::generateTriangles(modelFile);
    std::vector<rayClass> rayVector = rayClass::initializeRays(target, camera, height, width, v);
    std::vector<pixelStruct> pixelVector = rayClass::renderImage(rayVector, width, height, triangleVector);



    imageFileClass imageFile(width, height, imageFileName);
    imageFile.write(pixelVector);
    imageFile.file.close();
    

    return 0;
}