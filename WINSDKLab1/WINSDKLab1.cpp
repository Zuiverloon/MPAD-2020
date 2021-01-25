#include <windows.h>
#include <tlhelp32.h> // 快照函数的头文件

/**************************************************************************************


WINSDKLab1
Windows process list
BY ZJY


**************************************************************************************/

// Prototype for the Window Function

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

// Prototypes of functions called by WinMain

BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

//***************************************************************************************

int WINAPI WinMain(HINSTANCE hInstance,     // 入口函数
	HINSTANCE,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	if (!InitApplication(hInstance))       // 应用初始化
		return FALSE;

	if (!InitInstance(hInstance, nCmdShow)) // 实例初始化
		return FALSE;

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))   // 消息循环
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//***************************************************************************************

BOOL InitApplication(HINSTANCE hInstance)   // 应用初始化
{
	WNDCLASS  wc;  // Data structure of the window class

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)MainWndProc;  // Name of the Window Function
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("My1stWClass");  // Name of the window class

	return RegisterClass(&wc);
}

//***************************************************************************************

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)  // 实例初始化
{
	HWND hWnd = CreateWindow(TEXT("My1stWClass"),     // Name of the window class
		TEXT("2020MPADLAB1 Windows 进程列表 学号：10185102124 姓名：章君尧"), // Title of the window
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hWnd) return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//***************************************************************************************

// 窗口过程函数

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LPCTSTR hello;
	//TCHAR temp;   // 显示的内容
    LPCTSTR inf = TEXT("进程id     模块名");
	PAINTSTRUCT ps;
	HDC hdc;
    int hor=100;
    int ver=20;
    PROCESSENTRY32 pe32;

   // 给所有进程拍快照
        HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

   // 在使用这个结构之前，先设置它的大小
        pe32.dwSize = sizeof(pe32);

  // 遍历进程快照，逐个显示进程信息
        BOOL bMore = Process32First(hProcessSnap, &pe32);
	switch (message) {

	case WM_PAINT:  // 窗口客户区得刷新
        hdc = BeginPaint(hWnd, &ps);//必写
        TextOut(hdc, hor, ver, inf, lstrlen(inf));
        ver+=20;

        while (bMore){
            TCHAR temp[256];
            wsprintf(temp,TEXT("%05x      %s"),pe32.th32ProcessID,pe32.szExeFile);
            hello =temp;
            TextOut(hdc, hor, ver, hello, lstrlen(hello));
            ver+=20;
            bMore = Process32Next(hProcessSnap, &pe32);
            if (ver>=600){
                ver=20;
                hor+=200;
                TextOut(hdc, hor, ver, inf, lstrlen(inf));
                ver+=20;
            }
        }
        CloseHandle(hProcessSnap); // 关闭snapshot对象
        EndPaint(hWnd, &ps);//必写！
		return 0;

	case WM_DESTROY: // 窗口关闭

		PostQuitMessage(0);

		return 0;

	default:  // 缺省消息的处理

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

}


