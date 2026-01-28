struct vector3 {

    float x, y, z;

    vector3 operator+(const vector3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    vector3 operator-(const vector3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    vector3 operator*(const vector3& other) const {
        return {x*other.x, y*other.y, z*other.z};
    }

    vector3 normalize() {
        float norm = sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
        return {x/norm, y/norm, z/norm};
    }

    vector3 crossProduct(vector3 other) {
        return {y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x};
    }

    float dotProduct(vector3 other) {
        return {x*other.x + y*other.y + z*other.z};
    }

    vector3 scalar(float scalar) {
        return {scalar * x, scalar * y, scalar * z};
    }
};

struct vector2 {
    
    float x, y;
};

struct pixelStruct {

    uint8_t b, g, r;
};