#include "headers.hpp"

float dotProduct(const vector2d& v1, const vector2d& v2) {
    return (v1.x * v2.x) + (v1.y * v2.y);
}

float crossProduct(const vector2d& v1, const vector2d& v2) {
    return (v1.x * v2.y) - (v1.y * v2.x);
}

float degreesToRadians(float angle) {
    return angle * M_PI / 180.0f;
}

float radiansToDegrees(float angle) {
    return angle / M_PI * 180.0f;
}

float generateRandomFloat(float rangeStart, float rangeEnd) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(rangeStart, rangeEnd);
    return dist(gen);
}

int generateRandomInt(int rangeStart, int rangeEnd) {
    return generateRandomFloat(static_cast<float>(rangeStart), static_cast<float>(rangeEnd)); 
}

float angleBetweenVectors(vector2d &v1, vector2d &v2) {
    float dotProduct = v1.x * v2.x + v1.y * v2.y;
    float cosTheta = dotProduct / (v1.length() * v2.length());
    if (cosTheta > 1.0f) cosTheta = 1.0f;
    if (cosTheta < -1.0f) cosTheta = -1.0f;
    
    float angleRadians = std::acos(cosTheta);
    float angle = radiansToDegrees(angleRadians);
    if (crossProduct(v1, v2) < 0)
    {
        angle = -angle;
    }
    return angle;
}

float getDecimalPart(float value) {
    return value - static_cast<int>(value);
}

COLORREF HEXtoRGB(const std::string& hexColor) {
    // Ensure the string starts with '#' and has the correct length
    if (hexColor.length() != 7 || hexColor[0] != '#') {
        return RGB(255, 255, 255); // Default to white on invalid input
    }

    // Extract RGB components from the hex string
    int r, g, b;
    std::istringstream(hexColor.substr(1, 2)) >> std::hex >> r;
    std::istringstream(hexColor.substr(3, 2)) >> std::hex >> g;
    std::istringstream(hexColor.substr(5, 2)) >> std::hex >> b;

    return RGB(r, g, b);
}

colorRGB HEXtoINT(const std::string& hex) {
    // Ensure the hex string is valid
    if (hex.length() != 7 || hex[0] != '#') {
        return {255, 255, 255}; // Default to white if invalid
    }

    // Extract the R, G, B components
    int r, g, b;
    std::istringstream(hex.substr(1, 2)) >> std::hex >> r;
    std::istringstream(hex.substr(3, 2)) >> std::hex >> g;
    std::istringstream(hex.substr(5, 2)) >> std::hex >> b;

    return {r, g, b};
}


COLORREF InterpolateColor(const std::string& c1, const std::string& c2, float step) {
    // Parse the colors
    colorRGB color1 = HEXtoINT(c1);
    colorRGB color2 = HEXtoINT(c2);

    // Log the parsed colors (for debugging)
    // std::cout << "R: " << color1.R << "   " << color2.R << "\n";
    // std::cout << "G: " << color1.G << "   " << color2.G << "\n";
    // std::cout << "B: " << color1.B << "   " << color2.B << "\n";

    // Calculate interpolated components
    int IR = static_cast<int>(color1.R + (color2.R - color1.R) * step);
    int IG = static_cast<int>(color1.G + (color2.G - color1.G) * step);
    int IB = static_cast<int>(color1.B + (color2.B - color1.B) * step);

    // Ensure values stay within valid bounds [0, 255]
    IR = std::clamp(IR, 0, 255);
    IG = std::clamp(IG, 0, 255);
    IB = std::clamp(IB, 0, 255);

    return RGB(IR, IG, IB);
}

std::string ColorToText(COLORREF color) {
    // Extract the R, G, B components from the COLORREF
    int r = GetRValue(color);
    int g = GetGValue(color);
    int b = GetBValue(color);

    // Create a hex string in the format #RRGGBB
    std::ostringstream oss;
    oss << "#" << std::uppercase << std::setfill('0') << std::hex
        << std::setw(2) << r
        << std::setw(2) << g
        << std::setw(2) << b;

    return oss.str();
}