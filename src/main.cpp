#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <cmath>
#include "../include/vectors.hpp"
#include "../include/imageFileHandler.hpp"
#include "../include/modelFileHandler.hpp"
#include "../include/camera.hpp"
#include "../include/ray.hpp"


class triangleClass {
    public:

    std::vector<vector3> vertices;
    std::vector<vector2> texture;
    vector3 normal;

    triangleClass() {

        vertices.reserve(3);
        texture.reserve(3);
    }
};

int main() {



    int constexpr width = 255;
    int constexpr height = 255;
    vector3 constexpr cameraPosition = {-3, 0, 0};
    int constexpr cameraFieldOfView = 90;
    float viewportDistance = 1;
    vector3 target = {0, 0, 0};
    vector3 v = {0, 1, 0};
    const std::string imageFileName = "../renders/render.bmp";
    const std::string modelFileName = "../models/cube.obj";
    

    modelFileClass modelFile;
    modelFile.loadModel(modelFileName);
    modelFile.file.close();
    
    
    
    std::vector<triangleClass> triangleVector;
    
    for (const auto &object : modelFile.objects) {
        for (const auto &face : object.faces) {
            
            triangleClass tmpFace;
            
            tmpFace.vertices = {object.geometricVertices[face[0].x - 1], object.geometricVertices[face[1].x - 1], object.geometricVertices[face[2].x - 1]};
            tmpFace.texture = {object.textureCoordinates[face[0].y - 1], object.textureCoordinates[face[1].y - 1], object.textureCoordinates[face[2].y - 1]};
            tmpFace.normal = object.vertexNormals[face[0].z - 1];
            
            
            triangleVector.push_back(tmpFace);
        }
    }
    
    
    cameraClass camera(cameraPosition, cameraFieldOfView, viewportDistance, v);


    std::vector<rayClass> rayVector(width * height);
    rayClass::initializeRays(target, camera, height, width, v, rayVector);
    std::vector<pixelStruct> pixelVector(width * height);

    for (auto &ray : rayVector) {
        for (const auto &triangle : triangleVector) {
            if (ray.checkIntersection(triangle)) {

                pixelVector[ray.i * width + ray.j] = {255, 255, 255};
            }
        }
    }



    imageFileClass imageFile(width, height, imageFileName);
    imageFile.write(pixelVector);
    imageFile.file.close();
    

    return 0;
}