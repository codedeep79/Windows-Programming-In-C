#include<windows.h>
#include<stdlib.h>
#include<stdio.h>


#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 0
#define FILE_SUB_MENU_NEW 3
#define FILE_SUB_MENU_DIALOG 5
#define GENERATE_BUTTON 4
#define FILE_SUB_MENU_OPEN_DIALOG 6

LRESULT CALLBACK WindowsProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK DialogProcedure(HWND, UINT, WPARAM, LPARAM);

HMENU hMenu;
HWND hEdit, hName, hAge, hOut, hButton, hLogo, hMainWindow, hEditDialog;
HBITMAP hLogoImage, hGenerate;
void addMenus(HWND);
void addControls(HWND);
void loadImages(HWND);
void registerDialogClass(HINSTANCE);
void displayDialogBox(HWND);
void openFileDialog(HWND);
void displayContentFile(char*);

int WINAPI WinMain(HINSTANCE HInstance, HINSTANCE HPrevInstance, PSTR szCmdLine, int iCmdShow){
	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = HInstance;
	wc.lpszClassName = L"MyWindows";
	wc.lpfnWndProc = WindowsProcedure;

	if (!RegisterClassW(&wc))
		return -1;
	
	//1. Register Dialog Class
	registerDialogClass(HInstance);

	
	hMainWindow = CreateWindowW(L"MyWindows", L"Windows Application", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 700, 500,
		NULL, NULL, NULL, NULL);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}


LRESULT CALLBACK WindowsProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg)
	{
		int val1;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_CREATE:
			addMenus(hWnd);
			addControls(hWnd);

			
			break;
		case WM_COMMAND:
			switch (wp)
			{
				case FILE_MENU_NEW:
					MessageBeep(MB_OK);
					break;
				case FILE_MENU_OPEN:
					MessageBeep(MB_ICONINFORMATION);
					break;
				case FILE_SUB_MENU_DIALOG:
					// 2. Create Windows For Dialog
					displayDialogBox(hWnd);
					MessageBeep(MB_OK);
					break;
				case FILE_MENU_EXIT:
					val1 = MessageBoxW(hWnd, L"Are You Sure?", L"Notify !!!", MB_YESNO | MB_ICONEXCLAMATION);
					if (val1 == IDYES)
					{
						DestroyWindow(hWnd);

					}
					break;		
				case GENERATE_BUTTON:
					char name[30], age[10], out[50];
					GetWindowText(hName, name, 30);
					GetWindowText(hAge, age, 10);

					if (strcpy_s(out, "") == 0 || strcpy_s(out, "") == 0)
					{
						val1 = MessageBoxW(hWnd, L"You didn't enter anything!", NULL, MB_ABORTRETRYIGNORE);
						switch (val1)
						{
							case IDABORT:
								DestroyWindow(hWnd);
							case IDRETRY:
								return 0;
							case IDIGNORE:
								break;
						}
					}
					strcpy_s(out, name);
					strcat_s(out, " is ");
					strcat_s(out, age);
					strcat_s(out, " years old ");

					SetWindowText(hOut, out);
					break;
			}
			break;
	default: 
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void addMenus(HWND hWnd) {
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hFileSubMenu = CreateMenu();

	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR) hFileSubMenu, "New");
	AppendMenu(hFileSubMenu, MF_STRING, FILE_SUB_MENU_NEW, "New File");

	AppendMenu(hFileSubMenu, MF_STRING, FILE_SUB_MENU_DIALOG, "New Dialog");
	
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_OPEN, "Open");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hFileMenu, "File");
	AppendMenu(hMenu, MF_STRING, NULL, "Help");
	
	SetMenu(hWnd, hMenu);

}

void addControls(HWND hWnd) {

	CreateWindowW(L"static", L"Name: ", WS_VISIBLE | WS_CHILD, 100, 50, 100, 40,
		hWnd, NULL, NULL, NULL);
	hName = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 40, 200, 40,
		hWnd, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Age: ", WS_VISIBLE | WS_CHILD, 100, 90, 100, 40,
		hWnd, NULL, NULL, NULL);
	hAge =  CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 80, 200, 40,
		hWnd, NULL, NULL, NULL);

	hButton = CreateWindowW(L"button", L"Generate", WS_VISIBLE | WS_CHILD | WS_BORDER, 250, 130, 90, 40,
		hWnd, (HMENU) GENERATE_BUTTON, NULL, NULL);

	hOut = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 190, 300, 200,
		hWnd, NULL, NULL, NULL);

	
}

/*-------------- Dialog -------------------------*/
void registerDialogClass(HINSTANCE hInstances) {
	WNDCLASSW dialog = { 0 };
	dialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
	dialog.hCursor = LoadCursor(NULL, IDC_ARROW);
	dialog.hInstance = hInstances;
	dialog.lpszClassName = L"Dialog1";
	dialog.lpfnWndProc = DialogProcedure;

	RegisterClassW(&dialog);
}

LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
		case WM_COMMAND:
			switch (wp)
			{
			case FILE_SUB_MENU_OPEN_DIALOG:
				EnableWindow(hWnd, true);
				openFileDialog(hWnd);
				break;
			}
			break;
		case WM_CLOSE:
			EnableWindow(hWnd, true);
			DestroyWindow(hWnd);
			break;

		default: 
			return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void openFileDialog(HWND hWnd) {
	OPENFILENAME openFileName;
	ZeroMemory(&openFileName, sizeof(OPENFILENAME));
	char file_name[100];
	openFileName.lStructSize = sizeof(OPENFILENAME);
	
	// Handle Windows Owner
	openFileName.hwndOwner = hWnd;

	// Use file_name to assign file name
	openFileName.lpstrFile = file_name;
	openFileName.lpstrFile[0] = '\0';
	
	openFileName.nMaxFile = 100;
	openFileName.lpstrFilter = "All File\0*.*\0Source File\0*.cpp\0TEXT Files\0*.txt\0";
	openFileName.nFilterIndex = 1;

	GetOpenFileName(&openFileName);
	//MessageBox(NULL, openFileName.lpstrFile, "", MB_OK);
	displayContentFile(openFileName.lpstrFile);
}

void displayContentFile(char* path)
{
	errno_t err;
	FILE *f;
	err = fopen_s(&f, path, "rb");
	if (err == 0)
	{
		fseek(f, 0, SEEK_END);

		int _size = ftell(f);
		rewind(f);
		char *data = new char[_size + 1];
		fread(data, _size, 1, f);
		data[_size] = '\0';

		SetWindowText(hEditDialog, data);
	}
	else
	{
		printf_s("This file %s didn't open", *path);
	}
}

void displayDialogBox(HWND hWnd) {
	HWND hWnd1 = CreateWindowW(L"Dialog1", L"Dialog 1", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 240, 500, 400, 
		hWnd, NULL, NULL, NULL);
	CreateWindowW(L"button", L"Open File", WS_VISIBLE | WS_CHILD, 20, 20, 100, 40, 
		hWnd1, (HMENU)FILE_SUB_MENU_OPEN_DIALOG, NULL, NULL);

	hEditDialog = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | BS_MULTILINE | WS_BORDER | ES_AUTOVSCROLL,
		1, 60, 400, 300, hWnd1, NULL, NULL, NULL);
}
