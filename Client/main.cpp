#ifndef UNICODE
#define UNICODE
#endif

#include "Player.h"
#include <ctime>
#include <string>
#include <chrono>
#include <iostream>


Graphics* graphics; // The Almighty gfx
Player player;

std::chrono::time_point<std::chrono::system_clock> m_start_time;
std::chrono::time_point<std::chrono::system_clock> m_end_time;

LRESULT CALLBACK window_proc(HWND handle, UINT u_msg, WPARAM w_param, LPARAM l_param);

int WINAPI wWinMain(const HINSTANCE hInstance, HINSTANCE, PWSTR, const int nShowCmd)
{

#pragma region WindowSetup
	// Register the window class.
    constexpr wchar_t class_name[] = L"Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = window_proc;
	wc.hInstance = hInstance;
	wc.lpszClassName = class_name;

	RegisterClass(&wc);

    const HWND handle = CreateWindow(
		class_name,
		nullptr,
		WS_MAXIMIZE, // Fullscreen
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, // x, y, width, height
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (handle == nullptr)	return 1;

	SetWindowLong(handle, GWL_STYLE, 0); // Remove all window styles, basically removes the border and close|min|max buttons ... I hate those

	graphics = new Graphics();

	if (!graphics->Init(handle))
	{
		delete graphics;
		return 1;
	}

	ShowWindow(handle, nShowCmd);
    ShowCursor(NULL);
#pragma endregion

	// Run the message loop.
	MSG msg;
	msg.message = WM_NULL;
	std::wstring ms = L"0";

	player.Init(handle);
	while (msg.message != WM_QUIT)
	{
		m_start_time = std::chrono::system_clock::now();
		// If there is a message, then handle the message
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
		    DispatchMessage(&msg);
		}
		player.Update();

		graphics->BeginDraw();
		graphics->ClearScreen(0, 0, 0);
		D2D1_RECT_F rect = { 0, 0, 100, 50 };
		graphics->WriteText(L"FPS: "+ms, rect);
	    player.WriteStats(graphics);
		player.Render(graphics);
		graphics->EndDraw();
	    // Sleep(500);

		m_end_time = std::chrono::system_clock::now();
		ms = std::to_wstring(1000/std::chrono::duration_cast<std::chrono::milliseconds>(m_end_time - m_start_time).count());
	}
	delete graphics; // explicitly delete graphics since it's allocated in heap memory
    std::cout << "exit 0";
	return 0;
}

LRESULT CALLBACK window_proc(const HWND handle, const UINT u_msg, const WPARAM w_param, const LPARAM l_param)
{
	if (u_msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	else { player.OnWinEvent(u_msg, w_param, l_param); }

	return DefWindowProc(handle, u_msg, w_param, l_param);
}
