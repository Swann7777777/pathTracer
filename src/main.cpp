#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <math.h>
#include "../include/imageFileHandler.hpp"
#include "../include/modelFileHandler.hpp"


struct pixelStruct {

    uint8_t b, g, r;
};

class faceClass {
    public:

        std::vector<vector3> vertices;
        std::vector<vector2> texture;
        std::vector<vector3> normal;

        faceClass() {

            vertices.reserve(3);
            texture.reserve(3);
            normal.reserve(3);
        }
};

int main() {

    int constexpr width = 255;
    int constexpr height = 255;
    const std::string imageFileName = "../renders/render.bmp";
    const std::string modelFileName = "../models/cube.obj";
    
    imageFileClass imageFile(width, height, imageFileName);
    modelFileClass modelFile(modelFileName);

    std::vector<pixelStruct> pixelVector(width * height);

    std::vector<faceClass> faces;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            pixelVector[i * width + j].r = i;
            pixelVector[i * width + j].g = i;
            pixelVector[i * width + j].b = i;
        }
    }


    imageFile.file.write(reinterpret_cast<char*>(&imageFile.header), sizeof(imageFile.header));
    imageFile.file.write(reinterpret_cast<char*>(&imageFile.infoHeader), sizeof(imageFile.infoHeader));

    std::vector<char> paddingVector(imageFile.padding, 0);

    for (int i = 0; i < height; i++) {
        imageFile.file.write(reinterpret_cast<char*>(pixelVector.data() + i * width), width * sizeof(pixelStruct));
        imageFile.file.write(paddingVector.data(), imageFile.padding);
    }

    imageFile.file.close();
    modelFile.file.close();
    
    for (const auto &object : modelFile.objects) {
        for (const auto &face : object.faces) {

            faceClass tmpFace;

            tmpFace.vertices = {object.geometricVertices[face[0].x - 1], object.geometricVertices[face[1].x - 1], object.geometricVertices[face[2].x - 1]};
            tmpFace.texture = {object.textureCoordinates[face[0].y - 1], object.textureCoordinates[face[1].y - 1], object.textureCoordinates[face[2].y - 1]};
            tmpFace.normal = {object.vertexNormals[face[0].z - 1], object.vertexNormals[face[1].z - 1], object.vertexNormals[face[2].z - 1]};


            faces.push_back(tmpFace);
        }
    }
    
    return 0;
}