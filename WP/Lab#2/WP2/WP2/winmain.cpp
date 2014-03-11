#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' \
                version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' \
                language='*'\"")


#include <windows.h>
#include "resource.h"
#include <stdlib.h>




BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("LabWP2");
	HWND hWnd;
	MSG msg;
	WNDCLASS wndClass;

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR));
	wndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wndClass.lpszMenuName = szAppName;
	wndClass.lpszClassName = szAppName;

	if(!RegisterClass(&wndClass))
	{
		MessageBox(NULL, TEXT("This program requires Win NT"), szAppName, MB_ICONERROR);
		return 0;
	}
	

	hWnd = CreateWindow(szAppName, TEXT("Acid Trip"), 
						WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL | WS_SYSMENU,
						600, 400, 640, 200, NULL, NULL, hInstance, NULL);

	RegisterHotKey(hWnd, HK_CLOSE, MOD_CONTROL, 0x58);// Ctrl + X
	RegisterHotKey(hWnd, HK_BGCOLOR, MOD_ALT, 0x43);// Alt + C

	MessageBox(NULL, TEXT("Don't abuse ALT + C, unless you want to party."), TEXT("Warning"), MB_OK | MB_ICONASTERISK);


	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hInstance;
	static int prevScrollY = 0, prevScrollX = 0;
	static int red = 180, green = 180, blue = 180;
	static HWND hStatic, hListBox, hScrollStatic, hScrollHeight, hScrollWidth;
	SCROLLINFO sbInfo;
	int listElemId;
	static int txtColor;
	HFONT hFont;

	switch (message)
	{
	
	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;

		hStatic = CreateWindow(L"STATIC", L"The Color Can Be Changed",
							   WS_CHILD | WS_VISIBLE | SS_CENTER | SS_SUNKEN,
							   10, 30, 200, 20, hWnd, (HMENU)ID_STATICTEXT, NULL, NULL);

		hListBox = CreateWindow(L"LISTBOX", NULL,
								WS_CHILD | WS_VISIBLE | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT | LBS_DISABLENOSCROLL,
								250, 30, 150, 70, hWnd, (HMENU)ID_LISTBOX, NULL, NULL);

		SendMessage(hListBox, LB_ADDSTRING, TRUE, (WPARAM)L"Tahoma");
		SendMessage(hListBox, LB_ADDSTRING, TRUE, (WPARAM)L"Impact");
		SendMessage(hListBox, LB_ADDSTRING, TRUE, (WPARAM)L"Bookman Old Style");
		SendMessage(hListBox, LB_ADDSTRING, TRUE, (WPARAM)L"Calibri");


		hScrollStatic = CreateWindow(L"SCROLLBAR", NULL, 
									 WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_TOPALIGN,
									 10, 60, 200, 20, hWnd, (HMENU)ID_SCROLLSTATIC, NULL, NULL);

		sbInfo.cbSize = sizeof(SCROLLINFO);
		sbInfo.fMask = SIF_RANGE|SIF_POS;
		sbInfo.nMin = 0;
		sbInfo.nMax = 255;
		sbInfo.nPos = 255;

		SetScrollInfo(hScrollStatic, SB_CTL, &sbInfo, TRUE);

		hScrollHeight = CreateWindow(L"SCROLLBAR", NULL, 
									 WS_CHILD | WS_VISIBLE| SBS_HORZ | SBS_TOPALIGN,
									 10, 90, 200, 20, hWnd, (HMENU)ID_SCROLLHEIGHT, NULL, NULL);

		sbInfo.cbSize = sizeof(SCROLLINFO);
		sbInfo.fMask = SIF_RANGE|SIF_POS;
		sbInfo.nMin = 0;
		sbInfo.nMax = 1000;
		sbInfo.nPos = 240;

		SetScrollInfo(hScrollHeight, SB_CTL, &sbInfo, TRUE);


		hScrollWidth = CreateWindow(L"SCROLLBAR", NULL, 
									 WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_TOPALIGN,
									 10, 120, 200, 20, hWnd, (HMENU)ID_SCROLLWIDTH, NULL, NULL);

		sbInfo.cbSize = sizeof(SCROLLINFO);
		sbInfo.fMask = SIF_RANGE|SIF_POS;
		sbInfo.nMin = 0;
		sbInfo.nMax = 1500;
		sbInfo.nPos = 600;

		SetScrollInfo(hScrollWidth, SB_CTL, &sbInfo, TRUE);

		break;

	case WM_SETCURSOR:
		if (LOWORD(lParam) == HTCLIENT)
		{
			SetCursor(LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR)));
			return TRUE;
		}
		break;
	
	case WM_GETMINMAXINFO:
		{
			LPMINMAXINFO minMaxInfo;
			minMaxInfo = (LPMINMAXINFO)lParam;

			RECT rct;

			rct.left = 0;
			rct.top = 0;
			rct.right = 640;
			rct.bottom = 200;

			AdjustWindowRectEx(&rct, WS_OVERLAPPEDWINDOW, FALSE, WS_OVERLAPPEDWINDOW);

			POINT minSize;
			minSize.x = rct.right - rct.left;
			minSize.y = rct.bottom - rct.top;

			minMaxInfo->ptMinTrackSize = minSize;

			
		}
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			RECT rct;
			HDC hDC;
			HBRUSH hBrush;

			hDC = BeginPaint(hWnd, &ps);

			GetClientRect(hWnd, &rct);
			hBrush = CreateSolidBrush(RGB(red, green, blue));
			FillRect(hDC, &rct, hBrush);

			EndPaint(hWnd, &ps);
		}
		break;	

	

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_LISTBOX:
			switch(HIWORD(wParam))
			{
			case LBN_DBLCLK:
				listElemId = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				if(listElemId == 0)
				{
					hFont = CreateFont(17, 0, 0, 0, 0, 0, 0, 0, UNICODE, 0,
									   0,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Tahoma"));
				}
				else if(listElemId == 1)
				{
					hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, UNICODE, 0,
									   0,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Impact"));
				}
				else if(listElemId == 2)
				{
					hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, UNICODE, 0,
									   0,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Bookman Old Style"));
				}
				else if(listElemId == 3)
				{
					hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, UNICODE, 0,
									   0,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Calibri"));
				}

				SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
				SendMessage(hListBox, WM_SETFONT, (WPARAM)hFont, TRUE);

			}
			break;


		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		case IDM_MOVE:
			int xPos, yPos;
			xPos = rand() % 1000;
			yPos = rand() % 800;
			SetWindowPos(hWnd, HWND_TOP, xPos, yPos, 0, 0, SWP_NOSIZE);
			break;

		case IDM_ABOUT:
			DialogBox(hInstance, TEXT("AboutBox"), hWnd, AboutDlgProc);
			break;

		default:

			break;
		}
		break;


	case WM_HOTKEY:
		switch(wParam)
		{
		case HK_CLOSE:
			DestroyWindow(hWnd);

			break;

		case HK_BGCOLOR:

			red = rand() % 256;
			green = rand() % 256;
			blue = rand() % 256;
			ShowWindow(hWnd, SW_SHOWMAXIMIZED);
			InvalidateRect(hWnd, NULL, NULL);

			break;
			
		default: 

			break;
		}
		break;
	
	
		
	

	case WM_DESTROY:
		UnregisterHotKey(hWnd, HK_CLOSE);
		UnregisterHotKey(hWnd, HK_BGCOLOR);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}