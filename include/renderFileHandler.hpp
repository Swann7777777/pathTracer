class renderFileClass {
    public:
        
    textureFileClass::headerStruct header{};
    textureFileClass::infoHeaderStruct infoHeader{};

    int padding;
    std::ofstream file;

    int width_;
    int height_;


    
    
    renderFileClass(int width, int height, std::string fileName) {
        
        width_ = width;
        height_ = height;
        
        file.open(fileName, std::ios::binary);
        
        if (!file) {
            std::cout << "Couldn't open the render file.\n";
            exit(1);
        }
        
        padding = (4 - ((width_ * 3) % 4) % 4) % 4;
        
        header.signature = 0x4D42;
        header.fileSize = 54 + (24 * width_ + 8 * padding) * height_;
        header.reserved = 0;
        header.dataOffset = 54;
        
        infoHeader.size = 40;
        infoHeader.width = width_;
        infoHeader.height = -height_;
        infoHeader.planes = 1;
        infoHeader.bitsPerPixel = 24;
        infoHeader.compression = 0;
        infoHeader.imageSize = (width_ * 3 + padding) * height_;
        infoHeader.xpixelsPerM = 0;
        infoHeader.ypixelsPerM = 0;
        infoHeader.colorsUsed = 0;
        infoHeader.importantColors = 0;
    }


    void write(std::vector<pixelStruct> pixelVector) {

        file.write(reinterpret_cast<char*>(&header), sizeof(header));
        file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

        std::vector<char> paddingVector(padding, 0);

        for (int i = 0; i < height_; i++) {
            file.write(reinterpret_cast<char*>(pixelVector.data() + i * width_), width_ * sizeof(pixelStruct));
            file.write(paddingVector.data(), padding);
        }
    }
    };