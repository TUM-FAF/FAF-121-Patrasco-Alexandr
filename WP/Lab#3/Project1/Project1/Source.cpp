#pragma comment( lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


#include <windows.h>
#include <windowsx.h>

#define IDW_DRAWING_AREA    1001
#define IDB_PEN_TOOL        2001
#define IDB_LINE_TOOL       2002
#define IDB_POLYGON_TOOL    2003
#define IDB_ELLIPSE_TOOL    2004
#define IDB_BEZIER_TOOL     2005
#define IDB_ERASER_TOOL     2006
#define IDE_RED_FILL		3001
#define IDE_GREEN_FILL		3002
#define IDE_BLUE_FILL		3003
#define IDE_RED_STROKE		3004
#define IDE_GREEN_STROKE	3005
#define IDE_BLUE_STROKE		3006

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void updateColorPreview(HDC, COLORREF, int, int);
int getWeight(HWND);
COLORREF getColor(HWND, HWND, HWND);
POINT drawingLimits(int, int, RECT, int);
HRGN getLastRectRegion(RECT, int, BOOL*);
HRGN getLastEllipticRegion(RECT, int, BOOL*);

char szClassName[ ] = "Lab3";
HINSTANCE hInstance;

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = 0;
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
	wincl.hbrBackground = (HBRUSH)COLOR_WINDOW;

    if(!RegisterClassEx(&wincl)) return 0;

    hwnd = CreateWindowEx (
        0,
        szClassName,
        "Lab#3",
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX),
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 660,
        HWND_DESKTOP,
        NULL,
        hThisInstance,
        NULL);

    ShowWindow (hwnd, nCmdShow);

    while (GetMessage (&messages, NULL, 0, 0)) {
      TranslateMessage(&messages);
      DispatchMessage(&messages);
    }

    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

    static HWND hEraserWeight;
    static HWND hStrokeWeight;
    static HWND hPenTool;
    static HWND hLineTool;
    static HWND hPolygonTool;
    static HWND hEllipseTool;
    static HWND hBezierTool;
    static HWND hEraserTool;
    static HWND hFillCheck;
	static HWND hRStroke;
	static HWND hGStroke;
	static HWND hBStroke;
	static HWND hRFill;
	static HWND hGFill;
	static HWND hBFill;

    static POINT pen;
    static BOOL firstLine;
    static POINT newLine;
    static BOOL firstPolygon;
    static RECT newPolygon;
    static BOOL firstEllipse;
    static RECT newEllipse;
    static BOOL firstBezier;
    static BOOL secondBezier;
    static BOOL thirdBezier;
    static POINT pointsforBezier[4];
    static HRGN lastRegion;
    static BOOL regionDeleted;
	

    int xMouse, yMouse;

    static RECT drawingArea = {203, 20, 770, 413};

    
	RECT grad = {30, 260, 173, 300};

    RECT rectTemp;

    HDC hdc = GetDC(hwnd);
    static COLORREF strokeRGB;
    int strokeWeight;
    static COLORREF fillRGB;
    HBRUSH fillBrush;
    PAINTSTRUCT ps;
    HPEN strokePen;
    POINT point;
    RECT rect;

    HBRUSH hBrush;
	
   

    HDC hdcMem;
    BITMAP bitmap;
    HBITMAP hbmpimage = NULL;
    hbmpimage = (HBITMAP)LoadImage(hInstance, "i.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hbmpimage, sizeof(bitmap), &bitmap);

    switch(message) {

        case WM_CREATE:

            CreateWindowEx(
                0,
                "Button",
                "Tools",
                WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                5, 435,
                185, 170,
                hwnd,
                0,
                hInstance,
                NULL);

            CreateWindowEx(
                0,
                "Button",
                "Style",
                WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                5, 15,
                185, 180,
                hwnd,
                0,
                hInstance,
                NULL);

            CreateWindowEx(
                0,
                "Button",
                "Color",
                WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                5, 220,
                185, 190,
                hwnd,
                0,
                hInstance,
                NULL);

            CreateWindowEx(
                0,
                "Static",
                "Fill",
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                40, 315,
                45, 20,
                hwnd,
                (HMENU)0,
                hInstance,
                NULL);

            CreateWindowEx(
                0,
                "Static",
                "Stroke",
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                110, 315,
                45, 20,
                hwnd,
                (HMENU)0,
                hInstance,
                NULL);

            CreateWindowEx(
                0,
                "Static",
                "R",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                15, 335,
                10, 15,
                hwnd,
                (HMENU)0,
                hInstance,
                NULL);

            CreateWindowEx(
                0,
                "Static",
                "G",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                15, 355,
                10, 15,
                hwnd,
                (HMENU)0,
                hInstance,
                NULL);

            CreateWindowEx(
                0,
                "Static",
                "B",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                15, 376,
                10, 15,
                hwnd,
                (HMENU)0,
                hInstance,
                NULL);

            hPenTool = CreateWindowEx(
                0,
                "Button",
                "Pen",
				WS_VISIBLE | WS_CHILD | WS_GROUP | BS_AUTORADIOBUTTON | BS_PUSHLIKE,
                10, 470,
                80, 20,
                hwnd,
                (HMENU)IDB_PEN_TOOL,
                hInstance,
                NULL);

            Button_SetCheck(hPenTool, BST_CHECKED);

            hLineTool = CreateWindowEx(
                0,
                "Button",
                "Line",
				WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | BS_PUSHLIKE,
                10, 510,
                80, 20,
                hwnd,
                (HMENU)IDB_LINE_TOOL,
                hInstance,
                NULL);

            hPolygonTool = CreateWindowEx(
                0,
                "Button",
                "Polygon",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | BS_PUSHLIKE,
                100, 510,
                80, 20,
                hwnd,
                (HMENU)IDB_POLYGON_TOOL,
                hInstance,
                NULL);

            hEllipseTool = CreateWindowEx(
                0,
                "Button",
                "Ellipse",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | BS_PUSHLIKE,
                100, 470,
                80, 20,
                hwnd,
                (HMENU)IDB_ELLIPSE_TOOL,
                hInstance,
                NULL);

            hBezierTool = CreateWindowEx(
                0,
                "Button",
                "Bezier",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | BS_PUSHLIKE,
                10, 550,
                80, 20,
                hwnd,
                (HMENU)IDB_BEZIER_TOOL,
                hInstance,
                NULL);

            hFillCheck = CreateWindowEx(
                0,
                "Button",
                "Fill",
                WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                30, 50,
                80, 20,
                hwnd,
                (HMENU)0,
                hInstance,
                NULL);

            CreateWindowEx(
                0,
                "Static",
                "Stroke",
                WS_VISIBLE | WS_CHILD,
                30, 90,
                80, 20,
                hwnd,
                (HMENU)0,
                hInstance,
                NULL);

			CreateWindowEx(
                0,
                "Static",
                "Eraser",
                WS_VISIBLE | WS_CHILD,
                30, 128,
                80, 20,
                hwnd,
                (HMENU)0,
                hInstance,
                NULL);

            hStrokeWeight = CreateWindowEx(
                0,
                "Edit",
                "1",
                WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
                120, 90,
                20, 20,
                hwnd,
                (HMENU)0,
                hInstance,
                NULL);

			hRFill = CreateWindowEx(
                0,
                "Edit",
                "0",
                WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,
                40, 335,
                30, 15,
                hwnd,
                (HMENU)0,
                hInstance,
                NULL);

			hGFill = CreateWindowEx(
                0,
                "Edit",
                "0",
                WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,
                40, 355,
                30, 15,
                hwnd,
                (HMENU)0,
                hInstance,
                NULL);

			hBFill = CreateWindowEx(
                0,
                "Edit",
                "0",
                WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,
                40, 375,
                30, 15,
                hwnd,
                (HMENU)0,
                hInstance,
                NULL);

			hRStroke = CreateWindowEx(
                0,
                "Edit",
                "255",
                WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,
                125, 335,
                30, 15,
                hwnd,
                (HMENU)0,
                hInstance,
                NULL);

			hGStroke = CreateWindowEx(
                0,
                "Edit",
                "255",
                WS_VISIBLE | WS_CHILD | WS_BORDER | SS_RIGHT,
                125, 355,
                30, 15,
                hwnd,
                (HMENU)0,
                hInstance,
                NULL);

			hBStroke = CreateWindowEx(
                0,
                "Edit",
                "255",
                WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
                125, 375,
                30, 15,
                hwnd,
                (HMENU)0,
                hInstance,
                NULL);

            hEraserTool = CreateWindowEx(
                0,
                "Button",
                "Eraser",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | BS_PUSHLIKE,
                100, 550,
                80, 20,
                hwnd,
                (HMENU)IDB_ERASER_TOOL,
                hInstance,
                NULL);

            hEraserWeight = CreateWindowEx(
                0,
                "Edit",
                "1",
                WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
                120, 128,
                20, 20,
                hwnd, (HMENU)0,
                hInstance,
                NULL);
            return 0;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                default:
                    DefWindowProc(hwnd, WM_COMMAND, wParam, lParam);
                    break;
            }
            return 0;

        case WM_LBUTTONDOWN:
            xMouse = GET_X_LPARAM(lParam);
            yMouse = GET_Y_LPARAM(lParam);

            

                if((xMouse > drawingArea.left)&&(xMouse < drawingArea.right)&&(yMouse > drawingArea.top)&&(yMouse < drawingArea.bottom)) {
                strokeWeight = getWeight(hStrokeWeight);
                point = drawingLimits(xMouse, yMouse, drawingArea, strokeWeight);
                xMouse = point.x;
                yMouse = point.y;

                if((wParam == MK_LBUTTON)&&(Button_GetCheck(hPenTool) == BST_CHECKED)) {
                    pen.x = xMouse;
                    pen.y = yMouse;
                }

                if((wParam == MK_LBUTTON)&&(Button_GetCheck(hLineTool) == BST_CHECKED)) {
                    newLine.x = xMouse;
                    newLine.y = yMouse;
                    firstLine = true;
                }

                if((wParam == MK_LBUTTON)&&(Button_GetCheck(hPolygonTool) == BST_CHECKED)) {
                    newPolygon.left = xMouse;
                    newPolygon.top = yMouse;
                    firstPolygon = true;
                }

                if((wParam == MK_LBUTTON)&&(Button_GetCheck(hEllipseTool) == BST_CHECKED)) {
                    newEllipse.left = xMouse;
                    newEllipse.top = yMouse;
                    firstEllipse = true;
                }

                if((wParam == MK_LBUTTON)&&(Button_GetCheck(hBezierTool) == BST_CHECKED)) {
                    pointsforBezier[0] = point;
                    firstBezier  = true;
                    secondBezier = false;
                    thirdBezier  = false;
                }
            }
            return 0;

        case WM_LBUTTONUP:

            xMouse = GET_X_LPARAM(lParam);
            yMouse = GET_Y_LPARAM(lParam);

			strokeRGB = getColor(hRStroke, hGStroke, hBStroke);
			fillRGB = getColor(hRFill, hGFill, hBFill);
            strokeWeight = getWeight(hStrokeWeight);

            if(firstLine) {
                point = drawingLimits(xMouse, yMouse, drawingArea, strokeWeight);
                xMouse = point.x;
                yMouse = point.y;

                strokePen = CreatePen(PS_SOLID, strokeWeight, strokeRGB);
                SelectObject(hdc, strokePen);
                MoveToEx(hdc, xMouse, yMouse, NULL);
                LineTo(hdc, newLine.x, newLine.y);
                DeleteObject(strokePen);

                firstLine = false;
            }

            if(firstPolygon) {
                point = drawingLimits(xMouse, yMouse, drawingArea, strokeWeight);
                newPolygon.right = point.x;
                newPolygon.bottom = point.y;

                strokePen = CreatePen(PS_SOLID, strokeWeight, strokeRGB);
                fillBrush = (Button_GetCheck(hFillCheck) == BST_CHECKED)? CreateSolidBrush(fillRGB) : (HBRUSH)GetStockObject(NULL_BRUSH);
                SelectObject(hdc, strokePen);
                SelectObject(hdc, fillBrush);
                Rectangle(hdc, newPolygon.left, newPolygon.top, newPolygon.right, newPolygon.bottom);
                DeleteObject(strokePen);
                DeleteObject(fillBrush);

                lastRegion = getLastRectRegion(newPolygon, strokeWeight, &regionDeleted);

                firstPolygon = false;
            }

            if(firstEllipse) {
                point = drawingLimits(xMouse, yMouse, drawingArea, strokeWeight);
                newEllipse.right = point.x;
                newEllipse.bottom = point.y;

                strokePen = CreatePen(PS_SOLID, strokeWeight, strokeRGB);
                fillBrush = (Button_GetCheck(hFillCheck) == BST_CHECKED)? CreateSolidBrush(fillRGB) : (HBRUSH)GetStockObject(NULL_BRUSH);
                SelectObject(hdc, strokePen);
                SelectObject(hdc, fillBrush);
                Ellipse(hdc, newEllipse.left, newEllipse.top, newEllipse.right, newEllipse.bottom);
                DeleteObject(strokePen);
                DeleteObject(fillBrush);

                lastRegion = getLastEllipticRegion(newEllipse, strokeWeight, &regionDeleted);

                firstEllipse = false;
            }

            if(firstBezier) {
                point = drawingLimits(xMouse, yMouse, drawingArea, strokeWeight);
                pointsforBezier[1] = point;
                firstBezier  = false;
                secondBezier = true;
                thirdBezier  = false;
            }
            return 0;

        case WM_RBUTTONDOWN:
            xMouse = GET_X_LPARAM(lParam);
            yMouse = GET_Y_LPARAM(lParam);

            

            if((xMouse > drawingArea.left)&&(xMouse < drawingArea.right)&&(yMouse > drawingArea.top)&&(yMouse < drawingArea.bottom)) {
                strokeWeight = getWeight(hStrokeWeight);
                point = drawingLimits(xMouse, yMouse, drawingArea, strokeWeight);
                xMouse = point.x;
                yMouse = point.y;

                if((wParam == MK_RBUTTON)&&(Button_GetCheck(hBezierTool) == BST_CHECKED)&&(secondBezier)) {
                    pointsforBezier[2] = point;
                    firstBezier  = false;
                    secondBezier = false;
                    thirdBezier  = true;
                }
            }
            if(regionDeleted) {
                InvalidateRgn(hwnd, lastRegion, TRUE);
                DeleteObject(lastRegion);
                regionDeleted = false;
            }
            return 0;

        case WM_RBUTTONUP:
            xMouse = GET_X_LPARAM(lParam);
            yMouse = GET_Y_LPARAM(lParam);
            strokeRGB = getColor(hRStroke, hGStroke, hBStroke);
			fillRGB = getColor(hRFill, hGFill, hBFill);
            strokeWeight = getWeight(hStrokeWeight);
            point = drawingLimits(xMouse, yMouse, drawingArea, strokeWeight);
            xMouse = point.x;
            yMouse = point.y;

            if(thirdBezier) {
                pointsforBezier[3] = point;
                strokePen = CreatePen(PS_SOLID, strokeWeight, strokeRGB);
                SelectObject(hdc, strokePen);
                PolyBezier(hdc, pointsforBezier, 4);
                DeleteObject(strokePen);
                firstBezier  = false;
                secondBezier = false;
                thirdBezier  = false;
            }
            return 0;

        case WM_MOUSEMOVE:
            xMouse = GET_X_LPARAM(lParam);
            yMouse = GET_Y_LPARAM(lParam);

            if((xMouse > drawingArea.left)&&(xMouse < drawingArea.right)
                &&(yMouse > drawingArea.top)&&(yMouse < drawingArea.bottom)) {
                strokeRGB = getColor(hRStroke, hGStroke, hBStroke);
				fillRGB = getColor(hRFill, hGFill, hBFill);

                if((wParam == MK_LBUTTON)&&(Button_GetCheck(hPenTool) == BST_CHECKED)) {
                    strokePen = CreatePen(PS_SOLID, 1, strokeRGB);
                    SelectObject(hdc, strokePen);
                    MoveToEx(hdc, xMouse, yMouse, NULL);
                    LineTo(hdc, pen.x, pen.y);
                    DeleteObject(strokePen);
                    pen.x = xMouse;
                    pen.y = yMouse;
                }

                if((wParam == MK_LBUTTON)&&(Button_GetCheck(hEraserTool) == BST_CHECKED)) {
                    strokeWeight = getWeight(hEraserWeight);
                    point = drawingLimits(xMouse, yMouse, drawingArea, strokeWeight);
                    xMouse = point.x;
                    yMouse = point.y;
                    rect.left = point.x - (strokeWeight/2);
                    rect.right = point.x + (strokeWeight/2);
                    rect.top = point.y - (strokeWeight/2);
                    rect.bottom = point.y + (strokeWeight/2);
                    InvalidateRect(hwnd, &rect, FALSE);
                    SendMessage(hwnd, WM_PAINT, 0, 0);
                    ValidateRect(hwnd, &rect);
                }
            }
            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);


            hdcMem = CreateCompatibleDC(hdc);
            SelectObject(hdcMem, hbmpimage);
            BitBlt(hdc, 200, 444, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
            DeleteDC(hdcMem);

			rectTemp.top = grad.top;
            rectTemp.bottom = grad.bottom;
            for(int i = 0; i < (grad.right - grad.left)/3; i++) {
                int r;
                r = i * 255 / (grad.right - grad.left);
                rectTemp.left  = grad.left  + i;
                rectTemp.right = grad.left + i + 1;
                hBrush = CreateSolidBrush(RGB(r, r/3, r/3));
                FillRect(hdc, &rectTemp, hBrush);
                DeleteObject(hBrush);
            }
			for(int i = (grad.right - grad.left)/3; i < 2*(grad.right - grad.left)/3; i++) {
                int g;
                g = i * 255 / (grad.right - grad.left);
                rectTemp.left  = grad.left  + i;
                rectTemp.right = grad.left + i + 1;
                hBrush = CreateSolidBrush(RGB(g/3, g, g/3));
                FillRect(hdc, &rectTemp, hBrush);
                DeleteObject(hBrush);
            }
			for(int i = 2*(grad.right - grad.left)/3; i < (grad.right - grad.left); i++) {
                int b;
                b = i * 255 / (grad.right - grad.left);
                rectTemp.left  = grad.left  + i;
                rectTemp.right = grad.left + i + 1;
                hBrush = CreateSolidBrush(RGB(b/3, b/3, b));
                FillRect(hdc, &rectTemp, hBrush);
                DeleteObject(hBrush);
            }



            

            SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0,0,0)));
            SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
            Rectangle(hdc, drawingArea.left, drawingArea.top, drawingArea.right, drawingArea.bottom);

            EndPaint(hwnd, &ps);
            return 0;

        case WM_DESTROY:
            PostQuitMessage (0);
            return 0;

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

POINT drawingLimits(int xMouse, int yMouse, RECT limit, int stroke) {
    POINT result;
    stroke = stroke / 2 + 1;

    if(xMouse - stroke < limit.left) {
        result.x = limit.left + stroke;
    } else if(xMouse + stroke > limit.right) {
        result.x = limit.right - stroke;
    } else result.x = xMouse;

    if(yMouse - stroke < limit.top) {
        result.y = limit.top + stroke;
    } else if(yMouse + stroke > limit.bottom) {
        result.y = limit.bottom - stroke;
    } else result.y = yMouse;

    return result;
}


HRGN getLastEllipticRegion(RECT rect, int stroke, BOOL* flag) {
    HRGN result = CreateEllipticRgn(
        rect.left - (stroke / 2) - 1,
        rect.top - (stroke / 2) - 1,
        rect.right + (stroke / 2) + 1,
        rect.bottom + (stroke / 2) + 1);
    *flag = TRUE;
    return result;
}

HRGN getLastRectRegion(RECT rect, int stroke, BOOL* flag) {
    HRGN result = CreateRectRgn(
        rect.left - (stroke / 2) - 1,
        rect.top - (stroke / 2) - 1,
        rect.right + (stroke / 2) + 1,
        rect.bottom + (stroke / 2) + 1);
    *flag = TRUE;
    return result;
}

int getWeight(HWND input) {
    int result;
    int iLength = SendMessage(input, WM_GETTEXTLENGTH, 0, 0);
    char* szText = (char*)malloc(iLength+1);
    SendMessage(input, WM_GETTEXT, iLength+1, (LPARAM)szText);
    result = atoi(szText);
    _itoa(result, szText, 10);
    SendMessage(input, WM_SETTEXT, 0, (LPARAM)szText);
    free(szText);
    return result;
}

COLORREF getColor(HWND input1, HWND input2, HWND input3)
{
	COLORREF color;
	int red, green, blue, length;
	char* text;


	length = SendMessage(input1, WM_GETTEXTLENGTH, 0, 0);
	text = (char*)malloc(length + 1);
	SendMessage(input1, WM_GETTEXT, length + 1, (LPARAM)text);
	red = atoi(text);

	length = SendMessage(input2, WM_GETTEXTLENGTH, 0, 0);
	text = (char*)malloc(length + 1);
	SendMessage(input2, WM_GETTEXT, length + 1, (LPARAM)text);
	green = atoi(text);

	length = SendMessage(input3, WM_GETTEXTLENGTH, 0, 0);
	text = (char*)malloc(length + 1);
	SendMessage(input3, WM_GETTEXT, length + 1, (LPARAM)text);
	blue = atoi(text);

	free(text);

	color = RGB(red, green, blue);
	return color;
}
