#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <cmath>
#include <array>
#include <limits>
#include <cstring>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "../include/classes.hpp"
#include "../include/threads.hpp"
#include "../include/modelFileHandler.hpp"
#include "../include/triangle.hpp"
#include "../include/textureFileHandler.hpp"
#include "../include/renderFileHandler.hpp"
#include "../include/camera.hpp"
#include "../include/ray.hpp"

int main() {
    int constexpr width = 100;
    int constexpr height = 100;
    vector3 constexpr cameraPosition = {0, 2, 2};
    int constexpr cameraFieldOfView = 90;
    float viewportDistance = 1;
    vector3 target = {0, 2, 0};
    vector3 v = {0, 1, 0};
    const std::string imageFileName = "../renders/render.bmp";
    // const std::string modelFileName = "../models/skull.obj";
    const std::string modelFileName = "../models/farquaad.obj";
    // const std::string textureFileName = "../models/skull.jpg";
    const std::string textureFileName = "../models/farquaad.png";
    cameraClass camera(cameraPosition, cameraFieldOfView, viewportDistance, v);
    

    modelFileClass modelFile(modelFileName);    
    textureFileClass textureFile(textureFileName);

    threadPoolClass threadPool;

    std::vector<triangleClass> triangleVector = triangleClass::generateTriangles(modelFile);
    std::vector<rayClass> rayVector = rayClass::initializeRays(target, camera, height, width, v);
    std::vector<pixelStruct> pixelVector = rayClass::renderImage(rayVector, width, height, triangleVector, textureFile.pixelVector,
        textureFile.infoHeader.width, textureFile.infoHeader.height, threadPool);


    renderFileClass renderFile(width, height, imageFileName);
    renderFile.write(pixelVector);
    renderFile.file.close();
    

    return 0;
}