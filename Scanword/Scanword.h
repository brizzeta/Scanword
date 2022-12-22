#pragma once
#include "Header.h"

class Scanword
{
public:
	Scanword(void);
	~Scanword(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static Scanword* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy);
	void OnTrayIcon(WPARAM wp, LPARAM lp);
	void DisableEdits();
	HWND hDialog, hEdit[56], hBut[16];
	HICON hIcon;
	PNOTIFYICONDATA pNID;
	HANDLE hMutex;
	UINT enter_but = 0;
	BOOL edits[16] = {0};
};