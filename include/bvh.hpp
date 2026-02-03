class bvhClass {
    public:

    struct bvhNodeStruct {

        vector3 minBound;
        vector3 maxBound;
        std::array<bvhNodeStruct*, 2> childs = {nullptr, nullptr};
        std::vector<triangleClass*> triangles;



        void grow(vector3 point) {
            
            minBound.x = std::min(minBound.x, point.x);
            minBound.y = std::min(minBound.y, point.y);
            minBound.z = std::min(minBound.z, point.z);
            maxBound.x = std::max(maxBound.x, point.x);
            maxBound.y = std::max(maxBound.y, point.y);
            maxBound.z = std::max(maxBound.z, point.z);
        }

        std::array<std::array<vector3, 2>, 2> split() {

            float w = maxBound.x - minBound.x;
            float h = maxBound.y - minBound.y;
            float l = maxBound.z - minBound.z;

            if (w > h && w > l) {

                float middleX = (minBound.x + maxBound.x) / 2;
                vector3 middleBound = {middleX, maxBound.y, maxBound.z};

                return {{
                    {minBound, middleBound},
                    {middleBound, maxBound}
                }};
            }

            if (h > w && h > l) {

                float middleY = (minBound.y + maxBound.y) / 2;
                vector3 middleBound = {maxBound.x, middleY, maxBound.z};

                return {{
                    {minBound, middleBound},
                    {middleBound, maxBound}
                }};
            }

            // TO DO !!!
        }
    };

    bvhNodeStruct root;

    void generateTree(std::vector<triangleClass> &triangleVector, int &depth) {

        for (auto& triangle : triangleVector) {
            root.triangles.push_back(&triangle);
        }

        root.maxBound = {INFINITY, INFINITY, INFINITY};
        root.minBound = {-INFINITY, -INFINITY, -INFINITY};

        bvhNodeStruct* currentNode = &root;




        for (auto* triangle : currentNode->triangles) {
            for (auto& vertice : triangle->vertices) {
                currentNode->grow(vertice);
            }
        }


    }
};