// WindowsMessageTimeDelayTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<Windows.h>
#include<conio.h>
#include<iostream>
using namespace std;
#define WM_TEST WM_USER+80
#define WM_STOP WM_USER+90

int time[20];   //��¼��ʱʱ��
int time2[20];

DWORD WINAPI PeekMessageThread(LPVOID param)
{
	int k=0;
	MSG msg;
	while(1)
	{
		int i=PeekMessage(&msg,NULL,0,0,PM_REMOVE);
	if(0!=i)
	{
		if(msg.message==WM_TEST)
		{
			LARGE_INTEGER nCounter1,nCounter2,nCounter3,nFrequency;
			QueryPerformanceCounter(&nCounter2);
			QueryPerformanceFrequency(&nFrequency);//QueryPerformanceCounter(&nFrequency);
			//cout<<"���յ�WM_TEST"<<endl;
			int a,t;
			nCounter1=*(LARGE_INTEGER*)msg.lParam;
			a=*((int*)(msg.wParam));
			t=(1000*1000*(nCounter2.QuadPart-nCounter1.QuadPart))/(double)nFrequency.QuadPart;
			time[k]=t;
			QueryPerformanceCounter(&nCounter3);
			t=(1000*1000*(nCounter3.QuadPart-nCounter2.QuadPart))/(double)nFrequency.QuadPart;
			time2[k]=t;
			k++;
			//cout<<"���յ��������ǣ�"<<a<<"   WindowsMessage���ݺķ���"<<t<<"΢��"<<endl;
		}else if(msg.message==WM_STOP)
		{
			LARGE_INTEGER nCounter1,nCounter2,nFrequency;
			QueryPerformanceCounter(&nCounter2);
			QueryPerformanceFrequency(&nFrequency);
			nCounter1=*(LARGE_INTEGER*)msg.lParam;
			int t=1000*1000*(nCounter2.QuadPart-nCounter1.QuadPart)/(double)nFrequency.QuadPart;
			cout<<"����WM_STOP��Ϣ��������"<<t<<"΢��"<<endl;
			cout<<"Test Stop!"<<endl;
			break;
		}
	}
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	
	HANDLE hThread;
	DWORD threadID;
	hThread=CreateThread(NULL,0,PeekMessageThread,NULL,0,&threadID);
	Sleep(5000);
	WPARAM wParam;
	LPARAM lParam;
	int j=6;
	wParam=(WPARAM)&j;
	LARGE_INTEGER nCounter1;
	QueryPerformanceCounter(&nCounter1);
    lParam=(LPARAM)&nCounter1;
	for(int i=0;i<10;i++)
	{
	PostThreadMessage(threadID,WM_TEST,wParam,lParam);
	Sleep(10);
	}
	//Sleep(5000);
	QueryPerformanceCounter(&nCounter1);
	lParam=(LPARAM)&nCounter1;
	PostThreadMessage(threadID,WM_STOP,wParam,lParam);
	cout<<"����WM_TEST��ʱ��"<<endl;
	for(int i=0;i<10;i++)
	{
		cout<<time[i]<<"  ";
	}
	cout<<endl;
	cout<<"ÿ��Peekѭ����ʱ��"<<endl;
    for(int i=0;i<10;i++)
	{
		cout<<time2[i]<<"  ";
	}
	cout<<endl;

	getch();

	return 0;
}

