#pragma once

#include "resource.h"
using namespace std;
#include <vector>

extern POINT s_PointDown,s_PointUp,pt,point,point_e; //pt������Ļ�е�����;
extern int n,num; //n ��ǰ���ƵĶ���εĵ�ĸ���  num ��ǰ����εĵ�һ����;
extern vector<POINT>Poly;
extern bool WinState,numb,LB;//�жϴ���״̬;

void Move_VK_L(HWND hWnd);
void Move_VK_R(HWND hWnd);
void Move_VK_U(HWND hWnd);
void Move_VK_D(HWND hWnd);
void ROLL_VK_R(HWND hWnd);
void mouseMove(HWND hWnd,LPARAM lParam);
void RbuttonUp(HWND hWnd);
void LbuttonDown(LPARAM lParam);
void LbuttonUp(HWND hWnd,LPARAM lParam);
void winClear(HWND hWnd);
void FileSave();
void FileLoad(HWND hWnd);
void winPaint(HDC hdc);