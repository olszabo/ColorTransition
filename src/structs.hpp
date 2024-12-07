#ifndef STRUCTS_HPP
#define STRUCTS_HPP

struct TextureData {
    uint16_t width;
    uint16_t height;
    std::vector<uint32_t> pixels;
};

struct vector2d {
    float x;
    float y;

    void print() const {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }

    float cross(const vector2d &B, const vector2d &C) const {
        return (B.x - x) * (C.y - y) - (B.y - y) * (C.x - x);
    }

    float length() const {
        return sqrt(x * x + y * y);
    }

    float distance(const vector2d &v2) const {
        vector2d diff = {x - v2.x, y - v2.y};
        return diff.length();
    }

    vector2d scale(float k) const {
        return { x * k, y * k };
    }

    float dot(const vector2d &v2) const {
        return (x * v2.x) + (y * v2.y);
    }

    float dotNormalized(const vector2d &other) const {
        float magA = this->length();
        float magB = other.length();
        float dotProduct = this->dot(other);
        return dotProduct / (magA * magB);
    }

    vector2d normalize() const {
        float length = this->length();
        return { x / length, y / length };
    }

    vector2d lerp(const vector2d &end, float t) const {
        vector2d result;
        result.x = x + t * (end.x - x);
        result.y = y + t * (end.y - y);
        return result;
    }

    vector2d rotate(float angle) const {
        float cosTheta = std::cos(angle);
        float sinTheta = std::sin(angle);
        return {x * cosTheta - y * sinTheta, x * sinTheta + y * cosTheta};
    }
};

struct vector3d {
    float x;
    float y;
    float z;

    void print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
    }

    float length() const {
        return sqrt(x * x + y * y + z * z);
    }

    vector3d normalize() const {
        float length = this->length();
        return {x/length, y/length, z/length };
    }

    vector3d add(const vector3d &v2) const {
        return { x + v2.x, y + v2.y, z + v2.z };
    }

    vector3d sub(const vector3d &v2) const {
        return { x - v2.x, y - v2.y, z - v2.z };
    }

    vector3d scale(float k) const {
        return { x * k, y * k, z * k };
    }

    float dot(const vector3d &v2) const {
        return x * v2.x + y * v2.y + z * v2.z;
    }

    float dotNormalized(const vector3d &v2) const {
        float magA = this->length();
        float magB = v2.length();
        float dotProduct = this->dot(v2);
        return dotProduct / (magA * magB);
    }

    vector3d cross(const vector3d &v2) const {
        return {
            (y * v2.z - z * v2.y),
            (z * v2.x - x * v2.z),
            (x * v2.y - y * v2.x)
        };
    }

    vector3d normal(const vector3d &v2, const vector3d &v3) const {
        vector3d u = { v2.x - x, v2.y - y, v2.z - z };
        vector3d v = { v3.x - x, v3.y - y, v3.z - z };
        return u.cross(v).normalize();
    }

    float distance(const vector3d &v2) const {
        vector3d diff = this->sub(v2);
        return diff.length();
    }

    vector3d lerp(const vector3d &v2, float t) const {
        return {
            x + t * (v2.x - x),
            y + t * (v2.y - y),
            z + t * (v2.z - z)
        };
    }

    vector3d middle(const vector3d& v2) const {
        float fx = (x + v2.x) / 2;
        float fy = (y + v2.y) / 2;
        float fz = (z + v2.z) / 2;
        return {fx,fy,fz};
    }

    vector3d rotateXZ(float angle) const {
        float cosH = cosf(angle);
        float sinH = sinf(angle);
        return {x * cosH + z * sinH, y, -x * sinH + z * cosH};
    }

    vector3d rotateYZ(float angle) const {
        float cosV = cosf(angle);
        float sinV = sinf(angle);
        return {x, y * cosV + z * sinV, -y * sinV + z * cosV};
    }

    vector3d rotate(float angleH, float angleV) const {
        float cosH = cosf(angleH);
        float sinH = sinf(angleH);
        float cosV = cosf(angleV);
        float sinV = sinf(angleV);

        float newX = x * cosH + z * sinH;
        float newZ = -x * sinH + z * cosH;
        float newY = y * cosV + newZ * sinV;
        newZ = -y * sinV + newZ * cosV;

        return {newX, newY, newZ};
    }
};

struct matrix {
    float m[4][4];
    
    vector3d multiplyByVector(const vector3d& v) const {
        return {
            v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0],
            v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1],
            v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2]
        };
    }

    matrix multiply(const matrix& other) const {
        matrix result = {};
        
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                result.m[row][col] = 
                    m[row][0] * other.m[0][col] +
                    m[row][1] * other.m[1][col] +
                    m[row][2] * other.m[2][col] +
                    m[row][3] * other.m[3][col];
            }
        }

        return result;
    }
};

struct controls {

};

struct globals {
    float step;
};

struct colorRGB {
    int R;
    int G;
    int B;
};

#endif