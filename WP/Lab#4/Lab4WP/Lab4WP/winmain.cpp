#include <windows.h>

#include "ball.h"

#define IDT_TIMER 001

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static Ball *balls[50];
char className[] = "WPLab4";

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR arg, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wcex;

	wcex.hInstance = hInstance;
	wcex.lpszClassName = className;
	wcex.lpfnWndProc = WndProc;
	wcex.style = CS_DBLCLKS;
	wcex.cbSize = sizeof (WNDCLASSEX);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.lpszMenuName = NULL;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;


	if (!RegisterClassEx(&wcex)) return 0;

	hWnd = CreateWindowEx(0, className,
						  "WPLab4",
						  WS_OVERLAPPEDWINDOW,
						  CW_USEDEFAULT,
						  CW_USEDEFAULT,
						  700, 700,
						  HWND_DESKTOP,
						  NULL, hInstance,
						  NULL);
	ShowWindow(hWnd, nCmdShow);

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;

}

LRESULT CALLBACK WndProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HDC hDC;
	static HDC hDCMem;
	static PAINTSTRUCT ps;
	static RECT rect;
	static HBRUSH hBrush;
	static HBITMAP hBMMem;
	static HANDLE hOld;
	static int tSpeed = 50;
	static int nBalls = 0;

	switch(msg)
	{
	case WM_CREATE:

		hDC = GetDC(hWnd);
		GetClientRect(hWnd, &rect);
		hDCMem = CreateCompatibleDC(hDC);
		hBMMem = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);
		hOld = SelectObject(hDCMem, hBMMem);
		SetTimer(hWnd, IDT_TIMER, tSpeed, NULL);
		break;

	case WM_SIZE:

		SelectObject(hDCMem, hOld);
		DeleteObject(hBMMem);
		DeleteDC(hDCMem);
		hDC = GetDC(hWnd);
		GetClientRect(hWnd, &rect);
		hDCMem = CreateCompatibleDC(hDC);
		hBMMem = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);
		hOld = SelectObject(hDCMem, hBMMem);
		break;

	case WM_LBUTTONDOWN:

		POINT newCenter;
		newCenter.x = LOWORD(lParam);
		newCenter.y = HIWORD(lParam);

		balls[nBalls] = new Ball(newCenter, 5 + newCenter.x%5);
		balls[nBalls]->setColor(RGB(newCenter.x%127 + newCenter.y%128, newCenter.x%255, newCenter.y%175));
		nBalls++;
		break;

	case WM_MOUSEWHEEL:
		if((short)HIWORD(wParam) < 0)
		{
			tSpeed += 10;
		}
		else 
		{
			tSpeed -= 10;
			if(tSpeed < 0){tSpeed = 1;}
		}

		KillTimer(hWnd, IDT_TIMER);
		SetTimer(hWnd, IDT_TIMER, tSpeed, NULL);
		break;

	case WM_PAINT:

		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);

		for(int i = 0; i < nBalls - 1; i++)
		{
			for(int j = i + 1; j < nBalls; j++)
			{
				checkBallCollision(*balls[i], *balls[j]);
			}
		}

		FillRect(hDCMem, &rect, (HBRUSH)COLOR_WINDOW);

		for(int i = 0; i < nBalls; i++)
		{
			balls[i]->moveBall(hDCMem, rect, hBrush);
		}

		BitBlt(hDC, 0, 0, rect.right, rect.bottom, hDCMem, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;

	case WM_TIMER:

		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_DESTROY:

		SelectObject(hDCMem, hOld);
		DeleteObject(hBMMem);
		DeleteObject(hDCMem);
		KillTimer(hWnd, IDT_TIMER);

		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}
