class fileStreamClass {
    public:

        #pragma pack(push, 1) // Prevent padding

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

        struct pixelDataStruct { // Move that ?
            uint8_t b;
            uint8_t g;
            uint8_t r;
        };
        
        headerStruct header{};
        infoHeaderStruct infoHeader{};


        fileStreamClass(int width, int height) {

            header.signature = 0x4D42;
            header.reserved = 0;

            infoHeader.size = 40;
            infoHeader.width = width;
            infoHeader.height = height;
            infoHeader.planes = 1;
            infoHeader.bitsPerPixel = 8;
            infoHeader.compression = 0;
            infoHeader.imageSize = 0;
            infoHeader.xpixelsPerM = 0;
            infoHeader.ypixelsPerM = 0;
            infoHeader.colorsUsed = 0;
            infoHeader.importantColors = 0;
        }
};