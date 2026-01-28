class modelFileClass {
    public:

    struct objectStruct {

        std::vector<vector3> geometricVertices;
        std::vector<vector2> textureCoordinates;
        std::vector<vector3> vertexNormals;
        std::vector<std::vector<vector3>> faces;
    };



    std::ifstream file;

    std::vector<objectStruct> objects;

    void loadModel(std::string fileName) {
        
        file.open(fileName);

        if (!file) {
            std::cout << "Couldn't open the model file.\n";
            exit(1);
        }

        std::string line;
        float value;
        std::vector<float> tmp;
        objectStruct tmpObject;
        std::string prefix;
        

        while (getline(file, line)) {

            if (line.empty()) {
                continue;
            }

            tmp.clear();

            std::istringstream lineStream(line);

            lineStream >> prefix;

            if (prefix == "o" && !tmpObject.faces.empty()) {

                objects.push_back(tmpObject);
                tmpObject = {};
            }

            if (prefix == "v") {
                
                while (lineStream >> value) {
                    
                    tmp.push_back(value);
                }

                if (tmp.size() < 3 || tmp.size() > 4) {
                    std::cout << "Incorrect geometric vertice value in model file.\n";
                    exit(1);
                }

                tmpObject.geometricVertices.push_back({tmp[0], tmp[1], tmp[2]});
            }

            else if (prefix == "vt") {

                while (lineStream >> value) {
                    
                    tmp.push_back(value);
                }

                if (tmp.size() != 2) {
                    std::cout << "Incorrect texture coordinate value in model file.\n";
                    exit(1);
                }

                tmpObject.textureCoordinates.push_back({tmp[0], tmp[1]});
            }

            else if (prefix == "vn") {

                while (lineStream >> value) {
                    tmp.push_back(value);
                }

                if (tmp.size() < 1 || tmp.size() > 3) {
                    std::cout << "Incorrect vertex normal value in model file.\n";
                    exit(1);
                }

                tmpObject.vertexNormals.push_back({tmp[0], tmp[1], tmp[2]});
            }

            else if (prefix == "f") {

                char delim = '/';

                std::string tmpStr;
                std::string valueStr;
                std::vector<vector3> tmpFaces;

                while (lineStream >> tmpStr) {

                    std::istringstream ss1(tmpStr);

                    while (std::getline(ss1, valueStr, delim)) {
                        if (!valueStr.empty()) {
                            value = std::stof(valueStr);
                            tmp.push_back(value);
                        }
                    }

                    if (tmp.size() < 1 || tmp.size() > 3) {
                        std::cout << "Incorrect face value in model file.\n";
                        exit(1);
                    }

                    tmpFaces.push_back({tmp[0], tmp[1], tmp[2]});
                    tmp.clear();
                    tmpStr = "";
                }

                if (tmpFaces.size() != 3) {
                    std::cout << "Incorrect face value in model file.\n";
                    exit(1);
                }

                tmpObject.faces.push_back({tmpFaces[0], tmpFaces[1], tmpFaces[2]});
            }
        }

        objects.push_back(tmpObject);
    }

    void loadTexture() {
        
    }
};