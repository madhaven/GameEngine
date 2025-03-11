#pragma once

#include <d2d1.h>
#include <dwrite.h>
#include <string>

class Graphics
{
    ID2D1Factory* factory;
    IDWriteFactory* writeFactory;
    IDWriteTextFormat* writeFormat;
    ID2D1HwndRenderTarget* renderTarget;
    ID2D1SolidColorBrush* brush = NULL;

public:

    Graphics();
    ~Graphics();

    bool Init(HWND hwnd);

    void BeginDraw() { renderTarget->BeginDraw(); }

    void EndDraw() { renderTarget->EndDraw(); }

    void ClearScreen(float r, float g, float b) { renderTarget->Clear(D2D1::ColorF(r, g, b)); }

    void WriteText(const std::wstring& string, D2D1_RECT_F& layoutRect);

    void DrawEllipse(FLOAT x, FLOAT y, int r, D2D1_COLOR_F color);

    void DrawRectangle(D2D1_RECT_F& rect, D2D1_COLOR_F color);

    void DrawLine(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT width, D2D1_COLOR_F color);
};
