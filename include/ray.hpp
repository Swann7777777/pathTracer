class rayClass {
    public:

    vector3 origin;
    vector3 direction;
    int i;
    int j;

    static void initializeRays(vector3 target, cameraClass camera, int height, int width, vector3 v, std::vector<rayClass> &rayVector) {

        vector3 t = target - camera.position;
        vector3 b = t.crossProduct(v);
        vector3 tn = t.normalize();
        vector3 bn = b.normalize();
        vector3 vn = tn.crossProduct(bn);

        float gx = camera.d * std::tan(camera.fieldOfView / 2);
        float gy = gx * (height - 1) / (width - 1);

        vector3 qx = bn.scalar(2*gx / (width - 1));
        vector3 qy = vn.scalar(2*gy / (height - 1));
        vector3 p1m = tn.scalar(camera.d) - bn.scalar(gx) - vn.scalar(gy);

        std::cout << "E = (" << camera.position.x << "," << camera.position.z << "," << camera.position.y << ")\n";
        std::cout << "T = (" << target.x << "," << target.z << "," << target.y << ")\n";

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {

                rayVector[i * width + j].origin = camera.position;
                rayVector[i * width + j].i = i;
                rayVector[i * width + j].j = j;

                rayVector[i * width + j].direction = camera.position + (p1m + qx.scalar(j) + qy.scalar(i));

                std::cout << "vector(E,(" << rayVector[i * width + j].direction.x << "," << rayVector[i * width + j].direction.z << "," << rayVector[i * width + j].direction.y << "))\n";
            }
        }
    }

    bool checkIntersection(triangleClass triangle) {

        if (direction.dotProduct(triangle.normal) == 0) {
            return false;
        }

        return false;
    }
};