#include "Main.h"
#include <time.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "DataBase.h"




#define szWindowClass	TEXT("MyChatDesktop")
#define szTitle			TEXT("Chat App")

#define IDC_ID		1001
#define IDC_PW		1002
#define IDC_CREATE	1003
#define IDC_LOGIN	1004
#define IDC_DELETE	1005

HINSTANCE	g_hInstance;
HWND		g_editID;
HWND		g_editPW;

TCHAR		g_ID[40];
TCHAR		g_PW[40];

DB::CDataBase* g_db;

//MainManager* manager = new MainManager();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	g_hInstance = hInstance;

	WNDCLASSEX wcex; //WindowClassExtension
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW; //class style Horizental Vertical
	wcex.lpfnWndProc = (WNDPROC)WndProc; //���������� �����ؼ� ��
	wcex.cbClsExtra = 0; // �Ⱦ�
	wcex.cbWndExtra = 0; // �Ⱦ�
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); //�⺻Ŀ�� 

	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //��
	wcex.lpszMenuName = NULL;//wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //������ ����
	wcex.lpszClassName = szWindowClass;

	if (!RegisterClassEx(&wcex)) //��ω���� �˻�. ������ġ
		return 0;

	//������ ����
	HWND	hWnd = CreateWindowEx(WS_EX_APPWINDOW //Ŭ�����̸�
		, szWindowClass //�������̸�
		, szTitle //ĸ�� �� ���ڿ�
		, WS_OVERLAPPEDWINDOW //������ ��Ÿ��
		, CW_USEDEFAULT //�������� ��ǥ
		, CW_USEDEFAULT //�������� ��ǥ
		, 800 //width
		, 600 //height
		, NULL //�θ� ������
		, NULL //�޴�
		, hInstance //�ν��Ͻ� �ڵ�
		, NULL); // �����Ķ���, ������ ������

	if (!hWnd)
		return 0;

	ShowWindow(hWnd, nCmdShow); //�����츦 �����ִ� �Լ�

	MSG		msg;
	while (GetMessage(&msg, NULL, 0, 0)) //�޼��� ȹ��
	{
		TranslateMessage(&msg); //�̺�Ʈ ����
		DispatchMessage(&msg); //��� �߼�
	}

	return (int)msg.wParam;
}


// ������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd
	, UINT message
	, WPARAM wParam
	, LPARAM lParam)
{
	HDC	hdc;
	PAINTSTRUCT	ps;

	switch (message)
	{
		case WM_CREATE: //window message �ʱ�ȭ�ϴºκ�
		{
			g_db = new DB::CDataBase();
			if (g_db->Init() == false)
			{
				std::cout << "ERROR : DBConnect" << std::endl;
				getchar();
				exit(1);
			}

			g_editID = CreateWindow(TEXT("edit"), TEXT("ID"), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
				10, 10, 100, 30, hWnd, (HMENU)IDC_ID, g_hInstance, NULL);

			g_editPW = CreateWindow(TEXT("edit"), TEXT("PassWord"), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
				10, 50, 100, 30, hWnd, (HMENU)IDC_PW, g_hInstance, NULL);

			CreateWindow(TEXT("button"), TEXT("CreateUser"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				210, 10, 100, 30, hWnd, (HMENU)IDC_CREATE, g_hInstance, NULL);

			CreateWindow(TEXT("button"), TEXT("Login"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				210, 50, 100, 30, hWnd, (HMENU)IDC_LOGIN, g_hInstance, NULL);

			CreateWindow(TEXT("button"), TEXT("DeleteUser"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				210, 90, 100, 30, hWnd, (HMENU)IDC_DELETE, g_hInstance, NULL);
		}
			break;

		case WM_PAINT:
		{

		}
			break;

		case WM_DESTROY:
		{
			g_db->Destroy();

			delete g_db;
			g_db = nullptr;

			PostQuitMessage(0);
			return 0;
		}
			break;
	
		default:
			break;
	}

	//button
	switch (LOWORD(wParam))
	{
	case IDC_ID:
	{
		OutputDebugStringW(L"ID\n");

		TCHAR str[40];
		GetWindowText(g_editID, str, 40);
//		int len = GetWindowTextLength(g_editID);
// 		char buf[128];
// 		memset(buf, '\0', sizeof(char) * 128);
// 		WideCharToMultiByte(CP_ACP, 0, str, len, buf, len, NULL, NULL);

		memset(g_ID, '\0', sizeof(TCHAR) * 40);

		wcscat_s(g_ID, str);
	}
	break;

	case IDC_PW:
	{
		OutputDebugStringW(L"PW\n");
		TCHAR str[40];
		GetWindowText(g_editPW, str, 128);

		memset(g_PW, '\0', sizeof(TCHAR) * 40);

		wcscat_s(g_PW, str);
	}
	break;

	case IDC_CREATE:
	{
		OutputDebugStringW(L"test\n");
		
		if (g_db->CreateUser(g_ID, g_PW) == false)
		{
			MessageBox(
				NULL,
				(LPCWSTR)L"Can't Create Account.",
				(LPCWSTR)L"Create User",
				MB_ICONWARNING | MB_OK | MB_DEFBUTTON1
			);
		}
		else
		{
			MessageBox(
				NULL,
				(LPCWSTR)L"Completely Create Account.",
				(LPCWSTR)L"Create User",
				MB_ICONWARNING | MB_OK | MB_DEFBUTTON1
			);
		}
	}
	break;

	case IDC_LOGIN:
	{
		OutputDebugStringW(L"test\n");
		
		if (g_db->Login(g_ID, g_PW) == false)
		{
			MessageBox(
				NULL,
				(LPCWSTR)L"Can't Login Account.",
				(LPCWSTR)L"Login",
				MB_ICONWARNING | MB_OK | MB_DEFBUTTON1
			);
		}
		else
		{
			MessageBox(
				NULL,
				(LPCWSTR)L"Login Successful.",
				(LPCWSTR)L"Login",
				MB_ICONWARNING | MB_OK | MB_DEFBUTTON1
			);
		}
	}
	break;

	case IDC_DELETE:
	{
		OutputDebugStringW(L"test\n");
		
		if (g_db->DeleteUser(g_ID, g_PW) == false)
		{
			MessageBox(
				NULL,
				(LPCWSTR)L"Can't Delete Account.",
				(LPCWSTR)L"Login",
				MB_ICONWARNING | MB_OK | MB_DEFBUTTON1
			);
		}
		else
		{
			//set user state LOGIN
			MessageBox(
				NULL,
				(LPCWSTR)L"Delete Your Account.",
				(LPCWSTR)L"Login",
				MB_ICONWARNING | MB_OK | MB_DEFBUTTON1
			);
		}
	}
	break;

	default:
			break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}