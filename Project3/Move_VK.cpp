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

void Move_VK_L(HWND hWnd)
{
	for(int i=0;i<Poly.size();++i)
	{
		if (Poly[i].x==0) continue;
		Poly[i].x -= 10;
	}
	numb=true;
	::InvalidateRect(hWnd, NULL, 1);
}
void Move_VK_R(HWND hWnd)
{
	for(int i=0;i<Poly.size();++i)
	{
		if (Poly[i].x==0) continue;
		Poly[i].x += 10;
	}
	numb=true;
	::InvalidateRect(hWnd, NULL, 1);
}
void Move_VK_U(HWND hWnd)
{
	for(int i=0;i<Poly.size();++i)
	{
		if (Poly[i].x==0) continue;
		Poly[i].y -= 10;
	}
	numb=true;
	::InvalidateRect(hWnd, NULL, 1);
}
void Move_VK_D(HWND hWnd)
{
	for(int i=0;i<Poly.size();++i)
	{
		if (Poly[i].x==0) continue;
		Poly[i].y += 10;
	}
	numb=true;
	::InvalidateRect(hWnd, NULL, 1);
}
void ROLL_VK_R(HWND hWnd)
{
	for(int i=0;i<Poly.size();++i)
	{
		if (Poly[i].x==0) continue;
		double x = Poly[i].x;
		double y = Poly[i].y;
		Poly[i].x = (x-pt.x)*cos(0.6)-(y-pt.y)*sin(0.6)+pt.x;
		Poly[i].y = (y-pt.y)*cos(0.6)+(x-pt.x)*sin(0.6)+pt.y;
	}
	numb=true;
	::InvalidateRect(hWnd, NULL, 1);
}
void mouseMove(HWND hWnd,LPARAM lParam)
{
	if (GetKeyState(VK_CONTROL)<0&&LB==true)
	{	
		point.x=GET_X_LPARAM(lParam);
		point.y=GET_Y_LPARAM(lParam);
		double x=point_e.x-point.x;
		double y=point_e.y-point.y;
		for(int i=0;i<Poly.size();++i)
		{
			if (Poly[i].x==0) continue;
			Poly[i].x -= x;
			Poly[i].y -= y;
			point_e.x=point.x;
			point_e.y=point.y;
		}
		numb=true;
		::InvalidateRect(hWnd, NULL, 1);
	}
	
}
void RbuttonUp(HWND hWnd)
{
	if(Poly.size()&&n!=0)
	{	
		::InvalidateRect(hWnd, NULL, 1);
		Poly[Poly.size()-1].x=Poly[num].x;
		Poly[Poly.size()-1].y=Poly[num].y;
		s_PointUp.x=s_PointUp.y=0;
		Poly.push_back(s_PointUp);
		numb=true;
		num = num+n+1;
		n=0;
		::InvalidateRect(hWnd, NULL, 1);
	}
}
void LbuttonDown(LPARAM lParam)
{
	s_PointDown.x = GET_X_LPARAM(lParam); 
	s_PointDown.y = GET_Y_LPARAM(lParam); 
	point_e.x=s_PointDown.x;
	point_e.y=s_PointDown.y;
	if (WinState==true)
		if(!(GetKeyState(VK_CONTROL)<0))
			n++;
	LB=true;
}

void LbuttonUp(HWND hWnd,LPARAM lParam)
{
	s_PointUp.x = GET_X_LPARAM(lParam); 
	s_PointUp.y = GET_Y_LPARAM(lParam);
	LB=false;
	if(!(GetKeyState(VK_CONTROL)<0))
		if (WinState==true) {
			Poly.push_back(s_PointUp);
			::InvalidateRect(hWnd, NULL, 0);
		}
}
void winClear(HWND hWnd)
{
	Poly.clear();
	::InvalidateRect(hWnd, NULL, 1);
	n=0;num=0;
}
void FileSave()
{
	OPENFILENAME ofn = { 0 };  
	TCHAR strFilename[MAX_PATH] = TEXT("Polygon");
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = TEXT("多边形数据 (*.prj)\0*.prj\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = strFilename;
	ofn.nMaxFile = sizeof(strFilename);
	ofn.lpstrInitialDir = NULL;
	ofn.Flags =  OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrTitle = TEXT("保存到");  
	ofn.lpstrDefExt = TEXT("prj");
	if (GetSaveFileName(&ofn))
		MessageBox(NULL, strFilename, TEXT("保存到"), 0);   
	FILE *fp;
	if((fp=fopen(ofn.lpstrFile,"wb"))!=NULL) 
	for(int i=0;i<Poly.size();++i)
		fprintf(fp,"%d %d ",Poly[i].x,Poly[i].y);
	fclose(fp);
}

void winPaint(HDC hdc)
{
	if(WinState==true){
		if(n>1)
		{
			MoveToEx(hdc,Poly[Poly.size()-2].x,Poly[Poly.size()-2].y,NULL);
			LineTo(hdc,Poly[Poly.size()-1].x,Poly[Poly.size()-1].y);	
		}
		if(numb==true&&Poly.size())
		{
			for(int i=0;i<Poly.size()-1;++i)
			{
				if (Poly[i+1].x==0) 
				{	i++;
				continue;
				}
				MoveToEx(hdc,Poly[i].x,Poly[i].y,NULL);
				LineTo(hdc,Poly[i+1].x,Poly[i+1].y);
			}
		}
		numb=false;
	}
}
void FileLoad(HWND hWnd)
{
	OPENFILENAME ofn;
	TCHAR ext[] = TEXT(".dat");
	TCHAR szFile[MAX_PATH] = TEXT("Polygon.prj");
	TCHAR szFilter[] = TEXT("多边形数据 (*.prj)\0*.prj\0")
		TEXT("All Files (*.*)\0*.*\0\0");

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize  = sizeof(ofn);
	ofn.hwndOwner	 = hWnd;
	ofn.lpstrFilter  = szFilter;
	ofn.nFilterIndex = 1;		  
	ofn.lpstrFile	 = szFile;
	ofn.nMaxFile	 = MAX_PATH;
	ofn.lpstrDefExt  = ext;
	ofn.Flags	 = OFN_PATHMUSTEXIST|OFN_OVERWRITEPROMPT;
	if(GetOpenFileName(&ofn))
	{
		WinState=true;
		Poly.clear();
		num=0;
		n=0;
		FILE *fp;
		fp=fopen(ofn.lpstrFile,"r");
		int i=0;
		for (i=0;!feof(fp);++i)
		{
			fscanf(fp,"%d %d",&s_PointDown.x,&s_PointDown.y);
			Poly.push_back(s_PointDown);
			num++;
		}
		Poly.pop_back();
		num--;
		fclose(fp);
		::InvalidateRect(hWnd, NULL, 1);
		numb=true;
	}
}