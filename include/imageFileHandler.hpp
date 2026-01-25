class imageFileClass {
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
        
        headerStruct header{};
        infoHeaderStruct infoHeader{};

        int padding;
        std::ofstream file;


        imageFileClass(int width, int height, std::string fileName) {

            file.open(fileName, std::ios::binary);

            if (!file) {
                std::cout << "Couldn't open the render file.\n";
                exit(1);
            }

            padding = (4 - ((width * 3) % 4) % 4);

            header.signature = 0x4D42;
            header.fileSize = 54 + (24 * width + 8 * padding) * height;
            header.reserved = 0;
            header.dataOffset = 54;

            infoHeader.size = 40;
            infoHeader.width = width;
            infoHeader.height = height;
            infoHeader.planes = 1;
            infoHeader.bitsPerPixel = 24;
            infoHeader.compression = 0;
            infoHeader.imageSize = (width * 3 + padding) *height;
            infoHeader.xpixelsPerM = 0;
            infoHeader.ypixelsPerM = 0;
            infoHeader.colorsUsed = 0;
            infoHeader.importantColors = 0;
        }
};