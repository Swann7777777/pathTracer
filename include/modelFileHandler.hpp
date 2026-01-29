class modelFileClass {
    public:

    struct objectStruct {
        std::vector<std::vector<vector3>> triangles;
    };

    std::vector<vector3> geometricVertices;
    std::vector<vector2> textureCoordinates;
    std::vector<vector3> vertexNormals;

    std::ifstream file;

    std::vector<objectStruct> objects;

    modelFileClass(std::string fileName) {
        
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

            if (prefix == "o" && !tmpObject.triangles.empty()) {

                objects.push_back(tmpObject);
                tmpObject = {};
            }

            if (prefix == "v") {
                
                while (lineStream >> value) {
                    
                    tmp.push_back(value);
                }

                if (tmp.size() != 3) {
                    std::cout << line << "\n";
                    std::cout << "Incorrect geometric vertice value in model file.\n";
                    exit(1);
                }
                
                geometricVertices.push_back({tmp[0], tmp[1], tmp[2]});
            }
            
            else if (prefix == "vt") {
                
                while (lineStream >> value) {
                    
                    tmp.push_back(value);
                }
                
                if (tmp.size() != 2) {
                    std::cout << line << "\n";
                    std::cout << "Incorrect texture coordinate value in model file.\n";
                    exit(1);
                }

                textureCoordinates.push_back({tmp[0], tmp[1]});
            }
            
            else if (prefix == "vn") {
                
                while (lineStream >> value) {
                    tmp.push_back(value);
                }
                
                if (tmp.size() != 3) {
                    std::cout << "Incorrect vertex normal value in model file.\n";
                    exit(1);
                }
                
                vertexNormals.push_back({tmp[0], tmp[1], tmp[2]});
            }
            
            else if (prefix == "f") {
                
                char delim = '/';
                
                std::string tmpStr;
                std::string valueStr;
                std::vector<vector3> tmpTriangles;
                
                while (lineStream >> tmpStr) {
                    
                    std::istringstream ss1(tmpStr);
                    
                    while (std::getline(ss1, valueStr, delim)) {
                        if (!valueStr.empty()) {
                            value = std::stof(valueStr);
                            tmp.push_back(value);
                        }
                    }
                    
                    if (tmp.size() == 2) {
                        tmpTriangles.push_back({tmp[0], tmp[1], -1});
                    }

                    else if (tmp.size() == 3) {
                        tmpTriangles.push_back({tmp[0], tmp[1], tmp[2]});
                    }

                    else {
                        std::cout << "Incorrect triangle value in model file.\n";
                        std::cout << line << "\n";
                        exit(1);
                    }
                    
                    tmp.clear();
                    tmpStr = "";
                }
                
                if (tmpTriangles.size() != 3) {
                    std::cout << "Incorrect triangle value in model file.\n";
                    exit(1);
                }

                tmpObject.triangles.push_back({tmpTriangles[0], tmpTriangles[1], tmpTriangles[2]});
            }
        }

        objects.push_back(tmpObject);

        file.close();
    }
};