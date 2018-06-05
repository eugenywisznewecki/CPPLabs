#include <windows.h>
#include <tchar.h>

//-- Prototypes -------------------
LRESULT CALLBACK SimWndProc(HWND, UINT, WPARAM, LPARAM);
//-- Global Variables ------------
//  Стартовая функция

int APIENTRY _tWinMain(HINSTANCE hInstance,			//дескриптор, который Windows присваивает запущенному приложению
	HINSTANCE hPrevInstance,						//не  используется (использовался в старых версиях)
	LPTSTR lpszCmdLine,								//указатель на строку, в которую копируются аргументы приложений из командной строки
	int nCmdShow)									//целое значение, которое может быть передано функции ShowWindow
{
	WNDCLASSEX wc;
	MSG msg;
	HWND hWnd;

	HBRUSH hbr = CreateSolidBrush(RGB(50, 50, 50));			// цвет кисти!!!
																// Регистрация класса окна приложения
	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);									//размер структуры в байтах
	wc.lpszClassName = TEXT("SimpleClassName");						//указатель на строку, содержащую имя класса окна
	wc.lpfnWndProc = SimWndProc;									//указатель на оконную процедуру
	wc.style = CS_VREDRAW | CS_HREDRAW;								//стиль класса окна (перерисовать окно если размер изменен по горизонтали или вертикали)
	wc.hInstance = hInstance;										//дескриптор экземпляра приложения, в котором находится оконная процедура для этого класса
	wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_WARNING));	//дескриптор пиктограммы	IDI_HAND	IDI_APPLICATION		IDI_ASTERISK	IDI_WARNING
	wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEALL));		//дескриптор курсора			IDC_ARROW	IDC_HAND	IDC_IBEAM	IDC_SIZEALL
	wc.hbrBackground = hbr;					//дескриптор кисти, используемый для закраски фона окна
											//		(HBRUSH)(COLOR_WINDOW + 1);		// стаедартный цвет по умолчанию
	wc.lpszMenuName = NULL;											//указатель на строку, содержащую имя меню, применяемого по умолчанию для этого класса
	wc.cbClsExtra = 0;												// число дополнительных байтов, которые должны быть распределены в конце структуры класса
	wc.cbWndExtra = 0;												//число дополнительных байтов, которые должны быть распределены вслед за экземпляром класса

	if (!RegisterClassEx(&wc))				//регистрация класса окна, расширенная версия RegisterClass
	{
		MessageBox(NULL, TEXT("Ошибка регистрации класса окна!"),
			TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	//	Создание главного окна
	hWnd = CreateWindowEx(NULL, TEXT("SimpleClassName"),			//расширенный стиль окна
		TEXT("Simple Application with Message handling"),			//имя окна
		WS_OVERLAPPEDWINDOW,										//стиль окна
		100,						//горизонтальная позиция		0
		100,						//вертикальная позиция			0
		100,									//ширина окна		CW_USEDEFAULT
		100,									//высота окна		CW_USEDEFAULT
		NULL,				//дескриптор родительского окна
		NULL,					//дескриптор меню окна или идентификатор элемента управления
		hInstance,					//дескриптор экземпляра приложения
		NULL						//указатель на данны, передаваемые в приложении WM_CREATE
	);		//отработав функция возвращает дескриптор созданного окна

	if (!hWnd)				//проверка значения, которое вернула функция CreateWindowEx, т.к. окно могло не создаться (hWnd=NULL)
	{
		MessageBox(NULL, TEXT("Окно не создано!"),
			TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);			//функция для отображения на экране созданного окна
	UpdateWindow(hWnd);					//посылает оконной процедуре сообщение WM_PAINT


										//		Запуск цикла выборки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// Оконная процедура
LRESULT CALLBACK SimWndProc(HWND hWnd,			//дескриптор окна, получающего сообщение
	UINT msg,									//идентификатор сообщения
	WPARAM wParam,								//дополнительная информация, к-рая распознается системой
	LPARAM lParam)								//	 в зависимости от типа получаемого сообщения
{
	HDC hDC;
	switch (msg)
	{
	case WM_PAINT:    // Вывод при обновлении окна
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps); // Получение контекста для
									 // обновления окна 
		TextOut(hDC, 10, 10, TEXT("Hello, World!"), 13); // Вывод в контекст
		EndPaint(hWnd, &ps); // Завершение обновления окна
		break;
	case WM_DESTROY:  // Завершение работы приложения
		PostQuitMessage(0); // Посылка WM_QUIT приложению
		break;
	default: // Вызов "Обработчика по умолчанию"
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return FALSE;// Для ветвей с "break"
}