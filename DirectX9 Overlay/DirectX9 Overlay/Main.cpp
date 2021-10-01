#include "Header.h"
HWND hwnd, WindowHWND;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	const MARGINS margin = { 0, 0, Render.RenderWidth, Render.RenderHeight };

	switch (message) {

	case WM_PAINT:
		DwmExtendFrameIntoClientArea(hWnd, &margin);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	// Define Window Name
	auto window_name = "Untitled - Notepad";

	// Find Window
	WindowHWND = FindWindow(NULL, window_name);

	RECT wndRc;

	if (WindowHWND) {
		GetWindowRect(WindowHWND, &wndRc);
	}
	else {
		// Failed to Find Target.
		ExitProcess(0);
	}

	Render.RenderWidth = wndRc.right - wndRc.left;
	Render.RenderHeight = wndRc.bottom - wndRc.top;

	auto centerX = (GetSystemMetrics(SM_CXSCREEN) / 2) - (Render.RenderWidth / 2);
	auto centerY = (GetSystemMetrics(SM_CYSCREEN) / 2) - (Render.RenderHeight / 2);

	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)RGB(0, 0, 0);
	wc.lpszClassName = "WindowClass";

	RegisterClassEx(&wc);

	hwnd = CreateWindowEx(0, "WindowClass", "", WS_EX_TOPMOST | WS_POPUP, wndRc.left, wndRc.top, Render.RenderWidth, Render.RenderHeight, NULL, NULL, hInstance, NULL);

	SetWindowLong(hwnd, GWL_EXSTYLE, (int)GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);

	SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 255, ULW_COLORKEY | LWA_ALPHA);


	ShowWindow(hwnd, nCmdShow);

	Render.initD3D(hwnd);

	MSG msg;

	SetWindowPos(FindWindow(NULL, window_name), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	while (true)
	{
		auto WindowHWND = FindWindow(NULL, window_name);

		if (!WindowHWND) {
			ExitProcess(0);
		}
#if 1
		GetWindowRect(WindowHWND, &wndRc);

		Render.RenderWidth = wndRc.right - wndRc.left;
		Render.RenderHeight = wndRc.bottom - wndRc.top;
#endif
		MoveWindow(hwnd, wndRc.left, wndRc.top, Render.RenderWidth, Render.RenderHeight, true);

		SetWindowPos(hwnd, HWND_TOPMOST, wndRc.left, wndRc.top, Render.RenderWidth, Render.RenderHeight, SWP_NOMOVE | SWP_NOSIZE);

		Render.render(&WindowHWND);

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT) {
			exit(0);
		}

	}

	Render.cleanD3D();

	return msg.wParam;
}