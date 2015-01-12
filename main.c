#include <windows.h>
#include <stdio.h>
const char g_szClassName[] = "myWindowClass";
HRGN hRgn;
// Functions List //
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(DKGRAY_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	// if registration of main class fails
	if (!RegisterClassEx(&wc)){
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"Test region collision",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 450, 450,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL){
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0){
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg){
	case WM_CREATE:
	case WM_PAINT:
		{
			HDC hdc;
			PAINTSTRUCT ps;
			hdc = BeginPaint(hwnd, &ps);
			hRgn = CreateRectRgn(0, 0, 450, 450);
			Rectangle(hdc, 0, 0, 450, 450);
			EndPaint(hwnd, &ps);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			GetCursorPos(&pt);
			 int mX = pt.x;
			 int mY = pt.y;
			char buffer[25];
			sprintf(buffer, "%d %d", mX/200, mY/200);
			MessageBox(NULL, buffer, "You have clicked INSIDE hRgn%d", MB_ICONINFORMATION);/*
			if (PtInRegion(hRgn, mX, mY) != 0){
				char buffer[25];
				sprintf(buffer, "%d %d", mX,mY);
				MessageBox(NULL, buffer, "You have clicked INSIDE hRgn%d", MB_ICONINFORMATION);
			}
			else MessageBox(hwnd, "You have clicked OUTSIDE hRgn", "Notify", MB_OK);*/
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
