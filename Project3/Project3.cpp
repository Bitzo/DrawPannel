// Project3.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Project3.h"
#include <Windows.h>
#include <WindowsX.h>
#include <MMSystem.h>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <commdlg.h>
using namespace std;
#pragma comment(lib,"WINMM.LIB")

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PROJECT3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT3));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//;
//  目的: 注册窗口类。;
//
//  注释:;
//
//    仅当希望;;
//    此代码与添加到 Windows 95 中的“RegisterClassEx”;
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，;
//    这样应用程序就可以获得关联的;
//    “格式正确的”小图标。;
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT3));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_PROJECT3);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//;
//   函数: InitInstance(HINSTANCE, int)
//;
//   目的: 保存实例句柄并创建主窗口;
//
//   注释:;
//
//        在此函数中，我们在全局变量中保存实例句柄并;
//        创建和显示主程序窗口。;
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中;

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//;
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM);
//
//  目的: 处理主窗口的消息。;
//
//  WM_COMMAND	- 处理应用程序菜单;
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
POINT s_PointDown,s_PointUp,pt,point,point_e; //pt接收屏幕中点坐标;
int n=0,num=0; //n 当前绘制的多边形的点的个数  num 当前多边形的第一个点;
vector<POINT>Poly;
bool WinState = false,numb=false,LB=false;//判断窗口状态;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc,hMemDC;
	RECT rect;
	HBITMAP hBmp;
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_START:
			WinState=true;
			break;
		case IDM_CLEAR:
			winClear(hWnd);
			break;
		case IDM_SAVE:
			FileSave();
			break;
		case IDM_LOAD:
			FileLoad(hWnd);
			break;
		}
	case WM_RBUTTONUP:
		RbuttonUp(hWnd);
		break;
	case WM_LBUTTONDOWN:
		LbuttonDown(lParam);
		break;
	case WM_LBUTTONUP:
		LbuttonUp(hWnd,lParam);
		break;
	case WM_MOUSEMOVE:
		mouseMove(hWnd,lParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd,&rect);
		hMemDC = CreateCompatibleDC(hdc);
		hBmp = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
		SelectObject(hMemDC,hBmp);
		FillRect(hMemDC,&rect,NULL);

		//Draw Something .//
		winPaint(hMemDC);

		BitBlt(hdc,0,0,rect.right,rect.bottom,hMemDC,0,0,SRCAND);
		DeleteObject(hBmp);
		DeleteDC(hMemDC);
		
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch (wParam) 
		{
		case VK_LEFT: 
			Move_VK_L(hWnd);
			break; 
		case VK_RIGHT:
			Move_VK_R(hWnd);
			break; 
		case VK_UP:   
			Move_VK_U(hWnd);
			break;
		case VK_DOWN: 
			Move_VK_D(hWnd);
			break;
		case 'R':
		case 'r':			
			ROLL_VK_R(hWnd);
			break;
		}
		break;
	case WM_SIZE:
		::GetClientRect(hWnd, &rect);//得到窗口尺寸;
		pt.x = (rect.right-rect.left)/2.0;
		pt.y = (rect.bottom-rect.top)/2.0; 
		::InvalidateRect(hWnd, NULL, 1);
		numb=true;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
