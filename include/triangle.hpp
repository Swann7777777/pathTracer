class triangleClass {
    public:

    std::array<vector3, 3> vertices;
    std::array<vector2, 3> texture;
    vector3 normal;

    static std::vector<triangleClass> generateTriangles(const modelFileClass &modelFile) {

        std::vector<triangleClass> triangleVector;
    
        for (const auto &object : modelFile.objects) {
            for (const auto &triangle : object.triangles) {
                
                triangleClass tmpTriangle;
                
                tmpTriangle.vertices = {modelFile.geometricVertices[triangle[0].x - 1], modelFile.geometricVertices[triangle[1].x - 1], modelFile.geometricVertices[triangle[2].x - 1]};
                tmpTriangle.texture = {modelFile.textureCoordinates[triangle[0].y - 1], modelFile.textureCoordinates[triangle[1].y - 1], modelFile.textureCoordinates[triangle[2].y - 1]};
                //tmpTriangle.normal = object.vertexNormals[triangle[0].z - 1];
                
                triangleVector.push_back(tmpTriangle);
            }
        }

        return triangleVector;
    }
};