#include <iostream>
#include <Windows.h>


int ScreenWidth, ScreenHeight, Interval = 250; // 100 miSec

LRESULT CALLBACK Melt(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CREATE:
	{
		HDC desktop = GetDC(HWND_DESKTOP);
		HDC window = GetDC(hWnd);

		BitBlt(window, 0, 0, ScreenWidth, ScreenHeight, desktop, 0, 0, SRCCOPY);
		ReleaseDC(hWnd, window);
		ReleaseDC(HWND_DESKTOP, desktop);

		SetTimer(hWnd, 0, Interval, 0);
		ShowWindow(hWnd, SW_SHOW);
		break;
	}
	case WM_PAINT:
	{
		ValidateRect(hWnd, 0);
		break;
	}
	case WM_TIMER:
	{
		HDC wndw = GetDC(hWnd);
		int x = (rand() % ScreenWidth) - (200 / 2);
		int y = (rand() % 15);

		int width = (rand() % 200);
		BitBlt(wndw, x, y, width, ScreenHeight, wndw, x, 0, SRCCOPY);
		ReleaseDC(hWnd, wndw);

		break;
	}
	case WM_DESTROY:
	{
		KillTimer(hWnd, 0);
		PostQuitMessage(0);
		break;
	}
	return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int main(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int showCmd)  // 64 - APIENTRY 86 - No "APIENTRY"
{
	ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	WNDCLASS wndClass = { 0, Melt,0,0,inst,0,LoadCursorW(0, IDC_ARROW),0,0,L"Screenshoter" };
	if (RegisterClass(&wndClass)) {
		HWND hWnd = CreateWindowExA(WS_EX_TOPMOST, "Screenshoter", 0, WS_POPUP, 0, 0, ScreenWidth, ScreenHeight, HWND_DESKTOP, 0, inst, 0);
		if (hWnd) {
			srand(GetTickCount64());
			MSG msg = { 0 };
			while (msg.message != WM_QUIT) {
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			for (int i = 0; i < 100; i++)
			{
				std::cout << "THIS NO SCREENSHOTER, IT IS PRANK by eXTrimeXT - https://vk.com/red_line_linux !!!\n";
			}
			std::cout << "Press any key for exit :D ";
			int a = 0;
			std::cin >> a;
			exit;
		}
	}
}
