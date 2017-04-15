// Project3.cpp : ����Ӧ�ó������ڵ㡣
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

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
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

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PROJECT3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT3));

	// ����Ϣѭ��:
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
//  ����: MyRegisterClass()
//;
//  Ŀ��: ע�ᴰ���ࡣ;
//
//  ע��:;
//
//    ����ϣ��;;
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��;
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��;
//    ����Ӧ�ó���Ϳ��Ի�ù�����;
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ;
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
//   ����: InitInstance(HINSTANCE, int)
//;
//   Ŀ��: ����ʵ�����������������;
//
//   ע��:;
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������;
//        ��������ʾ�����򴰿ڡ�;
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����;

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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM);
//
//  Ŀ��: ���������ڵ���Ϣ��;
//
//  WM_COMMAND	- ����Ӧ�ó���˵�;
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
POINT s_PointDown,s_PointUp,pt,point,point_e; //pt������Ļ�е�����;
int n=0,num=0; //n ��ǰ���ƵĶ���εĵ�ĸ���  num ��ǰ����εĵ�һ����;
vector<POINT>Poly;
bool WinState = false,numb=false,LB=false;//�жϴ���״̬;
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
		// �����˵�ѡ��:
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
		::GetClientRect(hWnd, &rect);//�õ����ڳߴ�;
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
// �����ڡ������Ϣ�������
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
