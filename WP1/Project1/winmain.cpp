#include <windows.h>
#include <stdlib.h>


#define STATIC_DEFAULT 1
#define STATIC_CUSTOM 2
#define EDIT_DEFAULT 3
#define EDIT_CUSTOM 4
#define BUTTON_DEFAULT 5
#define BUTTON_CUSTOM 6

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("LabWP1");
	HWND hWnd;
	MSG msg;
	WNDCLASS wndClass;

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = szAppName;

	if(!RegisterClass(&wndClass))
	{
		MessageBox(NULL, TEXT("This program requires Win NT"), szAppName, MB_ICONERROR);
		return 0;
	}

	

	hWnd = CreateWindow(szAppName, TEXT("WP \"Red\" 1"), WS_OVERLAPPEDWINDOW,
						600, 400, 640, 200,
						NULL, NULL, hInstance, NULL);

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
	static HFONT hFont;
    static int red = 180, green = 180, blue = 180;
	static int fontFlag = 0, childWindowPositionFlag = 1;

	switch (message)
	{
		
	case WM_CREATE:
		{

			CreateWindow(TEXT("STATIC"), TEXT("Default Text"),
						 WS_CHILD | WS_VISIBLE, 10, 10, 150, 30, hWnd,
						 (HMENU) STATIC_DEFAULT, NULL, NULL );

			CreateWindow(TEXT("STATIC"), TEXT("Custom Text"),
						 WS_CHILD | WS_VISIBLE | SS_SUNKEN | SS_CENTER, 180, 10, 150, 30, hWnd,
						 (HMENU) STATIC_CUSTOM, NULL, NULL );

			CreateWindow(TEXT("EDIT"), TEXT("Default"),
						 WS_CHILD | WS_VISIBLE, 10, 120, 150, 30, hWnd,
						 (HMENU) EDIT_DEFAULT, NULL, NULL);

			CreateWindow(TEXT("EDIT"), TEXT("Custom"),
						 WS_CHILD | WS_VISIBLE | ES_CENTER, 180, 120, 150, 30, hWnd,
						 (HMENU) EDIT_CUSTOM, NULL, NULL);

			CreateWindow(TEXT("BUTTON"), TEXT("Change Color"),
						 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 60, 150, 50, hWnd,
						 (HMENU) BUTTON_DEFAULT, NULL, NULL);

			CreateWindow(TEXT("BUTTON"), TEXT("Exit"),
						 WS_CHILD | WS_VISIBLE | BS_HOLLOW | BS_PUSHBUTTON, 180, 60, 150, 50, hWnd,
						 (HMENU) BUTTON_CUSTOM, NULL, NULL);

			hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, TRUE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
							   CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Calibri"));

			SendMessage(GetDlgItem(hWnd, STATIC_CUSTOM), WM_SETFONT, (WPARAM)hFont, TRUE);
			SendMessage(GetDlgItem(hWnd, EDIT_CUSTOM), WM_SETFONT, (WPARAM)hFont, TRUE);
			SendMessage(GetDlgItem(hWnd, BUTTON_CUSTOM), WM_SETFONT, (WPARAM)hFont, TRUE);

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
		{
			switch(HIWORD(wParam))
			{
			case BN_CLICKED:
				switch (LOWORD(wParam))
				{
				case BUTTON_DEFAULT:
					{
						red = rand() % 256;
						green = rand() % 256;
						blue = rand() % 256;

						InvalidateRect(NULL, NULL, NULL);
					}					
					break;

				case BUTTON_CUSTOM:
					DestroyWindow(hWnd);
					break;
				}


			case EN_CHANGE:
				switch(LOWORD(wParam))
				{
				case EDIT_DEFAULT:
					{
						wchar_t text[128];
						wchar_t moveText[] = L"move";
						GetDlgItemText(hWnd, EDIT_DEFAULT, text, 128);
						if(lstrcmp(text, moveText) == 0)
						{
							POINT newPosition;
							newPosition.x = rand() % 1024;
							newPosition.y = rand() % 720;

							SetWindowPos(hWnd, HWND_TOP, newPosition.x, newPosition.y, 0, 0, SWP_NOSIZE);
						}
						SetWindowText(GetDlgItem(hWnd, STATIC_DEFAULT), text);
					}
					break;

				case EDIT_CUSTOM:
					{
						wchar_t text[128];
						wchar_t minText[] = L"minimize";
						GetDlgItemText(hWnd, EDIT_CUSTOM, text, 128);
						if(lstrcmp(text, minText) == 0)
						{
							ShowWindow(hWnd, SW_FORCEMINIMIZE);
						}
						SetWindowText(GetDlgItem(hWnd, STATIC_CUSTOM), text);						
					}
					break;
				}
			}
		}
		break;
	
	case WM_SIZE:
		{
			int x = LOWORD(lParam)/10 + 50;
			int y = HIWORD(lParam)/10 + 20;

			if(childWindowPositionFlag == 1)
			{

				SetWindowPos(GetDlgItem(hWnd, STATIC_DEFAULT), HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
				SetWindowPos(GetDlgItem(hWnd, BUTTON_DEFAULT), HWND_TOP, x, y + 40, 0, 0, SWP_NOSIZE);
				SetWindowPos(GetDlgItem(hWnd, EDIT_DEFAULT), HWND_TOP, x, y + 100, 0, 0, SWP_NOSIZE);
				SetWindowPos(GetDlgItem(hWnd, STATIC_CUSTOM), HWND_TOP, x*1.75 + 170, y, 0, 0, SWP_NOSIZE);
				SetWindowPos(GetDlgItem(hWnd, BUTTON_CUSTOM), HWND_TOP, x*1.75 + 170, y + 40, 0, 0, SWP_NOSIZE);
				SetWindowPos(GetDlgItem(hWnd, EDIT_CUSTOM), HWND_TOP, x*1.75 + 170, y + 100, 0, 0, SWP_NOSIZE);
			}
			else
			{
				SetWindowPos(GetDlgItem(hWnd, STATIC_CUSTOM), HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
				SetWindowPos(GetDlgItem(hWnd, BUTTON_CUSTOM), HWND_TOP, x, y + 40, 0, 0, SWP_NOSIZE);
				SetWindowPos(GetDlgItem(hWnd, EDIT_CUSTOM), HWND_TOP, x, y + 100, 0, 0, SWP_NOSIZE);
				SetWindowPos(GetDlgItem(hWnd, STATIC_DEFAULT), HWND_TOP, x*1.75 + 170, y, 0, 0, SWP_NOSIZE);
				SetWindowPos(GetDlgItem(hWnd, BUTTON_DEFAULT), HWND_TOP, x*1.75 + 170, y + 40, 0, 0, SWP_NOSIZE);
				SetWindowPos(GetDlgItem(hWnd, EDIT_DEFAULT), HWND_TOP, x*1.75 + 170, y + 100, 0, 0, SWP_NOSIZE);
			}
		}
		break;


	case WM_SYSCOMMAND:
		switch(LOWORD(wParam))
		{
		case SC_MINIMIZE:
			{
				HFONT hFontNew;

				if(fontFlag == 0)
				{
					hFontNew = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, UNICODE, OUT_OUTLINE_PRECIS,
										  CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Calibri"));
					fontFlag = 1;
				}
				else
				{
					hFontNew = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, UNICODE, OUT_OUTLINE_PRECIS,
										  CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Impact"));
					fontFlag = 0;
				}


				SendMessage(GetDlgItem(hWnd, STATIC_CUSTOM), WM_SETFONT, (WPARAM)hFontNew, TRUE);
				SendMessage(GetDlgItem(hWnd, EDIT_CUSTOM), WM_SETFONT, (WPARAM)hFontNew, TRUE);
				SendMessage(GetDlgItem(hWnd, BUTTON_CUSTOM), WM_SETFONT, (WPARAM)hFontNew, TRUE);
			}
			break;

		case SC_CLOSE:
			MessageBox(NULL, L"OH NOES, it doesn't work this way", L"Notification", MB_OK);
			int width, height;
			width = rand() % 500 + 640;
			height = rand() % 500 + 200;
			SetWindowPos(hWnd, HWND_TOP, 0, 0, width, height, SWP_NOMOVE);
			break;

		case SC_MAXIMIZE:
			{
				int x = LOWORD(lParam)/10 + 10;
				int y = HIWORD(lParam)/10 + 10;

				if(childWindowPositionFlag == 0)
				{
					ShowWindow(hWnd, SW_SHOWMAXIMIZED);
					SetWindowPos(GetDlgItem(hWnd, STATIC_DEFAULT), HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
					SetWindowPos(GetDlgItem(hWnd, BUTTON_DEFAULT), HWND_TOP, x, y + 40, 0, 0, SWP_NOSIZE);
					SetWindowPos(GetDlgItem(hWnd, EDIT_DEFAULT), HWND_TOP, x, y + 100, 0, 0, SWP_NOSIZE);
					SetWindowPos(GetDlgItem(hWnd, STATIC_CUSTOM), HWND_TOP, x*1.75 + 170, y, 0, 0, SWP_NOSIZE);
					SetWindowPos(GetDlgItem(hWnd, BUTTON_CUSTOM), HWND_TOP, x*1.75 + 170, y + 40, 0, 0, SWP_NOSIZE);
					SetWindowPos(GetDlgItem(hWnd, EDIT_CUSTOM), HWND_TOP, x*1.75 + 170, y + 100, 0, 0, SWP_NOSIZE);
					childWindowPositionFlag = 1;

				}
				else
				{
					ShowWindow(hWnd, SW_SHOWMAXIMIZED);
					SetWindowPos(GetDlgItem(hWnd, STATIC_CUSTOM), HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
					SetWindowPos(GetDlgItem(hWnd, BUTTON_CUSTOM), HWND_TOP, x, y + 40, 0, 0, SWP_NOSIZE);
					SetWindowPos(GetDlgItem(hWnd, EDIT_CUSTOM), HWND_TOP, x, y + 100, 0, 0, SWP_NOSIZE);
					SetWindowPos(GetDlgItem(hWnd, STATIC_DEFAULT), HWND_TOP, x*1.75 + 170, y, 0, 0, SWP_NOSIZE);
					SetWindowPos(GetDlgItem(hWnd, BUTTON_DEFAULT), HWND_TOP, x*1.75 + 170, y + 40, 0, 0, SWP_NOSIZE);
					SetWindowPos(GetDlgItem(hWnd, EDIT_DEFAULT), HWND_TOP, x*1.75 + 170, y + 100, 0, 0, SWP_NOSIZE);
					childWindowPositionFlag = 0;

				}
				InvalidateRect(NULL, NULL, NULL);
							
			}
			break;

		default:
			DefWindowProc(hWnd, message, wParam, lParam);
		
		}
		break;
	

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}