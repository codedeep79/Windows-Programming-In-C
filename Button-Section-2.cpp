#include<windows.h>
#include<stdlib.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 0
#define FILE_SUB_MENU_NEW 3
#define GENERATE_BUTTON 4

LRESULT CALLBACK WindowsProcedure(HWND, UINT, WPARAM, LPARAM);

HMENU hMenu;
HWND hEdit, hName, hAge, hOut;
void addMenus(HWND);
void addControls(HWND);


int WINAPI WinMain(HINSTANCE HInstance, HINSTANCE HPrevInstance, PSTR szCmdLine, int iCmdShow){

	// WNDCLASSW: Windows Class Object
	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = HInstance;
	wc.lpszClassName = L"MyWindows";
	wc.lpfnWndProc = WindowsProcedure;

	if (!RegisterClassW(&wc))
		return -1;
	
	// WS: Windows Style
	CreateWindowW(L"MyWindows", L"Windows Application", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 600, 500, 
		NULL, NULL, NULL, NULL);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

// HWND: Handle Windows
// UINT msg: Các tin nhắn dưới dạng constant
LRESULT CALLBACK WindowsProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg)
	{
		// WM: Windows Message
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
					// MB: Message Beep
					MessageBeep(MB_OK);
					break;
				case FILE_MENU_OPEN:
					MessageBeep(MB_ICONINFORMATION);
					break;
				case FILE_MENU_EXIT:
					DestroyWindow(hWnd);
					break;		
				case GENERATE_BUTTON:
					char name[30], age[10], out[50];
					GetWindowText(hName, name, 30);
					GetWindowText(hAge, age, 10);

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
	//AppendMenu(hFileSubMenu, MF_STRING, FILE_SUB_MENU_NEW_TITLE, "New Title");
	
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_OPEN, "Open");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

	// AppendMenu(hMenu, Flag_Show_Type , message_queue_menu , text);
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

	CreateWindowW(L"button", L"Generate", WS_VISIBLE | WS_CHILD | WS_BORDER, 250, 130, 90, 40,
		hWnd, (HMENU) GENERATE_BUTTON, NULL, NULL);

	hOut = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 190, 300, 200,
		hWnd, NULL, NULL, NULL);

}
