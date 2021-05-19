#include<windows.h>
#include"resource.h"
#include<strsafe.h>


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ErrorExit(LPTSTR lpszFunction);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPreInstance, _In_ LPSTR lpCmdLine, _In_ INT nCmdShow)
{
	//register Class
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;	//DefWindowProc默认函数没有设置退出，即使X掉程序后实际上还是在后台运行，消息循环无法退出
	wc.hInstance = hInstance;
	wc.lpszClassName = L"WindowsLearn";
	RegisterClass(&wc);

	////创建菜单资源
	//HMENU hMenuPopup = CreatePopupMenu();
	//AppendMenu(hMenuPopup, MF_STRING, 211, L"New File");
	//AppendMenu(hMenuPopup, MF_SEPARATOR, NULL, NULL);
	//AppendMenu(hMenuPopup, MF_STRING, 212, L"Open File");
	//HMENU hMenuTop = CreateMenu();
	//AppendMenu(hMenuTop, MF_POPUP, (UINT_PTR)hMenuPopup, L"File");
	//InsertMenu(hMenuTop, 1, MF_STRING | MF_BYPOSITION, 112, L"Edit");

	HWND hWnd = CreateWindow(wc.lpszClassName, L"Windows",
		WS_OVERLAPPEDWINDOW,	//windows style
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,	//position and size
		NULL,	//parent class
		NULL,	//menu
		hInstance,
		NULL
	);
	if (hWnd == NULL) return 0;

	ShowWindow(hWnd, nCmdShow);


	MSG msg = {};
	UINT msgFilterMin = 0, msgFilterMax = 0;
	while (GetMessage(&msg, NULL, msgFilterMin, msgFilterMax))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);	//线程消息分发给窗口，一个线程可有多个窗口，
	}

	//DestroyMenu(hMenuPopup);
	//DestroyMenu(hMenuTop);
	return 0;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HMENU hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
		SetMenu(hWnd, hMenu);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_COMMAND:
	{
		WORD menuId = LOWORD(wParam);
		switch (menuId)
		{
		case ID_VIEW:
		{
			MessageBox(hWnd, L"你点击了View菜单", L"提示", MB_OK);
			break;
		}
		case ID_NEW_FILE:
		{
			MessageBox(hWnd, L"你点击了NEW_FILE", L"提示", MB_OK);
			break;
		}
		case ID_HELP:
		{
			/*		MENUITEMINFO mii = { 0 };
					mii.cbSize = sizeof(MENUBARINFO);
					mii.fMask = MIIM_TYPE;
					mii.fType = MFT_STRING;
					mii.dwTypeData = new TCHAR[64];
					mii.cch = 64;
					HMENU hMenu = GetMenu(hWnd);
					BOOL ret = GetMenuItemInfo(hMenu, 4, true, &mii);
					int numMenu = GetMenuItemCount(hMenu);
					UINT id = GetMenuItemID(hMenu,numMenu-3);

					ErrorExit((LPTSTR)L"");*/

			break;
		}
		}
		break;
	}
	case WM_RBUTTONUP:
	{
		HMENU hRightPopup = CreatePopupMenu();
		AppendMenu(hRightPopup, MF_STRING, 10000, L"New");
		AppendMenu(hRightPopup, MF_STRING, 10001, L"Open");
		POINT pt = { LOWORD(lParam),HIWORD(lParam) };
		ClientToScreen(hWnd, &pt);
		TrackPopupMenu(hRightPopup, TPM_LEFTALIGN, pt.x, pt.y, 0, hWnd, NULL);//屏幕坐标系
		DestroyMenu(hRightPopup);
		break;
	}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


void ErrorExit(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}
