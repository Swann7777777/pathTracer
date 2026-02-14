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
#include <future>
#include <algorithm>
#include <map>
#include "../include/classes.hpp"
#include "../include/threadPool.hpp"
#include "../include/textureFileHandler.hpp"
#include "../include/modelFileHandler.hpp"
#include "../include/renderFileHandler.hpp"
#include "../include/camera.hpp"
#include "../include/bvh.hpp"
#include "../include/ray.hpp"

int main() {
    int constexpr renderWidth = 100;
    int constexpr renderHeight = 100;
    vector3 constexpr cameraPosition = {0, 5, 5};
    int constexpr cameraFieldOfView = 90;
    float viewportDistance = 1;
    vector3 target = {0, 5, 0};
    vector3 v = {0, 1, 0};
    int bvhDepth = 50;

    const std::string imageFileName = "../renders/render.bmp";
    const std::string modelDirectory = "../models/strider/";
    const std::string modelFileName = "strider_tank.obj";
    const std::string textureFileName = "";
    
    cameraClass camera(cameraPosition, cameraFieldOfView, viewportDistance, v);

    textureStruct texture;
    

    if (!textureFileName.empty()) {
        textureFileClass::loadTexture(textureFileName, texture, modelDirectory);
    }


    std::vector<triangleStruct> triangleVector;
    std::map<std::string, materialStruct> materialMap;
    modelFileClass modelFile(modelFileName, triangleVector, materialMap, modelDirectory);
    
    threadPoolClass threadPool;
    
    bvhClass bvh(triangleVector, bvhDepth);
    std::vector<rayClass::rayStruct> rayVector = rayClass::initializeRays(target, camera, renderHeight, renderWidth, v);
    std::vector<pixelStruct> pixelVector = rayClass::renderImage(rayVector, renderWidth, renderHeight, triangleVector, materialMap, threadPool, bvh);


    renderFileClass renderFile(renderWidth, renderHeight, imageFileName);
    renderFile.write(pixelVector);
    renderFile.file.close();
    

    return 0;
}