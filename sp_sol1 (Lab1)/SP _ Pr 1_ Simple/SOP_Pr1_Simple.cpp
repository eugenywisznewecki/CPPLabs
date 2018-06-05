#include <windows.h>
#include <tchar.h>

//-- Prototypes -------------------
LRESULT CALLBACK SimWndProc(HWND, UINT, WPARAM, LPARAM);
//-- Global Variables ------------
//  ��������� �������

int APIENTRY _tWinMain(HINSTANCE hInstance,			//����������, ������� Windows ����������� ����������� ����������
	HINSTANCE hPrevInstance,						//��  ������������ (������������� � ������ �������)
	LPTSTR lpszCmdLine,								//��������� �� ������, � ������� ���������� ��������� ���������� �� ��������� ������
	int nCmdShow)									//����� ��������, ������� ����� ���� �������� ������� ShowWindow
{
	WNDCLASSEX wc;
	MSG msg;
	HWND hWnd;

	HBRUSH hbr = CreateSolidBrush(RGB(50, 50, 50));			// ���� �����!!!
																// ����������� ������ ���� ����������
	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);									//������ ��������� � ������
	wc.lpszClassName = TEXT("SimpleClassName");						//��������� �� ������, ���������� ��� ������ ����
	wc.lpfnWndProc = SimWndProc;									//��������� �� ������� ���������
	wc.style = CS_VREDRAW | CS_HREDRAW;								//����� ������ ���� (������������ ���� ���� ������ ������� �� ����������� ��� ���������)
	wc.hInstance = hInstance;										//���������� ���������� ����������, � ������� ��������� ������� ��������� ��� ����� ������
	wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_WARNING));	//���������� �����������	IDI_HAND	IDI_APPLICATION		IDI_ASTERISK	IDI_WARNING
	wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEALL));		//���������� �������			IDC_ARROW	IDC_HAND	IDC_IBEAM	IDC_SIZEALL
	wc.hbrBackground = hbr;					//���������� �����, ������������ ��� �������� ���� ����
											//		(HBRUSH)(COLOR_WINDOW + 1);		// ����������� ���� �� ���������
	wc.lpszMenuName = NULL;											//��������� �� ������, ���������� ��� ����, ������������ �� ��������� ��� ����� ������
	wc.cbClsExtra = 0;												// ����� �������������� ������, ������� ������ ���� ������������ � ����� ��������� ������
	wc.cbWndExtra = 0;												//����� �������������� ������, ������� ������ ���� ������������ ����� �� ����������� ������

	if (!RegisterClassEx(&wc))				//����������� ������ ����, ����������� ������ RegisterClass
	{
		MessageBox(NULL, TEXT("������ ����������� ������ ����!"),
			TEXT("������"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	//	�������� �������� ����
	hWnd = CreateWindowEx(NULL, TEXT("SimpleClassName"),			//����������� ����� ����
		TEXT("Simple Application with Message handling"),			//��� ����
		WS_OVERLAPPEDWINDOW,										//����� ����
		100,						//�������������� �������		0
		100,						//������������ �������			0
		100,									//������ ����		CW_USEDEFAULT
		100,									//������ ����		CW_USEDEFAULT
		NULL,				//���������� ������������� ����
		NULL,					//���������� ���� ���� ��� ������������� �������� ����������
		hInstance,					//���������� ���������� ����������
		NULL						//��������� �� �����, ������������ � ���������� WM_CREATE
	);		//��������� ������� ���������� ���������� ���������� ����

	if (!hWnd)				//�������� ��������, ������� ������� ������� CreateWindowEx, �.�. ���� ����� �� ��������� (hWnd=NULL)
	{
		MessageBox(NULL, TEXT("���� �� �������!"),
			TEXT("������"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);			//������� ��� ����������� �� ������ ���������� ����
	UpdateWindow(hWnd);					//�������� ������� ��������� ��������� WM_PAINT


										//		������ ����� ������� ���������
	while (GetMessage(&msg, NULL, 0, 0))
	{
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// ������� ���������
LRESULT CALLBACK SimWndProc(HWND hWnd,			//���������� ����, ����������� ���������
	UINT msg,									//������������� ���������
	WPARAM wParam,								//�������������� ����������, �-��� ������������ ��������
	LPARAM lParam)								//	 � ����������� �� ���� ����������� ���������
{
	HDC hDC;
	switch (msg)
	{
	case WM_PAINT:    // ����� ��� ���������� ����
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps); // ��������� ��������� ���
									 // ���������� ���� 
		TextOut(hDC, 10, 10, TEXT("Hello, World!"), 13); // ����� � ��������
		EndPaint(hWnd, &ps); // ���������� ���������� ����
		break;
	case WM_DESTROY:  // ���������� ������ ����������
		PostQuitMessage(0); // ������� WM_QUIT ����������
		break;
	default: // ����� "����������� �� ���������"
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return FALSE;// ��� ������ � "break"
}