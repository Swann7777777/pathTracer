class textureFileClass {

    public:

    #pragma pack(push, 1)

    struct headerStruct {
        uint16_t signature;
        uint32_t fileSize;
        uint32_t reserved;
        uint32_t dataOffset;
    };

    struct infoHeaderStruct {
        uint32_t size;
        int32_t width;
        int32_t height;
        int16_t planes;
        int16_t bitsPerPixel;
        uint32_t compression;
        uint32_t imageSize;
        int32_t xpixelsPerM;
        int32_t ypixelsPerM;
        uint32_t colorsUsed;
        uint32_t importantColors;
    };

    #pragma pack(pop)

    std::ifstream file;
    headerStruct header{};
    infoHeaderStruct infoHeader{};
    std::vector<pixelStruct> pixelVector;

    textureFileClass(std::string fileName) {

        std::string commandString = "cd ../models && convert " + fileName + " tmpTexture.bmp";
        char command[512];
        strcpy(command, commandString.c_str());
        system(command);
        
        file.open("../models/tmpTexture.bmp", std::ios::binary);
        
        if (!file) {
            std::cout << "Couldn't open converted texture file\n";
            std::exit(1);
        }

        file.read(reinterpret_cast<char*>(&header), sizeof(headerStruct));
        file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeaderStruct));

        file.seekg(header.dataOffset);

        bool rgba = false;

        if (infoHeader.bitsPerPixel == 32) {
            rgba = true;
        }

        int padding = (4 - ((infoHeader.width * (3 + rgba)) % 4) % 4) % 4;

        for (int i = 0; i < infoHeader.height; i++) {
            for (int j = 0; j < infoHeader.width; j++) {
                pixelStruct pixel;
                file.read(reinterpret_cast<char*>(&pixel), 3);
                if (rgba) {
                    file.ignore(1);
                }
                pixelVector.push_back(pixel);
            }
            file.ignore(padding);
        }

        // for (int i = 0; i < infoHeader.height; i++) {
        //     std::vector<pixelStruct> pixelRow(infoHeader.width);
        //     file.read(reinterpret_cast<char*>(pixelRow.data()), infoHeader.width * 3);
        //     file.ignore(padding);
        //     for (int j = 0; j < infoHeader.width; j++) {
        //         pixelVector[rowIndex * infoHeader.width + j] = pixelRow[j];
        //     }
        //     rowIndex++;
        // }

        file.close();
    }
};