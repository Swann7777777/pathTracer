#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <math.h>
#include "../include/fileStream.hpp"


struct pixelStruct {

    uint8_t b, g, r;
};

int main() {

    int constexpr width = 255;
    int constexpr height = 255;
    std::string filename = "renders/render.bmp";
    
    fileStreamClass fileStream(width, height, filename);

    std::vector<pixelStruct> pixelVector(width * height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            pixelVector[i * width + j].r = 0;
            pixelVector[i * width + j].b = 0;
            pixelVector[i * width + j].g = 0;
        }
    }


    fileStream.file.write(reinterpret_cast<char*>(&fileStream.header), sizeof(fileStream.header));
    fileStream.file.write(reinterpret_cast<char*>(&fileStream.infoHeader), sizeof(fileStream.infoHeader));

    std::vector<char> paddingVector(fileStream.padding, 0);

    for (int i = 0; i < height; i++) {
        fileStream.file.write(reinterpret_cast<char*>(pixelVector.data() + i * width), width * sizeof(pixelStruct));
        fileStream.file.write(paddingVector.data(), fileStream.padding);
    }

    fileStream.file.close();


    return 0;
}