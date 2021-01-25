#include <windows.h>
#include <tlhelp32.h> // 快照函数的头文件
#include "resource.h"
//***************************************************************************************
//***************************************************************************************

#define IDM_FILE_EXIT  40005

// Prototype for the Window Function

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szAppName[] = TEXT("Resource") ;
// Prototypes of functions called by WinMain

//***************************************************************************************

int WINAPI WinMain(HINSTANCE hInstance,     // 入口函数
	HINSTANCE,
	LPSTR     lpCmdLine,
	int       iCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS  wc;  // Data structure of the window class

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)MainWndProc;  // Name of the Window Function
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	wc.lpszClassName = szAppName;  // Name of the window class



	if (!RegisterClass(&wc)) return 0;

	hwnd = CreateWindow(szAppName,TEXT("2020MPADLAB3"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);

	/*HMENU hMenu = GetMenu(hwnd);
	HMENU hMenu1=GetSubMenu(hMenu,0);
	HMENU hMenuPopup = CreateMenu();
	HMENU hMenu2 = CreateMenu();		//主菜单,水平
    HMENU hMenuPop1 = CreateMenu();

	AppendMenu(hMenuPop1,MF_STRING,IDM_FILE_EXIT,TEXT("Exit(&E)\tctrl+p"));
    InsertMenu(GetMenu(hwnd),0,MF_BYPOSITION|MF_POPUP,(unsigned int)hMenuPop1,TEXT("File(&F)"));*/

	HACCEL hAccel = LoadAccelerators(hInstance,MAKEINTRESOURCE(IDR_ACCEL));
	while (GetMessage(&msg, NULL, 0, 0))   // 消息循环
	{
		if (!TranslateAccelerator(hwnd,hAccel,&msg)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);}
	}

	return (int)msg.wParam;
}

//***************************************************************************************



//***************************************************************************************



//***************************************************************************************

// 窗口过程函数

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HMENU hMenu = GetMenu(hwnd);
	HMENU hMenu1=GetSubMenu(hMenu,0);
	HMENU hMenuPopup = CreateMenu();
	LPCTSTR text1a,text1b,text2a,text2b,text3a,text3b,text4a,text4b;
	LPCTSTR texta=TEXT("当前使用图标1"),textb=TEXT("当前使用图标2"),textc=TEXT("当前使用图标3");
    HINSTANCE hInstance;
    HMENU hMenu2 = CreateMenu();		//主菜单,水平
    HMENU hMenuPop1 = CreateMenu();	//下拉的菜单,垂直
	switch (message) {
    case WM_CREATE:

            AppendMenu(hMenuPop1,MF_STRING,IDM_FILE_EXIT,TEXT("Exit(&E)\tctrl+p"));
            InsertMenu(GetMenu(hwnd),0,MF_BYPOSITION|MF_POPUP,(unsigned int)hMenuPop1,TEXT("File(&F)"));
            SetMenu(hwnd, GetMenu(hwnd));//SetMenu(hwnd, hMenu);




    case WM_COMMAND:
        hInstance = GetModuleHandle(NULL);
        switch (LOWORD(wParam)){
            case IDM_X:
                //hdc = GetDC(hwnd);//必写
                //texta=TEXT("当前使用图标1");
                if (MessageBox(hwnd,TEXT("修改？"),TEXT("YES"),MB_YESNO|MB_ICONQUESTION)==IDYES){
                    hdc = GetDC(hwnd);
                    TextOut(hdc,50,50,texta,lstrlen(texta));
                    CheckMenuItem(hMenu, IDM_X, MF_CHECKED);
                    CheckMenuItem(hMenu, IDM_Y, MF_UNCHECKED);
                    CheckMenuItem(hMenu, IDM_Z, MF_UNCHECKED);
                    EnableMenuItem(GetMenu(hwnd),2,MF_BYPOSITION|MF_ENABLED);
                    SetMenu(hwnd,GetMenu(hwnd));
                    SetClassLong(hwnd,GCL_HICON,(long)LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON)));}
                    ReleaseDC(hwnd,hdc);//必写！
                return 0;
            case IDM_Y:
                //hdc = GetDC(hwnd);//必写
               // textb=TEXT("当前使用图标2");
                if (MessageBox(hwnd,TEXT("修改？"),TEXT("YES"),MB_YESNO|MB_ICONQUESTION)==IDYES){
                    hdc = GetDC(hwnd);
                    TextOut(hdc,50,50,textb,lstrlen(textb));
                    CheckMenuItem(hMenu, IDM_X, MF_UNCHECKED);
                    CheckMenuItem(hMenu, IDM_Y, MF_CHECKED);
                    CheckMenuItem(hMenu, IDM_Z, MF_UNCHECKED);
                    EnableMenuItem(GetMenu(hwnd),2,MF_BYPOSITION|MF_ENABLED);
                    SetMenu(hwnd,GetMenu(hwnd));
                    SetClassLong(hwnd,GCL_HICON,(long)LoadIcon(NULL,IDI_HAND));}
                    ReleaseDC(hwnd,hdc);//必写！
                return 0;
            case IDM_Z:
                //hdc = GetDC(hwnd);//必写
                //textc=TEXT("当前使用图标3");
                if (MessageBox(hwnd,TEXT("修改？"),TEXT("修改？"),MB_YESNO|MB_ICONQUESTION)==IDYES){
                    hdc = GetDC(hwnd);
                    TextOut(hdc,50,50,textc,lstrlen(textc));
                    CheckMenuItem(hMenu, IDM_X, MF_UNCHECKED);
                    CheckMenuItem(hMenu, IDM_Y, MF_UNCHECKED);
                    CheckMenuItem(hMenu, IDM_Z, MF_CHECKED);
                    EnableMenuItem(GetMenu(hwnd),2,MF_BYPOSITION|MF_GRAYED);
                    SetMenu(hwnd,GetMenu(hwnd));
                    SetClassLong(hwnd,GCL_HICON,(long)LoadIcon(NULL,IDI_APPLICATION));}
                    ReleaseDC(hwnd,hdc);//必写！
                return 0;

            case IDM_SA:
                    hdc = GetDC(hwnd);//必写
                    text1a=TEXT("显示信息1");
                    text1b=TEXT("                 ");
                    if (!GetMenuState(hMenu,IDM_SA,MF_BYCOMMAND)){
                        CheckMenuItem(hMenu, IDM_SA, MF_CHECKED);
                        TextOut(hdc,50,100,text1a,lstrlen(text1a));

                    }
                    else{
                         CheckMenuItem(hMenu, IDM_SA, MF_UNCHECKED);
                        TextOut(hdc,50,100,text1b,lstrlen(text1b));
                        //EndPaint(hwnd, &ps);//必写！
                    }
                    SetMenu(hwnd,GetMenu(hwnd));
                    ReleaseDC(hwnd,hdc);//必写！

                return 0;
            case IDM_SB:
                hdc = GetDC(hwnd);//必写
                text2a=TEXT("显示信息2");
                text2b=TEXT("                     ");
                if (!GetMenuState(hMenu,IDM_SB,MF_BYCOMMAND)){
                        CheckMenuItem(hMenu, IDM_SB, MF_CHECKED);
                        TextOut(hdc,150,100,text2a,lstrlen(text2a));

                    }
                    else{
                         CheckMenuItem(hMenu, IDM_SB, MF_UNCHECKED);
                         TextOut(hdc,150,100,text2b,lstrlen(text2b));

                    }
                     SetMenu(hwnd,GetMenu(hwnd));
                    ReleaseDC(hwnd,hdc);//必写！
                return 0;
            case IDM_SC:
                hdc = GetDC(hwnd);//必写
                text3a=TEXT("显示信息3");
                text3b=TEXT("                      ");
                if (!GetMenuState(hMenu,IDM_SC,MF_BYCOMMAND)){
                        CheckMenuItem(hMenu, IDM_SC, MF_CHECKED);
                        TextOut(hdc,50,300,text3a,lstrlen(text3a));
                    }
                    else{
                         CheckMenuItem(hMenu, IDM_SC, MF_UNCHECKED);
                         TextOut(hdc,50,300,text3b,lstrlen(text3b));
                    }
                     SetMenu(hwnd,GetMenu(hwnd));
                    ReleaseDC(hwnd,hdc);//必写！
                return 0;
            case IDM_SD:
                hdc = GetDC(hwnd);//必写
                text4a=TEXT("显示信息4");
                text4b=TEXT("                        ");
                if (!GetMenuState(hMenu,IDM_SD,MF_BYCOMMAND)){
                        CheckMenuItem(hMenu, IDM_SD, MF_CHECKED);
                        TextOut(hdc,150,300,text4a,lstrlen(text4a));
                    }
                    else{
                         CheckMenuItem(hMenu, IDM_SD, MF_UNCHECKED);
                         TextOut(hdc,150,300,text4b,lstrlen(text4b));
                    }
                     SetMenu(hwnd,GetMenu(hwnd));
                    ReleaseDC(hwnd,hdc);//必写！
                return 0;

            case IDM_INF:
                if (MessageBox(hwnd,TEXT("2020MPADLAB3 作者：章君尧 学号：10185102124"),TEXT("2020MPADLAB3"),MB_OK)==IDOK);
                SetMenu(hwnd,GetMenu(hwnd));
                return 0;
            case IDM_FILE_EXIT:
                if (MessageBox(hwnd,TEXT("关闭？"),TEXT("关闭？"),MB_YESNO|MB_ICONQUESTION)==IDYES){
                    DestroyWindow(hwnd);
                }
                SetMenu(hwnd,GetMenu(hwnd));
                return 0;

            default:  // 缺省消息的处理

		return DefWindowProc(hwnd, message, wParam, lParam);
        }

    case WM_PAINT:  // 窗口客户区得刷新
        hdc = BeginPaint(hwnd, &ps);//必写
        texta=TEXT("当前使用图标1");
        TextOut(hdc,50,50,texta,lstrlen(texta));
		EndPaint(hwnd, &ps);//必写！
		return 0;

	case WM_DESTROY: // 窗口关闭

		PostQuitMessage(0);

		return 0;

	default:  // 缺省消息的处理

		return DefWindowProc(hwnd, message, wParam, lParam);
	}

}


