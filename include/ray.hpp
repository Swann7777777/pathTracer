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

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                rayVector[i * width + j].origin = camera.position;
                rayVector[i * width + j].distance = std::numeric_limits<float>::max();
                rayVector[i * width + j].i = i;
                rayVector[i * width + j].j = j;
                rayVector[i * width + j].direction = (p1m + qx.scalar(j) + qy.scalar(i)).normalize();
            }
        }

        return rayVector;
    }

    bool checkIntersection(triangleClass &triangle, triangleClass &closestTriangle) {

        vector3 e1 = triangle.vertices[1] - triangle.vertices[0];
        vector3 e2 = triangle.vertices[2] - triangle.vertices[0];
        vector3 h = direction.crossProduct(e2);
        float a = e1.dotProduct(h);

        if (a > -0.0000001 && a < 0.0000001) {
            return false;
        }
        
        vector3 s = origin - triangle.vertices[0];

        float invA = 1/a;

        float u = (invA)*s.dotProduct(h);
        
        if (u > 1 || u < 0) {
            return false;
        }
        
        vector3 q = s.crossProduct(e1);
        float v = (invA)*direction.dotProduct(q);
        
        if (u + v > 1 || v < 0) {
            return false;
        }
        
        float t = (invA)*e2.dotProduct(q);
        
        if (t > 0) {
            if (t < distance) {
                distance = t;
                closestTriangle.u = u;
                closestTriangle.v = v;
                closestTriangle.w = 1 - (u + v);
                closestTriangle.texture = triangle.texture;
                return true;
            }
        }
        
        return false;
    }
    
    static std::vector<pixelStruct> renderImage(std::vector<rayClass> &rayVector, int width, int height, std::vector<triangleClass> &triangleVector,
        std::vector<pixelStruct> &texturePixelVector, int textureWidth, int textureHeight, threadPoolClass &threadPool){

        std::vector<pixelStruct> pixelVector(height * width, pixelStruct{160, 32, 240});

        std::vector<std::future<void>> results;

        int oldPercent = 0;

        for (auto ray : rayVector) {
            int percent = static_cast<int>(((ray.i * width + ray.j) / static_cast<float>(width * height)) * 100);
            if (percent != oldPercent) {
                oldPercent = percent;
                std::cout << percent << "% complete...\n";
            }

            auto task = std::make_shared<std::packaged_task<void()>>([&triangleVector, ray, textureWidth, &textureHeight, &pixelVector, &width, &texturePixelVector]() mutable {
                
                triangleClass closestTriangle;
                bool collision = false;

                for (auto &triangle : triangleVector) {
                    
                    if (ray.checkIntersection(triangle, closestTriangle)) {
                        collision = true;
                    }
                }

                if (collision) {
                    vector3 uvHit = closestTriangle.texture[0].scalar(closestTriangle.w) + closestTriangle.texture[1].scalar(closestTriangle.u) + closestTriangle.texture[2].scalar(closestTriangle.v);
                    float u = std::clamp(uvHit.x, 0.0f, 1.0f);
                    float v = std::clamp(uvHit.y, 0.0f, 1.0f);

                    size_t row = static_cast<size_t>(v * (textureHeight - 1));
                    size_t col = static_cast<size_t>(u * (textureWidth - 1));
                    size_t index = row * textureWidth + col;

                    pixelVector[ray.i * width + ray.j] = texturePixelVector[index];
                }
            });

            results.push_back(task->get_future());

            threadPool.enqueue([task]() { (*task)(); });
        }

        for (auto &f : results) {
            f.wait();
        }

        return pixelVector;
    }
};