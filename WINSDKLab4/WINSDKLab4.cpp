#include <windows.h>
#include "resource.h"
#include <iostream>
#include <commdlg.h>

using namespace std;

/***************************************************************************
WINSDKLab4
Drawing Beizer Curves
didn't upload the resources(icon,cursor,menu,bitmap,etc...)
maybe some bugs unfixed
ECNU 10185102124 ZJY
***************************************************************************/






POINT RecentC[4];
POINT RecentT[3];

int RCn=0;
int RTn=0;


LRESULT CALLBACK MainWndProc(HWND,UINT,WPARAM,LPARAM);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE,int);
HINSTANCE hInst;      // current instance
HWND hWnd;

int WINAPI WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{  if (!InitApplication(hInstance)) return FALSE;

   if (!InitInstance(hInstance,nCmdShow)) return FALSE;

   MSG msg;
   while (GetMessage(&msg, NULL, 0, 0))
   {
       TranslateMessage(&msg);
       DispatchMessage(&msg);
   }
   return (int)msg.wParam;
}

BOOL InitApplication(HINSTANCE hInstance)
{
    WNDCLASS  wc;

    wc.style         = NULL;
    wc.lpfnWndProc   = (WNDPROC)MainWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wc.lpszClassName = TEXT("2020MPADLAB");
    wc.lpszMenuName  = MAKEINTRESOURCE(CURVEMENU);
    return RegisterClass(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd  =     CreateWindow(TEXT("2020MPADLAB"),
                            TEXT("2020MPADLAB "),
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
   nCmdShow=SW_SHOWMAXIMIZED;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   HDC hdc;
   static int draw=0;
   static POINT point[4];
   static POINT trianglepoint[3];
   static int triState=0;
   static int nState=0;
   static BOOL fErase=FALSE;
   int xPos,yPos;
   HMENU hMenu= LoadMenu (hInst, MAKEINTRESOURCE(CURVEMENU) ) ;

   switch (message) {
      case WM_LBUTTONDOWN:
          //cout<<draw<<endl;
          xPos=LOWORD(lParam);   yPos=HIWORD(lParam);
          SetCapture(hWnd);
          hdc=GetDC(hWnd);
          SetROP2(hdc,R2_NOTXORPEN);
          if (draw==0){
          switch (nState){
            case 0:
              point[0].x=xPos;  point[0].y=yPos;
              nState=1;
              break;
            case 2:
              MoveToEx(hdc,point[0].x,point[0].y,NULL);
              LineTo(hdc,point[3].x,point[3].y);
              point[1].x=xPos;   point[1].y=yPos;
              point[2].x=xPos;   point[2].y=yPos;
              PolyBezier(hdc,point,4);
              nState=3;
              fErase=TRUE;
              break;
            case 4:
              PolyBezier(hdc,point,4);
              point[2].x=xPos;   point[2].y=yPos;
              PolyBezier(hdc,point,4);
              nState=5;
              fErase=TRUE;
              break;}
          }
          else if (draw==1){
            switch(triState){
            case 0:
                trianglepoint[0].x=xPos;trianglepoint[0].y=yPos;
                triState=1;
                break;
            case 2:
                triState=3;
                MoveToEx(hdc,trianglepoint[0].x, trianglepoint[0].y, NULL);
                LineTo(hdc,trianglepoint[2].x,trianglepoint[2].y);
                trianglepoint[1].x=xPos;trianglepoint[1].y=yPos;
                Polyline(hdc,trianglepoint,3);
                fErase=TRUE;
                break;
            }
          }
          ReleaseDC(hWnd,hdc);
          break;

      case WM_LBUTTONUP:
         // cout<<draw<<endl;
          xPos=LOWORD(lParam);   yPos=HIWORD(lParam);
          fErase=FALSE;
          if (draw==0){
          switch (nState){
            case 1:
              point[3].x=xPos;   point[3].y=yPos;
              nState=2;
              break;
            case 3:
              point[1].x=xPos;   point[1].y=yPos;
              nState=4;
              break;
            case 5:
              point[2].x=xPos;   point[2].y=yPos;
              nState=0;
              break;
          }}
          else if (draw==1){
            switch(triState){
            case 1:
                trianglepoint[2].x=xPos;trianglepoint[2].y=yPos;
                triState=2;
                break;
            case 3:
                trianglepoint[1].x=xPos;trianglepoint[1].y=yPos;
                triState=0;
                break;}
          }
          ReleaseCapture();
          break;
      case WM_MOUSEMOVE:
   //       cout<<draw<<endl;
          xPos=LOWORD(lParam);         yPos=HIWORD(lParam);
          if(draw==0 &&wParam&MK_LBUTTON){
              hdc=GetDC(hWnd);
              SetROP2(hdc,R2_NOTXORPEN);
              switch (nState){
                case 1:
                    if(fErase){
                        MoveToEx(hdc,point[0].x,point[0].y,NULL);
                        LineTo(hdc,point[3].x,point[3].y);
                    }
                    point[3].x=xPos;    point[3].y=yPos;
                    MoveToEx(hdc,point[0].x,point[0].y,NULL);
                    LineTo(hdc,point[3].x,point[3].y);
                  break;
                case 3:
                   // cout<<"a"<<endl;
                    if(fErase)  PolyBezier(hdc,point,4);
                    point[1].x=xPos;     point[1].y=yPos;
                    point[2].x=xPos;     point[2].y=yPos;
                    PolyBezier(hdc,point,4);
                    break;
                case 5:
                    //cout<<"b"<<endl;
                    if(fErase)  PolyBezier(hdc,point,4);
                    point[2].x=xPos;     point[2].y=yPos;
                    PolyBezier(hdc,point,4);
                    break;
              }
              fErase=TRUE;
              ReleaseDC(hWnd,hdc);
          }
          else if (draw==1 &&wParam&MK_LBUTTON){
                hdc=GetDC(hWnd);
                SetROP2(hdc,R2_NOTXORPEN);
                switch(triState){
                case 1:
                    //cout<<"a"<<endl;
                    if (fErase){
                        MoveToEx(hdc,trianglepoint[0].x,trianglepoint[0].y,NULL);
                        LineTo(hdc,trianglepoint[2].x,trianglepoint[2].y);
                    }
                    trianglepoint[2].x=xPos;trianglepoint[2].y=yPos;
                    MoveToEx(hdc,trianglepoint[0].x,trianglepoint[0].y,NULL);
                    LineTo(hdc,trianglepoint[2].x,trianglepoint[2].y);
                    break;

                case 3:
                   //cout<<"b"<<endl;
                   if (fErase){
                        Polyline(hdc,trianglepoint,3);
                    }
                    trianglepoint[1].x=xPos;trianglepoint[1].y=yPos;
                    /*MoveToEx(hdc,trianglepoint[0].x,trianglepoint[0].y,NULL);
                    LineTo(hdc,trianglepoint[1].x,trianglepoint[1].y);
                    MoveToEx(hdc,trianglepoint[1].x,trianglepoint[1].y,NULL);
                    LineTo(hdc,trianglepoint[2].x,trianglepoint[2].y);*/
                    MoveToEx(hdc,trianglepoint[0].x,trianglepoint[0].y,NULL);
                    LineTo(hdc,trianglepoint[2].x,trianglepoint[2].y);
                    Polyline(hdc,trianglepoint,3);
                    break;
                }
                fErase=TRUE;
              ReleaseDC(hWnd,hdc);
          }
          break;

      case WM_COMMAND:
          switch (LOWORD(wParam)) {
            case ID_HELP_ABOUT:
                 if (MessageBox(hWnd,TEXT("2020MPADLAB 作者：章君尧 学号：10185102124"),TEXT("2020MPADLAB"),MB_OK)==IDOK);
                SetMenu(hWnd,GetMenu(hWnd));
                break;

            case ID_FILE_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDM_CURVE:
                draw=0;
                //cout<<draw<<endl;
                CheckMenuRadioItem(hMenu,IDM_CURVE,ID_DRAW_TRIANGLE,IDM_CURVE,MF_BYCOMMAND);
                SetMenu(hWnd,hMenu);
                break;

            case ID_DRAW_TRIANGLE:
                draw=1;
               // cout<<draw<<endl;
                CheckMenuRadioItem(hMenu,IDM_CURVE,ID_DRAW_TRIANGLE,ID_DRAW_TRIANGLE,MF_BYCOMMAND);
                SetMenu(hWnd,hMenu);
                break;

            case ID_FILE_SAVE:
                if (draw==0){
                    RCn=1;
                    RecentC[0].x=point[0].x;
                    RecentC[0].y=point[0].y;
                    RecentC[1].x=point[1].x;
                    RecentC[1].y=point[1].y;
                    RecentC[2].x=point[2].x;
                    RecentC[2].y=point[2].y;
                    RecentC[3].x=point[3].x;
                    RecentC[3].y=point[3].y;
                }
                else if (draw==1){
                    RTn=1;
                    RecentT[0].x=trianglepoint[0].x;
                    RecentT[0].y=trianglepoint[0].y;
                    RecentT[1].x=trianglepoint[1].x;
                    RecentT[1].y=trianglepoint[1].y;
                    RecentT[2].x=trianglepoint[2].x;
                    RecentT[2].y=trianglepoint[2].y;
                }
                 if (MessageBox(hWnd,TEXT("Save Successfully!"),TEXT("Save"),MB_OK)==IDOK);
                SetMenu(hWnd,GetMenu(hWnd));
                break;

            case ID_FILE_RECENT:
                if  (RCn!=0){
                    hdc=GetDC(hWnd);
                    SetROP2(hdc,R2_NOTXORPEN);
                    PolyBezier(hdc,RecentC,4);
                    ReleaseDC(hWnd,hdc);
                }
                if (RTn!=0){
                    hdc=GetDC(hWnd);
                    SetROP2(hdc,R2_NOTXORPEN);
                    Polyline(hdc,RecentT,3);
                    ReleaseDC(hWnd,hdc);
                }
                break;
            case IDM_NEW:
                InvalidateRect(hWnd,NULL,TRUE);
                if (MessageBox(hWnd,TEXT("New Successfully!"),TEXT("New"),MB_OK)==IDOK);
                break;
            case ID_FILE_OPEN:
                    if (MessageBox(hWnd,TEXT("I don't know how to open."),TEXT("Open"),MB_OK)==IDOK);

                    break;


            default:
                return (DefWindowProc(hWnd, message, wParam, lParam));
         }
         break;

      case WM_DESTROY:
         PostQuitMessage(0);
         break;

      default:
         return (DefWindowProc(hWnd, message, wParam, lParam));
   }
   return 0;
}






