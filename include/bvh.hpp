class bvhClass {

    struct bvhNodeStruct {

        float x, y, z;
        float w, h, l;
        std::array<bvhNodeStruct*, 2> childs;
        std::vector<triangleClass*> triangles;

        bvhNodeStruct() {
            x = std::numeric_limits<float>::min();
            y = std::numeric_limits<float>::min();
            z = std::numeric_limits<float>::min();
            w = 0;
            h = 0;
            l = 0;
            childs[0] = nullptr;
            childs[1] = nullptr;
        }
    };

    bvhNodeStruct root;

    void generateTree(std::vector<triangleClass> &triangleVector) {

        root = bvhNodeStruct();

        for (auto& triangle : triangleVector) {
            root.triangles.push_back(&triangle);
        }

        bvhNodeStruct* currentNode = &root;

        for (auto* triangle : currentNode->triangles) {
            for (auto& vertice : triangle->vertices) {

                if (vertice.x < currentNode->x) {
                    currentNode->x = vertice.x;
                }

                if (vertice.x > currentNode->x + currentNode->w) {
                    currentNode->w = vertice.x - currentNode->x;
                }

                if (vertice.y < currentNode->y) {
                    currentNode->y = vertice.y;
                }

                if (vertice.y > currentNode->y + currentNode->h) {
                    currentNode->h = vertice.y - currentNode->y;
                }

                if (vertice.z < currentNode->z) {
                    currentNode->z = vertice.z;
                }

                if (vertice.z > currentNode->z + currentNode->l) {
                    currentNode->l = vertice.z;
                }
            }
        }

        for (auto* triangle : currentNode->triangles) {
            vector3 triangleAverage = (triangle->vertices[0] + triangle->vertices[1] + triangle->vertices[2]) / 3;
            if (triangleAverage.x < currentNode->x + (currentNode->w / 2)) {
                currentNode->childs[0]->triangles.push_back(triangle);
            }

            // And so on...
        }
    }
};