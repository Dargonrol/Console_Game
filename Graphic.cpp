#include "Graphic.h"

LRESULT CALLBACK Window::WindowProc(HWND p_hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*
	Window* pWindow;
	StateInfo* pState;

	if (uMsg == WM_CREATE)
	{
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		pWindow = reinterpret_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(p_hWnd, GWLP_USERDATA, (LONG_PTR)pWindow);
		pState = pWindow->pState;
	}
	else
	{
		LONG_PTR ptr = GetWindowLongPtr(p_hWnd, GWLP_USERDATA);
		Window* pWindow = reinterpret_cast<Window*>(ptr);
		pState = pWindow->pState;
	}
	*/
	
	switch (uMsg) {
	case WM_CLOSE:
		DestroyWindow(p_hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(p_hWnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 6));

		EndPaint(p_hWnd, &ps);
		break;
	}

	return DefWindowProc(p_hWnd, uMsg, wParam, lParam);
}

Window::Window(COORD size, LPCWSTR title)
	: hInstance(GetModuleHandle(nullptr))
{
	LPCWSTR CLASS_NAME = L"DR_WINDOW_CLASS";

	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIconW(NULL, IDI_ASTERISK);
	wndClass.hCursor = LoadCursorW(NULL, IDC_CROSS);
	wndClass.lpfnWndProc = WindowProc;
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	
	if (!RegisterClass(&wndClass))
		cout << "FATAL ERROR: Could not register window class\n";

	DWORD style = WS_OVERLAPPED | WS_SYSMENU;

	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + size.X;
	rect.bottom = rect.top + size.Y;

	AdjustWindowRect(&rect, style, false);

	if (pState == NULL)
	{
		cout << "FATAL ERROR: Could not create a püointer to StateInfo Struct!\n";
	}

	pState->mainBuffer.resize(rect.bottom - rect.top); // Größe der äußeren Vektor (y-Elemente) festlegen
	for (int i = 0; i < rect.bottom - rect.top; ++i) {
		pState->mainBuffer[i].resize(rect.right - rect.left); // Größe der inneren Vektoren (x-Elemente) festlegen
		for (int j = 0; j < rect.right - rect.left; ++j) {
			pState->mainBuffer[i][j].color = RGB(255, 0, 0); // Standardfarbe setzen
		}
	}

	hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		title,
		style,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		this
	);
}

Window::~Window()
{
	const wchar_t* CLASS_NAME = L"DR_WINDOW_CLASS";
	UnregisterClass(CLASS_NAME, hInstance);
}

bool Window::ProcessMessages()
{
	MSG msg = { };
	MSG* pmsg = &msg;
	ZeroMemory(pmsg, sizeof(msg));
	while (PeekMessage(pmsg, nullptr, 0u, 0u, PM_REMOVE)) {
		if (msg.message == WM_QUIT)
			return false;

		TranslateMessage(&msg);
		DispatchMessage(pmsg);
	}

	return true;
}

Window Window::returnObj()
{
	return *this;
}

bool Window::showWindow(int argument)
{
	return ShowWindow(hWnd, argument);
}

bool Window::addTextBox(LPCWSTR content, COORD pos, COORD size)
{
	RECT rect;
	GetWindowRect(hWnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	if (pos.X > width || pos.Y > height) {
		cout << "ERROR: TextBoxCreation Failed because coordiantes are out of bounds.\nLast Error: " << GetLastError() << "\n";
		return false;
	}
	CreateWindowW(
		L"static",
		L"test",
		WS_VISIBLE | WS_CHILD | 0,
		pos.X,
		pos.Y,
		size.X,
		size.Y,
		hWnd,
		NULL,
		NULL,
		NULL
	);
}