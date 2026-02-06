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
#include "../include/modelFileHandler.hpp"
#include "../include/textureFileHandler.hpp"
#include "../include/renderFileHandler.hpp"
#include "../include/camera.hpp"
#include "../include/bvh.hpp"
#include "../include/ray.hpp"

int main() {
    int constexpr width = 1920/2.5;
    int constexpr height = 1080/1;
    vector3 constexpr cameraPosition = {0, 1.5, 2};
    int constexpr cameraFieldOfView = 90;
    float viewportDistance = 1;
    vector3 target = {0, 1.5, 0};
    vector3 v = {0, 1, 0};
    int bvhDepth = 30;
    const std::string imageFileName = "../renders/render.bmp";
    const std::string modelFileName = "../models/farquaad.obj";
    const std::string textureFileName = "../models/farquaad.png";
    cameraClass camera(cameraPosition, cameraFieldOfView, viewportDistance, v);
    

    std::vector<triangleStruct> triangleVector;
    std::map<std::string, materialStruct> materialMap;
    modelFileClass modelFile(modelFileName, triangleVector, materialMap);
    textureFileClass textureFile(textureFileName);
    
    threadPoolClass threadPool;
    
    bvhClass bvh(triangleVector, bvhDepth);
    std::vector<rayClass::rayStruct> rayVector = rayClass::initializeRays(target, camera, height, width, v);
    std::vector<pixelStruct> pixelVector = rayClass::renderImage(rayVector, width, height, triangleVector, textureFile.pixelVector,
        textureFile.infoHeader.width, textureFile.infoHeader.height, threadPool, bvh);


    renderFileClass renderFile(width, height, imageFileName);
    renderFile.write(pixelVector);
    renderFile.file.close();
    

    return 0;
}