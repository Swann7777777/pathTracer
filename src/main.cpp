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

class polygonClass {

    public:

};


class faceClass {
    public:

        std::vector<vector3> vertices;
        std::vector<vector2> texture;
        vector3 normal;

        faceClass() {

            vertices.reserve(3);
            texture.reserve(3);
        }
};

int main() {



    int constexpr width = 1920;
    int constexpr height = 1080;
    vector3 constexpr cameraPosition = {-3, 0.5, 0};
    vector3 constexpr cameraAngle = {0, 0, 0};
    int constexpr cameraFieldOfView = 90;
    const std::string imageFileName = "../renders/render.bmp";
    const std::string modelFileName = "../models/cube.obj";
    

    modelFileClass modelFile;
    modelFile.loadModel(modelFileName);
    modelFile.file.close();
    
    
    
    std::vector<faceClass> faces;
    
    for (const auto &object : modelFile.objects) {
        for (const auto &face : object.faces) {
            
            faceClass tmpFace;
            
            tmpFace.vertices = {object.geometricVertices[face[0].x - 1], object.geometricVertices[face[1].x - 1], object.geometricVertices[face[2].x - 1]};
            tmpFace.texture = {object.textureCoordinates[face[0].y - 1], object.textureCoordinates[face[1].y - 1], object.textureCoordinates[face[2].y - 1]};
            tmpFace.normal = object.vertexNormals[face[0].z - 1];
            
            
            faces.push_back(tmpFace);
        }
    }
    
    
    cameraClass camera(cameraPosition, cameraAngle, cameraFieldOfView);



    std::vector<rayClass> rayVector(width * height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            rayVector[i * width + j].origin = camera.position_;

            vector2 p;


            rayVector[i * width + j].direction = {};
        }
    }









    

    std::vector<pixelStruct> pixelVector(width * height);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            
            pixelVector[i * width + j].r = j*255/1920;
            pixelVector[i * width + j].g = j*255/1920;
            pixelVector[i * width + j].b = j*255/1920;
        }
    }




    imageFileClass imageFile(width, height, imageFileName);
    imageFile.write(pixelVector);
    imageFile.file.close();
    

    return 0;
}