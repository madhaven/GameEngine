#pragma once

#include "Graphics.h"
#include "Player.h"

Graphics::Graphics()
{
    factory = NULL;
    renderTarget = NULL;
}

Graphics::~Graphics()
{
    if (factory)		factory->Release();
    if (renderTarget)	renderTarget->Release();
}

bool Graphics::Init(HWND hwnd)
{
    HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
    if (result != S_OK)	return false;

    result = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), reinterpret_cast<IUnknown**>(&writeFactory));
    if (result != S_OK)	return false;

    const WCHAR msc_fontName[] = L"Verdana";
    const FLOAT msc_fontSize = 18;

    result = writeFactory->CreateTextFormat(msc_fontName,NULL, DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        msc_fontSize,
        L"", //locale
        &writeFormat
    );
    if (result != S_OK)	return false;
    else
    {
        writeFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        writeFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }
    RECT playableArea;
    GetClientRect(hwnd, &playableArea);
    factory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(playableArea.right, playableArea.bottom)),
        &renderTarget);

    renderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f), &brush);


    return true;
}

void Graphics::WriteText(const std::wstring& string, D2D1_RECT_F& layoutRect)
{
    brush->SetColor(D2D1::ColorF(1.0f, 1.0f, 1.0f));
    renderTarget->DrawText(
        string.c_str(),
        string.length(),
        writeFormat,
        layoutRect,
        brush
    );
}

void Graphics::DrawEllipse(FLOAT x, FLOAT y, int r, D2D1_COLOR_F color)
{
    brush->SetColor(color);
    D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), r, r);
    renderTarget->FillEllipse(ellipse, brush);
}

void Graphics::DrawRectangle(D2D1_RECT_F& rect, D2D1_COLOR_F color)
{
    brush->SetColor(color);
    renderTarget->DrawRectangle(rect, brush, 2);
    renderTarget->FillRectangle(rect, brush);
}

void Graphics::DrawLine(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT width, D2D1_COLOR_F color)
{
    brush->SetColor(color);
    renderTarget->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), brush, 0.5f);
}
