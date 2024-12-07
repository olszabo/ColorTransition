#include "headers.hpp"

HFONT CreateCustomFont(int height, int width, bool bold, int angle, int orientation, bool italic, bool underline, bool strike, LPCSTR family) {
    if (!bold)
    {
        return CreateFont(
            height,          // Height of the font (negative for character height, positive for cell height)
            width,               // Width of the font (0 to let the system choose the best match)
            angle,               // Angle of escapement
            orientation,               // Orientation angle
            FW_NORMAL,       // Font weight (FW_NORMAL for normal, FW_BOLD for bold)
            italic,           // Italic
            underline,           // Underline
            strike,           // Strikeout
            DEFAULT_CHARSET, // Character set
            OUT_DEFAULT_PRECIS,  // Output precision
            CLIP_DEFAULT_PRECIS, // Clipping precision
            DEFAULT_QUALITY,     // Output quality
            DEFAULT_PITCH | FF_DONTCARE, // Pitch and family
            TEXT(family));
    } else {
        return CreateFont(
            height,          // Height of the font (negative for character height, positive for cell height)
            width,               // Width of the font (0 to let the system choose the best match)
            angle,               // Angle of escapement
            orientation,               // Orientation angle
            FW_BOLD,       // Font weight (FW_NORMAL for normal, FW_BOLD for bold)
            italic,           // Italic
            underline,           // Underline
            strike,           // Strikeout
            DEFAULT_CHARSET, // Character set
            OUT_DEFAULT_PRECIS,  // Output precision
            CLIP_DEFAULT_PRECIS, // Clipping precision
            DEFAULT_QUALITY,     // Output quality
            DEFAULT_PITCH | FF_DONTCARE, // Pitch and family
            TEXT(family));
    }
    
    
}

HFONT CreateScaledFont(int height) {
    return CreateFont(
        height,          // Height of the font (negative for character height, positive for cell height)
        0,               // Width of the font (0 to let the system choose the best match)
        0,               // Angle of escapement
        0,               // Orientation angle
        FW_NORMAL,       // Font weight (FW_NORMAL for normal, FW_BOLD for bold)
        FALSE,           // Italic
        FALSE,           // Underline
        FALSE,           // Strikeout
        DEFAULT_CHARSET, // Character set
        OUT_DEFAULT_PRECIS,  // Output precision
        CLIP_DEFAULT_PRECIS, // Clipping precision
        DEFAULT_QUALITY,     // Output quality
        DEFAULT_PITCH | FF_DONTCARE, // Pitch and family
        TEXT("Arial"));       // Font face (you can choose another font if needed)
}

void DrawTriangle(HDC hdc, const vector2d& p1, const vector2d& p2, const vector2d& p3, COLORREF outlineColor, COLORREF fillColor) {
    bool fillTriangle = 0;
    HBRUSH hBrush = CreateSolidBrush(fillColor);
    HPEN hPen = CreatePen(PS_SOLID, 1, outlineColor);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    
    // Draw the outline of the triangle
    MoveToEx(hdc, (int)p1.x, (int)p1.y, NULL);
    LineTo(hdc, (int)p2.x, (int)p2.y);
    LineTo(hdc, (int)p3.x, (int)p3.y);
    LineTo(hdc, (int)p1.x, (int)p1.y);
    
    if (fillTriangle) {
        POINT points[3]; // Array to hold the triangle vertices
        // Define the vertices of the triangle
        points[0].x = (int)p1.x;
        points[0].y = (int)p1.y;
        points[1].x = (int)p2.x;
        points[1].y = (int)p2.y;
        points[2].x = (int)p3.x;
        points[2].y = (int)p3.y;

        Polygon(hdc, points, 3);
    }

    SelectObject(hdc, hOldBrush);
    SelectObject(hdc, hOldPen);
    DeleteObject(hBrush);
    DeleteObject(hPen);
}

void WriteText(HDC hdc, const std::string& text, int x, int y, COLORREF color) {
    SetTextColor(hdc, color);
    SetBkMode(hdc, TRANSPARENT);
    // Convert std::string to LPCSTR
    TextOut(hdc, x, y, text.c_str(), text.length());
}

// Displays the number on the screen in specified location
void DrawNumber(HDC hdc, float number, int precision, const std::string& prefix, int x, int y, int fontSize, COLORREF color) {
    HFONT hFont = CreateScaledFont(fontSize);
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision);
    oss << prefix << number;
    std::string text = oss.str();
    SetTextColor(hdc, color);
    SetBkMode(hdc, TRANSPARENT);
    TextOut(hdc, x, y, text.c_str(), text.length());
    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);
}

// Displays a 3D point as a number on the screen in specified location
void DrawCoordinates(HDC hdc, const vector3d& coords, const std::string& prefix, int x, int y, int fontSize, COLORREF color) {
    HFONT hFont = CreateScaledFont(fontSize);
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << prefix << " X: " << coords.x << " Y: " << coords.y << " Z: " << coords.z;
    std::string text = oss.str();
    SetTextColor(hdc, color);
    SetBkMode(hdc, TRANSPARENT);
    TextOut(hdc, x, y, text.c_str(), text.length());
    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);
}

void DrawPoint(HDC hdc, vector2d position, int radius, COLORREF color) {
    HPEN hPen = CreatePen(PS_SOLID, 2*radius, color);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    // Select a null brush to ensure the circle is not filled
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));

    // Draw the circle outline (using Ellipse function)
    Ellipse(hdc, position.x - radius, position.y - radius, position.x + radius, position.y + radius);

    // Restore the original pen and brush, then clean up
    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hPen);
}
