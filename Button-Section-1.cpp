#include<windows.h>
#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 0
#define FILE_SUB_MENU_NEW 3
#define FILE_SUB_MENU_NEW_TITLE 4

LRESULT CALLBACK WindowsProcedure(HWND, UINT, WPARAM, LPARAM);

HMENU hMenu;
HWND hEdit;
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
	CreateWindowW(L"MyWindows", L"Windows Application", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 900, 900, 
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
				case FILE_SUB_MENU_NEW_TITLE:
					wchar_t text[100];

					// GetWindowTextW(Component, text, max_count_word)
					GetWindowTextW(hEdit, text, 100);
					SetWindowTextW(hWnd, text);
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
	AppendMenu(hFileSubMenu, MF_STRING, FILE_SUB_MENU_NEW_TITLE, "New Title");
	
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_OPEN, "Open");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

	// AppendMenu(hMenu, Flag_Show_Type , message_queue_menu , text);
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hFileMenu, "File");
	AppendMenu(hMenu, MF_STRING, NULL, "Help");
	
	SetMenu(hWnd, hMenu);

}

void addControls(HWND hWnd) {

	CreateWindowW(L"static", L"Enter Your Name: ", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER , 200, 100, 200, 40,
		hWnd, NULL, NULL, NULL);
	hEdit = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 200, 155, 200, 50,
		hWnd, NULL, NULL, NULL);

	CreateWindowW(L"button", L"Change Title", WS_VISIBLE | WS_CHILD, 200, 205, 100, 50, hWnd, (HMENU)FILE_SUB_MENU_NEW_TITLE, NULL, NULL);

}
