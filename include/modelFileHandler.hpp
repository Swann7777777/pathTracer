class modelFileClass {
    public:

    struct objectStruct {
        std::vector<std::vector<vector3>> triangles;
    };

    std::vector<vector3> geometricVertices;
    std::vector<vector3> textureCoordinates;
    std::vector<vector3> vertexNormals;
    std::vector<objectStruct> objects;


    void verticeLoading(std::istringstream &lineStream, std::string &line) {

        float value;
        std::vector<float> tmp;

        while (lineStream >> value) {
                
            tmp.push_back(value);
        }

        if (tmp.size() != 3) {
            std::cout << "Unknown geometric vertice value in model file.\n";
            std::cout << line << "\n";
            exit(1);
        }
            
        geometricVertices.push_back({tmp[0], tmp[1], tmp[2]});
    }


    void textureLoading(std::istringstream &lineStream, std::string &line) {

        float value;
        std::vector<float> tmp;

        while (lineStream >> value) {
            
            tmp.push_back(value);
        }
        
        if (tmp.size() != 2) {
            std::cout << "Unknown texture coordinate value in model file.\n";
            std::cout << line << "\n";
            exit(1);
        }

        textureCoordinates.push_back({tmp[0], tmp[1], 0});
    }

    void normalLoading(std::istringstream &lineStream, std::string &line) {

        float value;
        std::vector<float> tmp;

        while (lineStream >> value) {
            tmp.push_back(value);
        }
        
        if (tmp.size() != 3) {
            std::cout << "Unknown vertex normal value in model file.\n";
            std::cout << line << "\n";
            exit(1);
        }
        
        vertexNormals.push_back({tmp[0], tmp[1], tmp[2]});
    }

    void faceLoading(std::istringstream &lineStream, std::string &line, objectStruct &tmpObject, std::vector<triangleStruct> &triangleVector, materialStruct* currentMaterial) {

        char delim = '/';
        
        std::string tmpStr;
        std::string valueStr;
        float value;
        std::vector<float> tmp;
        std::vector<vector3> tmpTriangleIndices;
        
        while (lineStream >> tmpStr) {
            
            std::istringstream ss1(tmpStr);
            
            while (std::getline(ss1, valueStr, delim)) {
                if (!valueStr.empty()) {
                    value = std::stof(valueStr);
                    tmp.push_back(value);
                }
            }

            if (tmp.size() != 3) {
                std::cout << "Unknown triangle value in model file.\n";
                std::cout << line << "\n";
                exit(1);
            }

            tmpTriangleIndices.push_back({tmp[0], tmp[1], tmp[2]});
        }
        
        if (tmpTriangleIndices.size() != 3) {
            std::cout << "Unknown triangle value in model file.\n";
            std::cout << line << "\n";
            exit(1);
        }

        std::array<vector3*, 3> vertices = {&geometricVertices[tmpTriangleIndices[0].x - 1], &geometricVertices[tmpTriangleIndices[1].x - 1], &geometricVertices[tmpTriangleIndices[2].x - 1]};
        std::array<vector3*, 3> texture = {&textureCoordinates[tmpTriangleIndices[0].y - 1], &textureCoordinates[tmpTriangleIndices[1].y - 1], &textureCoordinates[tmpTriangleIndices[2].y - 1]};
        vector3* normal = &vertexNormals[tmpTriangleIndices[0].z];

        triangleStruct tmpTriangle;
        tmpTriangle.vertices = vertices;
        tmpTriangle.texture = texture;
        tmpTriangle.normal = normal;
        tmpTriangle.material = currentMaterial;

        triangleVector.push_back(tmpTriangle);
    }



    void loadMtlFile(std::string fileName, std::map<std::string, materialStruct> materialMap) {

        std::ifstream file(fileName);

        if (!file) {
            std::cout << "Couldn't open the material file.\n";
            exit(1);
        }

        std::string line;
        std::string prefix;
        materialStruct tmpMaterial;
        std::string materialName;
        std::vector<float> tmp;
        float value;

        while (getline(file, line)) {

            if (line.empty()) {
                continue;
            }

            std::istringstream lineStream(line);

            lineStream >> prefix;

            if (prefix == "newmtl" && !materialName.empty()) {
                materialMap[materialName] = tmpMaterial;
                tmpMaterial = {};
                lineStream >> materialName;
            }

            else if (prefix == "Ka") {
                
                while (lineStream >> value) {
                    tmp.push_back(value);
                }

                tmpMaterial.ambientColor = {tmp[0], tmp[1], tmp[2]};
            }

            else if (prefix == "Kd") {

                while (lineStream >> value) {
                    tmp.push_back(value);
                }

                tmpMaterial.diffuseColor = {tmp[0], tmp[1], tmp[2]};
            }

            else if (prefix == "Ks") {

                while (lineStream >> value) {
                    tmp.push_back(value);
                }

                tmpMaterial.specularColor = {tmp[0], tmp[1], tmp[2]};
            }

            else if (prefix == "Ns") {

                lineStream >> value;

                tmpMaterial.specularWeight = value;
            }

            else if (prefix == "d") {

                lineStream >> value;

                tmpMaterial.dissolvance = value;
            }

            else if (prefix == "Tr") {

                lineStream >> value;

                tmpMaterial.dissolvance = 1 - value;
            }

            else if (prefix == "Tf") {

                while (lineStream >> value) {
                    tmp.push_back(value);
                }

                tmpMaterial.transmissionColor = {tmp[0], tmp[1], tmp[2]};
            }

            else if (prefix == "Ni") {

                lineStream >> value;

                tmpMaterial.opticalDensity = value;
            }


            tmp.clear();
        }

        materialMap[materialName] = tmpMaterial;
    }



    modelFileClass(std::string fileName, std::vector<triangleStruct> &triangleVector, std::map<std::string, materialStruct> &materialMap) {

        std::ifstream file(fileName);

        if (!file) {
            std::cout << "Couldn't open the model file.\n";
            exit(1);
        }

        std::string line;
        objectStruct tmpObject;
        std::string prefix;
        std::string materialName;
        materialStruct* currentMaterial;
        

        while (getline(file, line)) {

            if (line.empty()) {
                continue;
            }

            std::istringstream lineStream(line);

            lineStream >> prefix;

            if (prefix == "mtllib") {
                std::string mtlFileName;
                lineStream >> mtlFileName;
                loadMtlFile(mtlFileName, materialMap);
            }

            else if (prefix == "usemtl") {
                lineStream >> materialName;
                currentMaterial = &materialMap[materialName];
            }

            else if (prefix == "o" && !tmpObject.triangles.empty()) {

                objects.push_back(tmpObject);
                tmpObject = {};
            }

            else if (prefix == "v") {
                verticeLoading(lineStream, line);
            }
            
            else if (prefix == "vt") {
                textureLoading(lineStream, line);
            }
            
            else if (prefix == "vn") {
                normalLoading(lineStream, line);
            }
            
            else if (prefix == "f") {
                faceLoading(lineStream, line, tmpObject, triangleVector, currentMaterial);
            }
        }

        objects.push_back(tmpObject);

        file.close();
    }
};