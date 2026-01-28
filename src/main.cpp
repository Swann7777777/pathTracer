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



    int constexpr width = 7;
    int constexpr height = 4;
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
    
    
    cameraClass camera(cameraPosition, cameraFieldOfView, viewportDistance, v);

    vector3 t = target - camera.position;
    vector3 b = t.crossProduct(v);
    vector3 tn = t.normalize();
    vector3 bn = b.normalize();
    vector3 vn = tn.crossProduct(bn);

    float gx = camera.d * std::tan(camera.fieldOfView / 2);
    float gy = gx * (height - 1) / (width - 1);

    vector3 qx = bn.scalar(2*gx / (width - 1));
    vector3 qy = vn.scalar(2*gy / (height - 1));
    vector3 p1m = tn.scalar(camera.d) - bn.scalar(gx) - vn.scalar(gy);

    std::cout << "E = (" << cameraPosition.x << "," << cameraPosition.z << "," << cameraPosition.y << ")\n";
    std::cout << "T = (" << target.x << "," << target.z << "," << target.y << ")\n";

    std::vector<rayClass> rayVector(width * height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            rayVector[i * width + j].origin = camera.position;

            rayVector[i * width + j].direction = camera.position + (p1m + qx.scalar(j) + qy.scalar(i));

            std::cout << "vector(E,(" << rayVector[i * width + j].direction.x << "," << rayVector[i * width + j].direction.z << "," << rayVector[i * width + j].direction.y << "))\n";
        }
    }









    

    std::vector<pixelStruct> pixelVector(width * height);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            
            pixelVector[i * width + j].r = 0;
            pixelVector[i * width + j].g = 0;
            pixelVector[i * width + j].b = 0;
        }
    }






    imageFileClass imageFile(width, height, imageFileName);
    imageFile.write(pixelVector);
    imageFile.file.close();
    

    return 0;
}