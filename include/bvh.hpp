class bvhClass {
    public:

    struct bvhNodeStruct {

        vector3 minBound;
        vector3 maxBound;
        std::array<bvhNodeStruct*, 2> childs = {nullptr, nullptr};
        std::vector<triangleStruct*> triangles;

        bvhNodeStruct() {
            maxBound = {-INFINITY, -INFINITY, -INFINITY};
            minBound = {INFINITY, INFINITY, INFINITY};
        }


        void grow(vector3 point) {
            
            minBound.x = std::min(minBound.x, point.x);
            minBound.y = std::min(minBound.y, point.y);
            minBound.z = std::min(minBound.z, point.z);
            maxBound.x = std::max(maxBound.x, point.x);
            maxBound.y = std::max(maxBound.y, point.y);
            maxBound.z = std::max(maxBound.z, point.z);
        }

        void split() {

            childs[0] = new bvhNodeStruct();
            childs[1] = new bvhNodeStruct();

            float w = maxBound.x - minBound.x;
            float h = maxBound.y - minBound.y;
            float l = maxBound.z - minBound.z;

            vector3 middleMinBound;
            vector3 middleMaxBound;

            if (w > h && w > l) {

                float middleX = (minBound.x + maxBound.x) / 2;
                middleMinBound = {middleX, minBound.y, minBound.z};
                middleMaxBound = {middleX, maxBound.y, maxBound.z};
            }

            else if (h > w && h > l) {

                float middleY = (minBound.y + maxBound.y) / 2;
                middleMinBound = {minBound.x, middleY, minBound.z};
                middleMaxBound = {maxBound.x, middleY, maxBound.z};
            }

            else {

                float middleZ = (minBound.z + maxBound.z) / 2;
                middleMinBound = {minBound.x, minBound.y, middleZ};
                middleMaxBound = {maxBound.x, maxBound.y, middleZ};
            }

            childs[0]->minBound = minBound;
            childs[0]->maxBound = middleMaxBound;
            childs[1]->minBound = middleMinBound;
            childs[1]->maxBound = maxBound;
        }

        bool checkInBound(vector3 &point) {
            if (point.x > maxBound.x || point.y > maxBound.y || point.z > maxBound.z) {
                return false;
            }

            return true;
        }
    };

    bvhNodeStruct root;

    bvhClass(std::vector<triangleStruct> &triangleVector, int &maxDepth) {

        for (auto& triangle : triangleVector) {
            root.triangles.push_back(&triangle);
        }

        for (auto* triangle : root.triangles) {
            for (auto& vertice : triangle->vertices) {
                root.grow(*vertice);
            }
        }

        buildChilds(&root, 0, maxDepth);
    }

    void buildChilds(bvhNodeStruct* node, int currentDepth, const int &maxDepth) {

        if (node->triangles.size() == 0) {
            return;
        }

        node->split();

        for (auto* triangle : node->triangles) {
            vector3 triangleAverage = (*triangle->vertices[0] + *triangle->vertices[1] + *triangle->vertices[2]) / 3;

            if (node->childs[0]->checkInBound(triangleAverage)) {
                node->childs[0]->triangles.push_back(triangle);
            }

            else {
                node->childs[1]->triangles.push_back(triangle);
            }
        }

        for (int i = 0; i < 2; i++) {
            for (auto* triangle : node->childs[i]->triangles) {
                for (auto& vertice : triangle->vertices) {
                    node->childs[i]->grow(*vertice);
                }
            }
        }

        currentDepth++;

        if (currentDepth < maxDepth) {
            buildChilds(node->childs[0], currentDepth, maxDepth);
            buildChilds(node->childs[1], currentDepth, maxDepth);
        }
    }
};