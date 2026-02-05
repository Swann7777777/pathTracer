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

    vector3 crossProduct(const vector3& other) const {
        return {y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x};
    }

    float dotProduct(const vector3& other) const {
        return {x*other.x + y*other.y + z*other.z};
    }

    vector3 scalar(const float& scalar) const {
        return {scalar * x, scalar * y, scalar * z};
    }

    vector3 min(const vector3 other) const {
        return {std::min(x, other.x), std::min(y, other.y), std::min(z, other.z)};
    }

    vector3 max(const vector3 other) const {
        return {std::max(x, other.x), std::max(y, other.y), std::max(z, other.z)};
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