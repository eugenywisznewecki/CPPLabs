#include <Windows.h>
#include "sp_pr1.h"


// ЗАДАНИЕ 3.8
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	LPCTSTR hello = TEXT("Привет из Win32 приложения с графическим интерфейсом\n");
	LPCTSTR lpszHeloWndTitle = MESSAGE_TITLE;

	SYSTEMTIME time, localtime;
	GetSystemTime(&time);
	GetLocalTime(&localtime);

	TCHAR bufferedResult[200] = TEXT("");
	TCHAR bufferedname[200] = TEXT("");
	lstrcpy(bufferedname, TEXT("Author Yushkevich Eugeny 70322\n"));
	
	TCHAR bufferTime[100] = TEXT("");
	wsprintf(bufferTime, TEXT("Design time <%d/%d/%d, %d:%d:%d >\n"), time.wDay, time.wMonth, time.wYear,
		time.wHour, time.wMinute, time.wSecond);

	TCHAR bufferNow[100] = TEXT("");
	wsprintf(bufferNow, TEXT("Runtime <%d/%d/%d, %d:%d:%d >\n"), localtime.wDay, localtime.wMonth, localtime.wYear,
		localtime.wHour, localtime.wMinute, localtime.wSecond);

	lstrcat(bufferedResult, hello);
	lstrcat(bufferedResult, bufferedname);
	lstrcat(bufferTime, bufferNow);
	lstrcat(bufferedResult, bufferTime);
	
	
	//MessageBox(NULL, bufferedResult, lpszHeloWndTitle, MB_OK | MB_RIGHT);


	int iRetValue1, iRetValue2;
	LPCTSTR lpszMesBoxTitle = TEXT("Var 11");

	LPTSTR lpszResponce;
	do {
		iRetValue1 = MessageBox(NULL, TEXT("The message box contains two push buttons: Retry and Cancel"), lpszMesBoxTitle,
			MB_RETRYCANCEL | MB_ICONQUESTION | MB_SETFOREGROUND | MB_DEFBUTTON1);

		switch (iRetValue1)

		{
		case IDABORT:

			lpszResponce = (LPTSTR)TEXT(" (ABORT)");

			break;

		case IDRETRY:

			lpszResponce = (LPTSTR)TEXT(" (RETRY)");

			break;


		default: lpszResponce = (LPTSTR)TEXT("Misunderstand");

		}

		TCHAR buf[200] = TEXT("");

		lstrcat(buf, lpszResponce);

		lstrcat(buf, TEXT(" Continue"));

		iRetValue2 = MessageBox(NULL, buf, lpszMesBoxTitle,

			MB_YESNO | MB_ICONQUESTION | MB_SETFOREGROUND);
	}

	while (iRetValue2 != IDNO);
	
	return 0;
}