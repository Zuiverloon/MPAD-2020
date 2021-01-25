#include<windows.h>
#include<stdlib.h>
#include<string.h>
#include "resource.h"
#include <iostream>
#include <commdlg.h>

/***************************************************************************
WINSDKLab5
Font&Text Common Dialogs
didn't upload the resources(icon,cursor,menu,bitmap,etc...)
maybe some bugs unfixed
ECNU 10185102124 ZJY
***************************************************************************/



//#define IDM_FILE_EXIT 40001
//#define IDM_HELP_ABOUT 40002
using namespace std;
long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam);
BOOL InitWindowsClass(HINSTANCE hInstance);
BOOL InitWindows(HINSTANCE hInstance,int nCmdShow);
#include "resource.h"
#include <iostream>
#include <commdlg.h>
BOOL InitWindowsClass(HINSTANCE hInstance)//初始化窗口类
{
		WNDCLASS WndClass;
		WndClass.cbClsExtra=0;
		WndClass.cbWndExtra=0;
		WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));
		WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
		WndClass.hIcon=LoadIcon(NULL,"END");
		WndClass.hInstance=hInstance;
		WndClass.lpfnWndProc=WndProc;
		WndClass.lpszClassName="WinText";
		WndClass.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);
		WndClass.style=CS_HREDRAW|CS_VREDRAW;
		return RegisterClass(&WndClass);
}

BOOL InitWindows(HINSTANCE hInstance,int nCmdShow) //初始化窗口
{
	HWND hWnd;
		hWnd=CreateWindow("WinText",  //生成窗口
						"2020MPADLAB9",
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						0,
						CW_USEDEFAULT,
						0,
						NULL,
						NULL,
						hInstance,
						NULL);
		if(!hWnd)
			return FALSE;
		ShowWindow(hWnd,nCmdShow);//显示窗口
		UpdateWindow(hWnd);
		return TRUE;
}
//主函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	HINSTANCE hInst;
	hInst =  hPrevInstance;
	MSG Message;
	if(!InitWindowsClass(hInstance))		return FALSE;
	if(!InitWindows(hInstance,nCmdShow))	return FALSE;
	while(GetMessage(&Message,0,0,0))		//消息循环
		{TranslateMessage(&Message);
		 DispatchMessage(&Message);
        }
	return Message.wParam;
}

long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam)
{

    HINSTANCE hInst;
    static long nXChar,nCaps,nYChar;
  int pointx,pointy,i,j;
  HDC hDC=GetDC(hWnd);   					//定义指向设备环境的句柄
  TEXTMETRIC tm;				//存放字体各种属性的结构体变量
  PAINTSTRUCT PtStr; 			//指向包含绘图信息的结构体变量
  TCHAR *textbuf[4]={"故人西辞黄鹤楼", "烟花三月下扬州","孤帆远影碧空尽", "唯见长江天际流"};

  CHOOSEFONT cf;            // common dialog box structure
        static LOGFONT lf;        // logical font structure
        static DWORD rgbCurrent;  // current text color
        HFONT hfont, hfontPrev;
        DWORD rgbPrev;
        HMENU hMenu= LoadMenu (hInst, MAKEINTRESOURCE(IDR_MENU1) ) ;

HMENU topMenu=CreateMenu();
HMENU Popup=CreateMenu();
//AppendMenu(Popup,MF_STRING,IDM_FILE_EXIT,"Exit");
     //AppendMenu(topMenu,MF_POPUP,(UINT)Popup,"File");

    // AppendMenu(Popup,MF_STRING,IDM_HELP_ABOUT,"About");
     //AppendMenu(topMenu,MF_POPUP,(UINT)Popup,"Help");

  switch(iMessage)  					//处理消息
  {	case WM_CREATE:						//处理窗口创建消息
	 hDC=GetDC(hWnd) ;   				//获取当前设备表句柄
	 GetTextMetrics(hDC,&tm); 			//获取字体信息
	 nXChar=tm.tmAveCharWidth;  			//获取字符宽度
     nYChar=tm.tmHeight+tm.tmExternalLeading;	//字符高度
	 nCaps=(tm.tmPitchAndFamily&1?3:2)*nXChar/2;	//字间距
	 ReleaseDC(hWnd,hDC); return 0;		//释放当前设备句柄


     SetMenu(hWnd, topMenu);//SetMenu(hwnd, hMenu);
     DrawMenuBar(hWnd);

     /*file=CreatePopupMenu();
     help=CreatePopupMenu();
     InsertMenu(topMenu,0,MF_BYPOSITION,(UINT)file,"File");
     AppendMenu(topMenu,0,1,"About");
     SetMenu(hWnd,topMenu);*/

	case WM_RBUTTONUP:




// Initialize CHOOSEFONT
        ZeroMemory(&cf, sizeof(cf));
        cf.lStructSize = sizeof (cf);
        cf.hwndOwner = hWnd;
        cf.lpLogFont = &lf;
        cf.rgbColors = rgbCurrent;
        cf.Flags = CF_SCREENFONTS | CF_EFFECTS|CF_INITTOLOGFONTSTRUCT;

        if (ChooseFont(&cf)==TRUE)
        {
            hfont = CreateFontIndirect(cf.lpLogFont);
            hfontPrev = (HFONT)SelectObject(hDC, hfont);
            rgbCurrent= cf.rgbColors;
            rgbPrev = SetTextColor(hDC, rgbCurrent);
        }
        /*hDC=GetDC(hWnd) ;
        SelectObject(hDC,(HFONT)hfont);
        SetTextColor(hDC,rgbCurrent);
        GetTextMetrics(hDC,&tm); 			//获取字体信息
	 nXChar=tm.tmAveCharWidth;  			//获取字符宽度
     nYChar=tm.tmHeight+tm.tmExternalLeading;	//字符高度
	 nCaps=(tm.tmPitchAndFamily&1?3:2)*nXChar/2;
        for(i=4;i>0;i--)
	 {for(j=0;j<7;j++)					//输出文本
        {  pointx=100+i*nXChar*5;	pointy=50+j*(nYChar+nCaps);
	       TextOut(hDC,pointx,pointy,textbuf[4-i]+j*2,2);
	    }
	 }
	 ReleaseDC(hWnd,hDC);*/
	 InvalidateRect(hWnd,NULL,TRUE);
	 break;

case WM_PAINT: 						//处理重画消息
	hDC=BeginPaint(hWnd,&PtStr); 		//开始绘图
	hfont=CreateFontIndirect(&lf);
	SelectObject(hDC,(HFONT)hfont);
    SetTextColor(hDC,rgbCurrent);
    GetTextMetrics(hDC,&tm); 			//获取字体信息
	 nXChar=tm.tmAveCharWidth;  			//获取字符宽度
     nYChar=tm.tmHeight+tm.tmExternalLeading;	//字符高度
	 nCaps=(tm.tmPitchAndFamily&1?3:2)*nXChar/2;
	 for(i=4;i>0;i--)
	 {for(j=0;j<7;j++)					//输出文本
        {  pointx=100+i*nXChar*5;	pointy=50+j*(nYChar+nCaps);
	       TextOut(hDC,pointx,pointy,textbuf[4-i]+j*2,2);
	    }
	 }
     EndPaint(hWnd,&PtStr); return 0; 		//结束绘图

     /*case WM_PAINT: 						//处理重画消息
	hDC=BeginPaint(hWnd,&PtStr); 		//开始绘图
	hfont=CreateFontIndirect(&lf);
	SelectObject(hDC,(HFONT)hfont);
    SetTextColor(hDC,rgbCurrent);
    GetTextMetrics(hDC,&tm);
	  nXChar=tm.tmAveCharWidth;  			//获取字符宽度
     nYChar=tm.tmHeight+tm.tmExternalLeading;	//字符高度
	 nCaps=(tm.tmPitchAndFamily&1?3:2)*nXChar/2;	//字间距
	 for(i=4;i>0;i--)
	 {for(j=0;j<7;j++)					//输出文本
        {  pointx=100+i*nXChar*5;	pointy=50+j*(nYChar+nCaps);
	       TextOut(hDC,pointx,pointy,textbuf[4-i]+j*2,2);
	    }
	 }
	 cout<<"paint!"<<endl;


     EndPaint(hWnd,&PtStr); return 0; 		//结束绘图*/

     case WM_COMMAND:
          switch (LOWORD(wParam)) {
                case ID_HELP_ABOUT:
                 if (MessageBox(hWnd,TEXT("2020MPADLAB 作者：章君尧 学号：10185102124"),TEXT("2020MPADLAB"),MB_OK)==IDOK);
                 break;

                case ID_FILE_EXIT:
                DestroyWindow(hWnd);
                break;

                default:
                return (DefWindowProc(hWnd, iMessage, wParam, lParam));
          }
          break;



	case WM_DESTROY: //结束应用程序
	 PostQuitMessage(0);	return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
  }
}


