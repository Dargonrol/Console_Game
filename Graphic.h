#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>

using namespace std;

class Window {
	static LRESULT CALLBACK WindowProc(HWND p_hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	Window(COORD size, LPCWSTR title);
	//Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	~Window();

	bool ProcessMessages();

	Window returnObj();

	bool showWindow(int argument);

	bool addTextBox(LPCWSTR content, COORD pos, COORD size); //https://www.youtube.com/watch?v=9JMQkUOhW1s&list=PLWzp0Bbyy_3i750dsUj7yq4JrPOIUR_NK&index=3

	void setPixel(COORD pos, COLORREF color);

private:
	HINSTANCE hInstance;
	HWND hWnd;

	typedef struct {
		COLORREF color;
	} pixel;

	typedef vector<vector<pixel>> pixelBuffer;

	struct StateInfo {
		pixelBuffer mainBuffer;
		int state;
	};

	StateInfo* pState = new (nothrow) StateInfo;
};