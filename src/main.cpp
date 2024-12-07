#include "headers.hpp"

int screenWidth = 1920;
int screenHeight = 1080;

int mouseX;
int mouseY;

float centerX = screenWidth/2;
float centerY = screenHeight/2;
vector2d screenCenter = {centerX, centerY};

bool isFullScreen = false;
bool keys[256] = {false};

globals gl;
controls ctrl;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "WinAPI";

    if (!RegisterClass(&wc)) {
        MessageBoxW(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    HWND hwnd = CreateWindow("WinAPI", "WinAPI", WS_OVERLAPPEDWINDOW,
                         CW_USEDEFAULT, CW_USEDEFAULT, screenWidth, screenHeight,
                         NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBoxW(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    SetCursor(LoadCursor(NULL, IDC_ARROW));

    gl.step = 0.0f;

    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            InvalidateRect(hwnd, NULL, FALSE);
            updateControls();
        }
    }
    Gdiplus::GdiplusShutdown(gdiplusToken);

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_LBUTTONDOWN: {
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);
            
            break;
        }
        case WM_MOUSEMOVE: {
            mouseX = LOWORD(lParam);
            mouseY = HIWORD(lParam);
            if (mouseY > 2*screenHeight) {
                mouseY = 0;
            }
            if (mouseX > 2*screenWidth) {
                mouseX = 0;
            }
            break;
        }
        case WM_LBUTTONUP: {
            break;
        }
        case WM_TIMER: {
            InvalidateRect(hwnd, NULL, FALSE);
            break;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            Render(hdc);

            EndPaint(hwnd, &ps);
            break;
        }
        case WM_SIZE: {
            screenWidth = LOWORD(lParam);
            screenHeight = HIWORD(lParam);
            centerX = screenWidth/2;
            centerY = screenHeight/2;
            screenCenter = {centerX, centerY};
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case WM_ERASEBKGND: {
            return TRUE;
        }
        case WM_CLOSE: {
            DestroyWindow(hwnd);
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        case WM_KEYDOWN:
            keys[wParam] = true;
            if (wParam == VK_F11) {
                ToggleFullscreen(hwnd);
            }
            break;

        case WM_KEYUP:
            keys[wParam] = false;
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void ToggleFullscreen(HWND hwnd) {
    static WINDOWPLACEMENT wp = { sizeof(WINDOWPLACEMENT) };
    
    if (!isFullScreen) {
        GetWindowPlacement(hwnd, &wp);
        screenWidth = GetSystemMetrics(SM_CXSCREEN);
        screenHeight = GetSystemMetrics(SM_CYSCREEN);
        centerX = screenWidth/2;
        centerY = screenHeight/2;
        screenCenter = {centerX, centerY};

        LONG style = GetWindowLong(hwnd, GWL_STYLE);
        SetWindowLong(hwnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);

        SetWindowPos(hwnd, HWND_TOP, 0, 0, screenWidth, screenHeight, SWP_NOOWNERZORDER | SWP_FRAMECHANGED);

        isFullScreen = true;
    } else {
        SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
        SetWindowPlacement(hwnd, &wp);
        
        SetWindowPos(hwnd, NULL, wp.rcNormalPosition.left, wp.rcNormalPosition.top, 
                     wp.rcNormalPosition.right - wp.rcNormalPosition.left,
                     wp.rcNormalPosition.bottom - wp.rcNormalPosition.top,
                     SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);

        isFullScreen = false;

        screenWidth = wp.rcNormalPosition.right - wp.rcNormalPosition.left;
        screenHeight = wp.rcNormalPosition.bottom - wp.rcNormalPosition.top;
        centerX = screenWidth/2;
        centerY = screenHeight/2;
        screenCenter = {centerX, centerY};
    }
}