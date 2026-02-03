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

    vector3 operator/(const float& divider) const {
        return {x/divider, y/divider, z/divider};
    }

    vector3 normalize() const {
        float norm = sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
        return {x/norm, y/norm, z/norm};
    }

    vector3 crossProduct(vector3& other) const {
        return {y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x};
    }

    float dotProduct(vector3& other) const {
        return {x*other.x + y*other.y + z*other.z};
    }

    vector3 scalar(const float& scalar) const {
        return {scalar * x, scalar * y, scalar * z};
    }
};

#pragma pack(push, 1)

struct pixelStruct {
    uint8_t b, g, r;
};

struct rgbaPixelStruct {
    uint8_t b, g, r, a;
};

#pragma pack(pop)