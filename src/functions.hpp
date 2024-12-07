#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP


// main.cpp
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void ToggleFullscreen(HWND hwnd);

// render.cpp
void Render(HDC hdc);

HFONT CreateCustomFont(int height, int width, bool bold, int angle, int orientation, bool italic, bool underline, bool strike, LPCSTR family);
HFONT CreateScaledFont(int height);
void DrawTriangle(HDC hdc, const vector2d& p1, const vector2d& p2, const vector2d& p3, COLORREF outlineColor, COLORREF fillColor);
void WriteText(HDC hdc, const std::string& text, int x, int y, COLORREF color);
void DrawNumber(HDC hdc, float number, int precision, const std::string& prefix, int x, int y, int fontSize, COLORREF color);
void DrawCoordinates(HDC hdc, const vector3d& coords, const std::string& prefix, int x, int y, int fontSize, COLORREF color);
void DrawPoint(HDC hdc, vector2d position, int radius, COLORREF color);

float degreesToRadians(float angle);
float radiansToDegrees(float angle);
float getDecimalPart(float value);

void updateControls();

float dotProduct(const vector2d& v1, const vector2d& v2);
float crossProduct(const vector2d& v1, const vector2d& v2);
float generateRandomFloat(float rangeStart, float rangeEnd);
int generateRandomInt(int rangeStart, int rangeEnd);
float angleBetweenVectors(vector2d &v1, vector2d &v2);
COLORREF HEXtoRGB(const std::string& hexColor);
COLORREF InterpolateColor(const std::string& c1, const std::string& c2, float step);
std::string ColorToText(COLORREF color);


#endif