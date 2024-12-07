#include "headers.hpp"

void Render(HDC hdc) {
    // Create an off-screen buffer
    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hbmMem = CreateCompatibleBitmap(hdc, screenWidth, screenHeight);
    HGDIOBJ hOld = SelectObject(hdcMem, hbmMem);
    RECT rect = { 0, 0, screenWidth, screenHeight };
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));  // Black background
    FillRect(hdcMem, &rect, hBrush);
    DeleteObject(hBrush);

    HFONT hFont = CreateCustomFont(100, 40, true, 0, 0, false, false, false, "Rubik");
    HFONT hOldFont = (HFONT)SelectObject(hdcMem, hFont);

    // gl.step = 0.8;

    std::string startColor = "#FF0000";
    std::string endColor = "#0000FF";

    COLORREF InterpolatedColor = InterpolateColor(startColor, endColor, gl.step);
    std::string InterpolateColorText = ColorToText(InterpolatedColor);

    SetTextColor(hdcMem, InterpolatedColor);
    SetBkMode(hdcMem, TRANSPARENT); // Transparent background for text

    // Draw the text
    DrawText(hdcMem, InterpolateColorText.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    if (gl.step < 1)
    {
        gl.step += 0.0004;
    }
    if (gl.step > 1) {
        gl.step = 1;
    }
    

    // Restore font and clean up
    SelectObject(hdcMem, hOldFont);
    DeleteObject(hFont);

    // Blit the buffer to the screen
    BitBlt(hdc, 0, 0, screenWidth, screenHeight, hdcMem, 0, 0, SRCCOPY);

    SelectObject(hdcMem, hOld);
    DeleteObject(hbmMem);
    DeleteDC(hdcMem);
}