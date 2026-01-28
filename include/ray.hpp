class rayClass {
    public:

    vector3 origin;
    vector3 direction;
    float distance;
    int i;
    int j;

    static std::vector<rayClass> initializeRays(vector3 target, cameraClass camera, int height, int width, vector3 v) {

        std::vector<rayClass> rayVector(width * height);

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

        //std::cout << "E = (" << camera.position.x << "," << camera.position.z << "," << camera.position.y << ")\n";
        //std::cout << "T = (" << target.x << "," << target.z << "," << target.y << ")\n";

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {

                rayVector[i * width + j].origin = camera.position;
                rayVector[i * width + j].distance = std::numeric_limits<float>::max();
                rayVector[i * width + j].i = i;
                rayVector[i * width + j].j = j;

                rayVector[i * width + j].direction = (p1m + qx.scalar(i) + qy.scalar(j));

                //std::cout << "vector(E,(" << rayVector[i * width + j].direction.x << "," << rayVector[i * width + j].direction.z << "," << rayVector[i * width + j].direction.y << "))\n";
            }
        }

        return rayVector;
    }

    bool checkIntersection(const triangleClass &triangle) {

        vector3 e1 = triangle.vertices[1] - triangle.vertices[0];
        vector3 e2 = triangle.vertices[2] - triangle.vertices[0];
        vector3 h = direction.crossProduct(e2);
        float a = e1.dotProduct(h);

        if (a > -0.001 && a < 0.001) {
            return false;
        }
        
        vector3 s = origin - triangle.vertices[0];
        float u = (1/a)*s.dotProduct(h);
        
        if (u > 1 || u < 0) {
            return false;
        }
        
        vector3 q = s.crossProduct(e1);
        float v = (1/a)*direction.dotProduct(q);
        
        if (u + v > 1 || v < 0) {
            return false;
        }
        
        float t = (1/a)*e2.dotProduct(q);
        
        if (t > 0) {
            if (t < distance) {
                distance = t;
            }

            return true;
        }
        
        return false;
    }

    static std::vector<pixelStruct> renderImage(std::vector<rayClass> &rayVector, int width, int height, std::vector<triangleClass> &triangleVector) {

        std::vector<pixelStruct> pixelVector(height * width);


        float coefficient = 0.01;

        int oldPercent = 0;

        for (auto &ray : rayVector) {
            int percent = std::round(((ray.i * width + ray.j) / static_cast<float>(width * height)) * 100);
            if (percent != oldPercent) {
                oldPercent = percent;
                std::cout << percent << "% complete...\n";
            }

            for (const auto &triangle : triangleVector) {


                ray.checkIntersection(triangle);
                
            }

            uint8_t color = static_cast<uint8_t>((255/(ray.distance * coefficient)));

            pixelVector[ray.i * width + ray.j] = {color, color, color};
        }

        return pixelVector;
    }
};