#include <windows.h>
#include "resource.h"

/***************************************************************************
WINSDKLab3
Using resources(dialogs,icons)
switching between English/Chinese
didn't upload the resources(icon,cursor,menu,bitmap,etc...)
maybe some bugs unfixed
ECNU 10185102124 ZJY
***************************************************************************/

// Prototype for the Window Function

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szAppName[] = TEXT("Resource") ;
// Prototypes of functions called by WinMain

//***************************************************************************************
HWND hDlgModeless=0;
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
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = szAppName;  // Name of the window class



	if (!RegisterClass(&wc)) return 0;
    TCHAR text[256];
    LoadString(hInstance,IDS_INFTC,text,256);
	hwnd = CreateWindow(szAppName,text,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);


	HACCEL hAccel = LoadAccelerators(hInstance,MAKEINTRESOURCE(IDR_ACCEL));
	//HWND hDlgModeless=0;
	while (GetMessage(&msg, NULL, 0, 0))   // 消息循环
	{
		if ((!IsWindow(hDlgModeless)||!IsDialogMessage(hDlgModeless,&msg))&&!TranslateAccelerator(hwnd,hAccel,&msg)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);}
	}

	return (int)msg.wParam;
}

//***************************************************************************************

int ic1=0,ic2=0,ic3=0,icc1=0,icc2=0,icc3=0;
int c1=1,c2=0,c3=0;

//***************************************************************************************
BOOL CALLBACK D1Proc(HWND hDlg, UINT uMsg,WPARAM wParam,LPARAM lParam){
    switch (uMsg){
        case WM_INITDIALOG:
            if (ic1==1){
                CheckDlgButton(hDlg,IDC_CHECK1,BST_CHECKED);
            }
            else if (ic1==0){
                CheckDlgButton(hDlg,IDC_CHECK1,BST_UNCHECKED);
            }
            if (ic2==1){
                CheckDlgButton(hDlg,IDC_CHECK2,BST_CHECKED);
            }
            else if (ic2==0){
                CheckDlgButton(hDlg,IDC_CHECK2,BST_UNCHECKED);
            }
            if (ic3==1){
                CheckDlgButton(hDlg,IDC_CHECK3,BST_CHECKED);
            }
            else if (ic3==0){
                CheckDlgButton(hDlg,IDC_CHECK3,BST_UNCHECKED);
            }
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
            case IDC_CHECK1:
                ic1++;
                ic1%=2;
                return FALSE;
            case IDC_CHECK2:
                ic2++;
                ic2%=2;
                return FALSE;
            case IDC_CHECK3:
                ic3++;
                ic3%=2;
                return FALSE;
            case IDOK:

                EndDialog(hDlg,0);
                return TRUE;

            case IDCANCEL:
                EndDialog(hDlg,0);
                return FALSE;
            }
            break;
            //return TRUE;
        case WM_PAINT:
        default:return FALSE;
    }
}

BOOL CALLBACK D2Proc(HWND hDlg, UINT uMsg,WPARAM wParam,LPARAM lParam){
    switch (uMsg){
    case WM_INITDIALOG:
         if (icc1==1){
                CheckDlgButton(hDlg,IDC_RADIO1,BST_CHECKED);
            }
            else if (icc1==0){
                CheckDlgButton(hDlg,IDC_RADIO1,BST_UNCHECKED);
            }
            if (icc2==1){
                CheckDlgButton(hDlg,IDC_RADIO2,BST_CHECKED);
            }
            else if (icc2==0){
                CheckDlgButton(hDlg,IDC_RADIO2,BST_UNCHECKED);
            }
            if (icc3==1){
                CheckDlgButton(hDlg,IDC_RADIO3,BST_CHECKED);
            }
            else if (icc3==0){
                CheckDlgButton(hDlg,IDC_RADIO3,BST_UNCHECKED);
            }
            return TRUE;
    case WM_COMMAND:
            switch (LOWORD(wParam))
            {
            case IDC_RADIO1:
                icc1=1;
                icc2=0;
                icc3=0;
                return FALSE;

            case IDC_RADIO2:
                icc2=1;
                icc3=0;
                icc1=0;
                return FALSE;
            case IDC_RADIO3:
                icc3=1;
                icc2=0;
                icc1=0;
                return FALSE;

            case IDOK:
                InvalidateRect(GetParent(hDlg),NULL,TRUE);
                DestroyWindow(hDlg);
                hDlgModeless=0;
                return TRUE;

            case IDCANCEL:
                InvalidateRect(GetParent(hDlg),NULL,TRUE);
                DestroyWindow(hDlg);
                hDlgModeless=0;
                return TRUE;
            }
        //InvalidateRect(GetParent(hDlg),NULL,TRUE);
        return TRUE;
        default:return FALSE;
    }
}
//***************************************************************************************

// 窗口过程函数

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
    HMENU hMenu=GetMenu(hwnd);
    HINSTANCE hInstance;
    TCHAR text[256],text1[256];
	switch (message) {
        case WM_CREATE:
           // InvalidateRect(hwnd,NULL,TRUE);
        case WM_COMMAND:
            hInstance = GetModuleHandle(NULL);
            OPENFILENAME ofn;
            TCHAR szFile[256];
            switch (LOWORD(wParam)){
                case ID_40030:
                PostQuitMessage(0);
                return 0;

                case ID_FILE_EXIT:
                PostQuitMessage(0);
                return 0;

                case ID_40031:
                        DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG1),hwnd,(DLGPROC)D1Proc);
                        InvalidateRect(hwnd,NULL,TRUE);
                    return 0;
                case ID_DIALOG_MODALDIALOG:
                        DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG1),hwnd,(DLGPROC)D1Proc);
                        InvalidateRect(hwnd,NULL,TRUE);
                    return 0;

                case ID_40032:
                    if (!IsWindow(hDlgModeless)){
                    hDlgModeless=CreateDialog(hInstance,MAKEINTRESOURCE(IDD_DIALOG2),hwnd,(DLGPROC)D2Proc);

                    ShowWindow(hDlgModeless,SW_SHOW);
                    InvalidateRect(hwnd,NULL,TRUE);}
                    //UpdateWindow(hwnd);
                    //InvalidateRect(hwnd,NULL,TRUE);}
                    return 0;

                case ID_DIALOG_MODALLESSDIALOG:
                    if (!IsWindow(hDlgModeless)){
                    hDlgModeless=CreateDialog(hInstance,MAKEINTRESOURCE(IDD_DIALOG2),hwnd,(DLGPROC)D2Proc);

                    ShowWindow(hDlgModeless,SW_SHOW);
                    InvalidateRect(hwnd,NULL,TRUE);}
                    //UpdateWindow(hwnd);
                    //InvalidateRect(hwnd,NULL,TRUE);}
                    return 0;

                case ID_40033:
                    ZeroMemory(&ofn, sizeof(ofn));
                    ofn.lStructSize = sizeof(ofn);
                    ofn.hwndOwner = hwnd;
                    ofn.lpstrFile = szFile;
                    //ofn.lpstrFile[0] = TEXT('/0');
                    ofn.nMaxFile = sizeof(szFile);
                    ofn.lpstrFilter = NULL;
                    ofn.nFilterIndex = 1;
                    ofn.lpstrFileTitle = NULL;
                    ofn.nMaxFileTitle = 0;
                    ofn.lpstrInitialDir = NULL;
                    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                    //if()
                    if ( GetOpenFileNameA(&ofn)==TRUE )
                    {
	//显示选择的文件。
                        LoadString(hInstance,IDS_FSC,text,256);
                        MessageBox(NULL,szFile,text,MB_OK);
                    }
                    return 0;

                case ID_DIALOG_FILEDIALOG:
                    ZeroMemory(&ofn, sizeof(ofn));
                    ofn.lStructSize = sizeof(ofn);
                    ofn.hwndOwner = hwnd;
                    ofn.lpstrFile = szFile;
                    //ofn.lpstrFile[0] = TEXT('/0');
                    ofn.nMaxFile = sizeof(szFile);
                    ofn.lpstrFilter = NULL;
                    ofn.nFilterIndex = 1;
                    ofn.lpstrFileTitle = NULL;
                    ofn.nMaxFileTitle = 0;
                    ofn.lpstrInitialDir = NULL;
                    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                    //if()
                    if ( GetOpenFileNameA(&ofn)==TRUE )
                    {
	//显示选择的文件。
                        LoadString(hInstance,IDS_FSE,text,256);
                        MessageBox(NULL,szFile,text,MB_OK);
                    }
                    return 0;

                case ID_40034:
                    hdc=GetDC(hwnd);
                    c1=1;c2=0;c3=0;
                    LoadString(hInstance,IDS_C1+0,text,256);
                  //  TextOut(hdc,50,50,TEXT("              "),lstrlen(TEXT("             ")));
                    TextOut(hdc,50,50,text,lstrlen(text));
                    SetClassLong(hwnd,GCL_HCURSOR,(long)LoadCursor(NULL,IDC_ARROW));
                    CheckMenuItem(hMenu, ID_40034, MF_CHECKED);
                    CheckMenuItem(hMenu, ID_40035, MF_UNCHECKED);
                    CheckMenuItem(hMenu, ID_40036, MF_UNCHECKED);
                    ReleaseDC(hwnd,hdc);//必写！
                    return 0;

                case ID_CURSOR_CURSOR1:
                    hdc=GetDC(hwnd);
                    c1=1;c2=0;c3=0;
                    LoadString(hInstance,IDS_C1+100,text,256);
                  //  TextOut(hdc,50,50,TEXT("              "),lstrlen(TEXT("             ")));
                    TextOut(hdc,50,50,text,lstrlen(text));
                    SetClassLong(hwnd,GCL_HCURSOR,(long)LoadCursor(NULL,IDC_ARROW));
                    CheckMenuItem(hMenu, ID_CURSOR_CURSOR1, MF_CHECKED);
                    CheckMenuItem(hMenu, ID_CURSOR_CURSOR2, MF_UNCHECKED);
                    CheckMenuItem(hMenu, ID_CURSOR_CURSOR3, MF_UNCHECKED);
                    ReleaseDC(hwnd,hdc);//必写！
                    return 0;

                case ID_40035:
                    hdc=GetDC(hwnd);
                    c1=0;c2=1;c3=0;
                    LoadString(hInstance,IDS_C2+0,text,256);
                  //  TextOut(hdc,50,50,TEXT("              "),lstrlen(TEXT("             ")));
                    TextOut(hdc,50,50,text,lstrlen(text));
                    SetClassLong(hwnd,GCL_HCURSOR,(long)LoadCursor(NULL,IDC_CROSS));
                    CheckMenuItem(hMenu, ID_40034, MF_UNCHECKED);
                    CheckMenuItem(hMenu, ID_40035, MF_CHECKED);
                    CheckMenuItem(hMenu, ID_40036, MF_UNCHECKED);
                    ReleaseDC(hwnd,hdc);//必写！
                    return 0;

                case ID_CURSOR_CURSOR2:
                    hdc=GetDC(hwnd);
                    c1=0;c2=1;c3=0;
                    LoadString(hInstance,IDS_C2+100,text,256);
                 //   TextOut(hdc,50,50,TEXT("              "),lstrlen(TEXT("             ")));
                    TextOut(hdc,50,50,text,lstrlen(text));
                    SetClassLong(hwnd,GCL_HCURSOR,(long)LoadCursor(NULL,IDC_CROSS));
                    CheckMenuItem(hMenu, ID_CURSOR_CURSOR1, MF_UNCHECKED);
                    CheckMenuItem(hMenu, ID_CURSOR_CURSOR2, MF_CHECKED);
                    CheckMenuItem(hMenu, ID_CURSOR_CURSOR3, MF_UNCHECKED);
                    ReleaseDC(hwnd,hdc);//必写！
                    return 0;

                case ID_40036:
                    hdc=GetDC(hwnd);
                    c1=0;c2=0;c3=1;
                    LoadString(hInstance,IDS_C3,text,256);
                  //  TextOut(hdc,50,50,TEXT("              "),lstrlen(TEXT("             ")));
                    TextOut(hdc,50,50,text,lstrlen(text));
                    SetClassLong(hwnd,GCL_HCURSOR,(long)LoadCursor(hInstance,MAKEINTRESOURCE(IDC_CURSOR1)));
                    CheckMenuItem(hMenu, ID_40034, MF_UNCHECKED);
                    CheckMenuItem(hMenu, ID_40035, MF_UNCHECKED);
                    CheckMenuItem(hMenu, ID_40036, MF_CHECKED);
                    ReleaseDC(hwnd,hdc);//必写！
                    return 0;
                case ID_CURSOR_CURSOR3:
                    hdc=GetDC(hwnd);
                    c1=0;c2=0;c3=1;
                    LoadString(hInstance,IDS_C3+100,text,256);
                   // TextOut(hdc,50,50,TEXT("              "),lstrlen(TEXT("             ")));
                    TextOut(hdc,50,50,text,lstrlen(text));
                    SetClassLong(hwnd,GCL_HCURSOR,(long)LoadCursor(hInstance,MAKEINTRESOURCE(IDC_CURSOR1)));
                    CheckMenuItem(hMenu, ID_CURSOR_CURSOR1, MF_UNCHECKED);
                    CheckMenuItem(hMenu, ID_CURSOR_CURSOR2, MF_UNCHECKED);
                    CheckMenuItem(hMenu, ID_CURSOR_CURSOR3, MF_CHECKED);
                    ReleaseDC(hwnd,hdc);//必写！
                    return 0;

                case ID_40038:
                    hMenu=LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU2));
                    hdc=GetDC(hwnd);
                    TextOut(hdc,50,50,TEXT("              "),lstrlen(TEXT("             ")));
                    if (c1==1)LoadString(hInstance,IDS_C1+100,text,256);TextOut(hdc,50,50,TEXT("              "),lstrlen(TEXT("             ")));TextOut(hdc,50,50,text,lstrlen(text));
                    if (c2==1)LoadString(hInstance,IDS_C2+100,text,256);TextOut(hdc,50,50,TEXT("              "),lstrlen(TEXT("             ")));TextOut(hdc,50,50,text,lstrlen(text));
                    if (c3==1)LoadString(hInstance,IDS_C3+100,text,256);TextOut(hdc,50,50,TEXT("              "),lstrlen(TEXT("             ")));TextOut(hdc,50,50,text,lstrlen(text));
                    ReleaseDC(hwnd,hdc);//必写！
                    SetMenu(hwnd,hMenu);
                    TCHAR text1[256];
                    LoadString(hInstance,IDS_INFTE,text1,256);
                    SetWindowText(hwnd,text1);
                   // ShowWindow(hwnd,iCmdShow);
                    UpdateWindow(hwnd);
                    return 0;

                case ID_LANGUAGE_CHINESE:
                    hMenu=LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU1));
                    hdc=GetDC(hwnd);
                    TextOut(hdc,50,50,TEXT("              "),lstrlen(TEXT("             ")));
                    if (c1==1)LoadString(hInstance,IDS_C1+0,text,256);TextOut(hdc,50,50,TEXT("              "),lstrlen(TEXT("             ")));TextOut(hdc,50,50,text,lstrlen(text));
                    if (c2==1)LoadString(hInstance,IDS_C2+0,text,256);TextOut(hdc,50,50,TEXT("              "),lstrlen(TEXT("             ")));TextOut(hdc,50,50,text,lstrlen(text));
                    if (c3==1)LoadString(hInstance,IDS_C3+0,text,256);TextOut(hdc,50,50,TEXT("              "),lstrlen(TEXT("             ")));TextOut(hdc,50,50,text,lstrlen(text));
                    ReleaseDC(hwnd,hdc);//必写！
                    SetMenu(hwnd,hMenu);
                    text1[256];
                    LoadString(hInstance,IDS_INFTC,text1,256);
                    SetWindowText(hwnd,text1);
                    UpdateWindow(hwnd);
                    return 0;

                case ID_40039:
                LoadString(hInstance,IDS_INFAC,text,256);
                LoadString(hInstance,IDS_INFTC,text1,256);
                if (MessageBox(hwnd,text,text1,MB_OK)==IDOK);
                SetMenu(hwnd,GetMenu(hwnd));
                return 0;

                case ID_ABOUT_INFORMATION:
                LoadString(hInstance,IDS_INFAE,text,256);
                LoadString(hInstance,IDS_INFTE,text1,256);
                if (MessageBox(hwnd,text,text1,MB_OK)==IDOK);
                SetMenu(hwnd,GetMenu(hwnd));
                return 0;

                default:  // 缺省消息的处理

                    return DefWindowProc(hwnd, message, wParam, lParam);
         }

   case WM_PAINT:  // 窗口客户区得刷新
        hdc=BeginPaint(hwnd, &ps);//必写
        HINSTANCE hInstance;//=GetModuleHandle(NULL);
        PAINTSTRUCT ps;
        HBITMAP hB;
        BITMAP bitmap;
        HDC hMemDc;
        int width,height;
        TCHAR text3[256];
		if (c1==1){
                hInstance=GetModuleHandle(NULL);
                LoadString(hInstance,IDS_C1+0,text3,256);
                TextOut(hdc,50,50,text3,lstrlen(text3));
		}
		if (ic1==1){
            hInstance = GetModuleHandle(NULL);
            hB=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP1));
            GetObject(hB,sizeof(BITMAP),&bitmap);
            width=bitmap.bmWidth;
            height=bitmap.bmHeight;
            hMemDc=CreateCompatibleDC(hdc);
            SelectObject(hMemDc,hB);
            BitBlt(hdc,100,200,width,height,hMemDc,0,0,SRCCOPY);
            DeleteDC(hMemDc);
            DeleteObject(hB);}
        if (ic2==1){
            hInstance = GetModuleHandle(NULL);
            hB=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP2));
            GetObject(hB,sizeof(BITMAP),&bitmap);
            width=bitmap.bmWidth;
            height=bitmap.bmHeight;
            hMemDc=CreateCompatibleDC(hdc);
            SelectObject(hMemDc,hB);
            BitBlt(hdc,100,300,width,height,hMemDc,0,0,SRCCOPY);
            DeleteDC(hMemDc);
            DeleteObject(hB);}
        if (ic3==1){
            hInstance = GetModuleHandle(NULL);
            hB=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP3));
            GetObject(hB,sizeof(BITMAP),&bitmap);
            width=bitmap.bmWidth;
            height=bitmap.bmHeight;
            hMemDc=CreateCompatibleDC(hdc);
            SelectObject(hMemDc,hB);
            BitBlt(hdc,100,400,width,height,hMemDc,0,0,SRCCOPY);
            DeleteDC(hMemDc);
            DeleteObject(hB);}
        if (icc1==1){
            hInstance = GetModuleHandle(NULL);
            hB=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP1));
            GetObject(hB,sizeof(BITMAP),&bitmap);
            width=bitmap.bmWidth;
            height=bitmap.bmHeight;
            //hdc=BeginPaint(hDlg,&ps);
            hMemDc=CreateCompatibleDC(hdc);
            SelectObject(hMemDc,hB);
            BitBlt(hdc,200,200,width,height,hMemDc,0,0,SRCCOPY);
            DeleteDC(hMemDc);
            DeleteObject(hB);}
        if (icc2==1){
            hInstance = GetModuleHandle(NULL);
            hB=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP2));
            GetObject(hB,sizeof(BITMAP),&bitmap);
            width=bitmap.bmWidth;
            height=bitmap.bmHeight;
            //hdc=BeginPaint(hDlg,&ps);
            hMemDc=CreateCompatibleDC(hdc);
            SelectObject(hMemDc,hB);
            BitBlt(hdc,200,300,width,height,hMemDc,0,0,SRCCOPY);
            DeleteDC(hMemDc);
            DeleteObject(hB);}
        if (icc3==1){
            hInstance = GetModuleHandle(NULL);
            hB=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP3));
            GetObject(hB,sizeof(BITMAP),&bitmap);
            width=bitmap.bmWidth;
            height=bitmap.bmHeight;
            //hdc=BeginPaint(hDlg,&ps);
            hMemDc=CreateCompatibleDC(hdc);
            SelectObject(hMemDc,hB);
            BitBlt(hdc,200,400,width,height,hMemDc,0,0,SRCCOPY);
            DeleteDC(hMemDc);
            DeleteObject(hB);}
		EndPaint(hwnd, &ps);//必写！
		return 0;

	case WM_DESTROY: // 窗口关闭

		PostQuitMessage(0);

		return 0;
    case WM_CLOSE:
        DestroyWindow(hDlgModeless);
        hDlgModeless=0;

	default:  // 缺省消息的处理

		return DefWindowProc(hwnd, message, wParam, lParam);
	}

}
