#include<Windows.h>


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPreInstance, _In_ LPSTR lpCmdLine, _In_ INT nCmdShow)
{
	//register Class
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;	//DefWindowProcĬ�Ϻ���û�������˳�����ʹX�������ʵ���ϻ����ں�̨���У���Ϣѭ���޷��˳�
	wc.hInstance = hInstance;
	wc.lpszClassName = L"WindowsLearn";
	RegisterClass(&wc);

	//

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
	while (GetMessage(&msg,NULL,msgFilterMin,msgFilterMax))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);	//�߳���Ϣ�ַ������ڣ�һ���߳̿��ж�����ڣ�
	}
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
