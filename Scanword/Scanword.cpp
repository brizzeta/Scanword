#define WM_ICON WM_APP
#define ID_TRAYICON WM_USER
#include "Scanword.h"
#include <string>
using namespace std;

Scanword* Scanword::ptr = NULL;

Scanword::Scanword(void)
{
	pNID = new NOTIFYICONDATA;
	ptr = this;
}

Scanword::~Scanword(void)
{
	delete pNID;
}

void Scanword::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL Scanword::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	HINSTANCE hInst = GetModuleHandle(NULL);
	hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	SetClassLong(hDialog, GCL_HICON, LONG(hIcon));
	memset(pNID, 0, sizeof(NOTIFYICONDATA));
	pNID->cbSize = sizeof(NOTIFYICONDATA);
	pNID->hIcon = hIcon;
	pNID->hWnd = hwnd;
	lstrcpy(pNID->szTip, TEXT("��������"));
	pNID->uCallbackMessage = WM_ICON;
	pNID->uFlags = NIF_TIP | NIF_ICON | NIF_MESSAGE | NIF_INFO;
	lstrcpy(pNID->szInfo, TEXT("����������� ������"));
	lstrcpy(pNID->szInfoTitle, TEXT("��������!"));
	pNID->uID = ID_TRAYICON;

	//������ ������ ���� ������ ���������
	TCHAR GUID[] = TEXT("{B98A2629 - FDE6 - 4B87 - 8484 - DBCB7A2B8034}");
	hMutex = CreateMutex(NULL, FALSE, GUID);
	DWORD dwAnswer = WaitForSingleObject(hMutex, 0);
	if (dwAnswer == WAIT_TIMEOUT)
	{
		MessageBox(hwnd, TEXT("���������� ��� �������!"), TEXT("�������"), MB_OK | MB_ICONINFORMATION);
		EndDialog(hwnd, 0);
	}

	//��������� ����������� Edit � Button
	for (int i = 0; i < 56; i++)
	{
		hEdit[i] = GetDlgItem(hwnd, IDC_EDIT1 + i);
		if(i < 16)
		{
			hBut[i] = GetDlgItem(hwnd, IDC_BUTTON1 + i);
		}
	}

	//������������� ������ ������ � edit
	LOGFONT logfont;
	ZeroMemory(&logfont, sizeof(LOGFONT));
	logfont.lfCharSet = DEFAULT_CHARSET;
	logfont.lfHeight = -50;
	HFONT hFont = CreateFontIndirect(&logfont);
	for (int i = 0; i < 56; i++)
	{
		SendMessage(hEdit[i], WM_SETFONT, (WPARAM)hFont, TRUE);
		SendMessage(hEdit[i], EM_SETLIMITTEXT, (WPARAM)1, 1);  //����� �� ���� ���� � ���� edit
	}
	return TRUE;
}

//������������� ���� ������ disabled
void Scanword::DisableEdits()
{
	for (int i = 0; i < 56; i++)
	{
		EnableWindow(hEdit[i], FALSE);
	}
}

void Scanword::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_CHECK)
	{
		//������������� �����
		HFONT hFont = CreateFont(-43, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Palatino Linotype"));

		//������
		TCHAR answ[][10] = {
			TEXT("�������"),
			TEXT("�����"),
			TEXT("����"),
			TEXT("�������"),
			TEXT("��������"),
			TEXT("��������"),
			TEXT("�����"),
			TEXT("�����"),
			TEXT("����"),
			TEXT("����"),
			TEXT("����"),
			TEXT("���"),
			TEXT("�������"),
			TEXT("������"),
			TEXT("���������"),
			TEXT("������")
		};
		TCHAR text[10][2];  //���� ����� �������� ����� �� edit'��
		TCHAR answ2[10];    //���� ����������� ����� � ���� ������ ��� ��������� � ������ �������

		//��������� 1 ������

		GetWindowText(hEdit[5], text[0], 2);   //�������� ���������� edit'��
		GetWindowText(hEdit[12], text[1], 2);
		GetWindowText(hEdit[19], text[2], 2);
		GetWindowText(hEdit[25], text[3], 2);
		GetWindowText(hEdit[33], text[4], 2);
		GetWindowText(hEdit[40], text[5], 2);
		GetWindowText(hEdit[49], text[6], 2);		

		for(int i = 0; i < 7; i++)   //����������� ����� � ���� ������
		{
			answ2[i] = text[i][0];
		}

		answ2[7] = '\0';

		if (!lstrcmpi(answ[0], answ2))  //���� ����� ������
		{
			SendMessage(hEdit[5], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));  //�������� �����
			SendMessage(hEdit[12], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[19], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[25], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[33], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[40], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[49], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			EnableWindow(hBut[0], FALSE);    //��������� ������ �������			
			edits[0] = 1;                    //���������� ���������� ������
		}

		//��������� 2 ������

		GetWindowText(hEdit[0], text[0], 2);   //�������� ���������� edit'��
		GetWindowText(hEdit[7], text[1], 2);
		GetWindowText(hEdit[13], text[2], 2);
		GetWindowText(hEdit[21], text[3], 2);
		GetWindowText(hEdit[26], text[4], 2);

		for (int i = 0; i < 5; i++)   //����������� ����� � ���� ������
		{
			answ2[i] = text[i][0];
		}

		answ2[5] = '\0';

		if (!lstrcmpi(answ[1], answ2))  //���� ����� ������
		{
			SendMessage(hEdit[0], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));  //�������� �����
			SendMessage(hEdit[7], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[13], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[21], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[26], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			EnableWindow(hBut[1], FALSE);    //��������� ������ �������			
			edits[1] = 1;                    //���������� ���������� ������
		}

		//��������� 3 ������

		GetWindowText(hEdit[1], text[0], 2);   //�������� ���������� edit'��
		GetWindowText(hEdit[2], text[1], 2);
		GetWindowText(hEdit[3], text[2], 2);
		GetWindowText(hEdit[4], text[3], 2);

		for (int i = 0; i < 4; i++)   //����������� ����� � ���� ������
		{
			answ2[i] = text[i][0];
		}

		answ2[4] = '\0';

		if (!lstrcmpi(answ[2], answ2))  //���� ����� ������
		{
			SendMessage(hEdit[1], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));  //�������� �����
			SendMessage(hEdit[2], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[3], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[4], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			EnableWindow(hBut[2], FALSE);    //��������� ������ �������			
			edits[2] = 1;                    //���������� ���������� ������
		}

		//��������� 4 ������

		GetWindowText(hEdit[11], text[0], 2);   //�������� ���������� edit'��
		GetWindowText(hEdit[18], text[1], 2);
		GetWindowText(hEdit[24], text[2], 2);
		GetWindowText(hEdit[32], text[3], 2);
		GetWindowText(hEdit[39], text[4], 2);
		GetWindowText(hEdit[48], text[5], 2);
		GetWindowText(hEdit[55], text[6], 2);

		for (int i = 0; i < 7; i++)   //����������� ����� � ���� ������
		{
			answ2[i] = text[i][0];
		}

		answ2[7] = '\0';

		if (!lstrcmpi(answ[3], answ2))  //���� ����� ������
		{
			SendMessage(hEdit[11], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));  //�������� �����
			SendMessage(hEdit[18], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[24], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[32], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[39], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[48], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[55], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			EnableWindow(hBut[3], FALSE);    //��������� ������ �������			
			edits[3] = 1;                    //���������� ���������� ������
		}

		//��������� 5 ������

		GetWindowText(hEdit[1], text[0], 2);   //�������� ���������� edit'��
		GetWindowText(hEdit[9], text[1], 2);
		GetWindowText(hEdit[14], text[2], 2);
		GetWindowText(hEdit[22], text[3], 2);
		GetWindowText(hEdit[28], text[4], 2);
		GetWindowText(hEdit[35], text[5], 2);
		GetWindowText(hEdit[44], text[6], 2);
		GetWindowText(hEdit[51], text[7], 2);

		for (int i = 0; i < 8; i++)   //����������� ����� � ���� ������
		{
			answ2[i] = text[i][0];
		}

		answ2[8] = '\0';

		if (!lstrcmpi(answ[4], answ2))  //���� ����� ������
		{
			SendMessage(hEdit[1], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));  //�������� �����
			SendMessage(hEdit[9], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[14], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[22], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[28], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[35], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[44], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[51], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			EnableWindow(hBut[4], FALSE);    //��������� ������ �������
			edits[4] = 1;                    //���������� ���������� ������
		}

		//��������� 6 ������

		GetWindowText(hEdit[3], text[0], 2);   //�������� ���������� edit'��
		GetWindowText(hEdit[10], text[1], 2);
		GetWindowText(hEdit[16], text[2], 2);
		GetWindowText(hEdit[23], text[3], 2);
		GetWindowText(hEdit[30], text[4], 2);
		GetWindowText(hEdit[37], text[5], 2);
		GetWindowText(hEdit[46], text[6], 2);
		GetWindowText(hEdit[53], text[7], 2);

		for (int i = 0; i < 8; i++)   //����������� ����� � ���� ������
		{
			answ2[i] = text[i][0];
		}

		answ2[8] = '\0';

		if (!lstrcmpi(answ[5], answ2))  //���� ����� ������
		{
			SendMessage(hEdit[3], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));  //�������� �����
			SendMessage(hEdit[10], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[16], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[23], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[30], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[37], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[46], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[53], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			EnableWindow(hBut[5], FALSE);    //��������� ������ �������
			edits[5] = 1;                    //���������� ���������� ������
		}

		//��������� 7 ������

		GetWindowText(hEdit[5], text[0], 2);   //�������� ���������� edit'��
		GetWindowText(hEdit[6], text[1], 2);
		GetWindowText(hEdit[7], text[2], 2);
		GetWindowText(hEdit[8], text[3], 2);
		GetWindowText(hEdit[9], text[4], 2);

		for (int i = 0; i < 5; i++)   //����������� ����� � ���� ������
		{
			answ2[i] = text[i][0];
		}

		answ2[5] = '\0';

		if (!lstrcmpi(answ[6], answ2))  //���� ����� ������
		{
			SendMessage(hEdit[5], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));  //�������� �����
			SendMessage(hEdit[6], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[7], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[8], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[9], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			EnableWindow(hBut[6], FALSE);    //��������� ������ �������
			edits[6] = 1;                    //���������� ���������� ������
		}

		//��������� 8 ������

		GetWindowText(hEdit[14], text[0], 2);   //�������� ���������� edit'��
		GetWindowText(hEdit[15], text[1], 2);
		GetWindowText(hEdit[16], text[2], 2);
		GetWindowText(hEdit[17], text[3], 2);
		GetWindowText(hEdit[18], text[4], 2);

		for (int i = 0; i < 5; i++)   //����������� ����� � ���� ������
		{
			answ2[i] = text[i][0];
		}

		answ2[5] = '\0';

		if (!lstrcmpi(answ[7], answ2))  //���� ����� ������
		{
			SendMessage(hEdit[14], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));  //�������� �����
			SendMessage(hEdit[15], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[16], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[17], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[18], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			EnableWindow(hBut[7], FALSE);    //��������� ������ �������
			edits[7] = 1;                    //���������� ���������� ������
		}

		//��������� 9 ������

		GetWindowText(hEdit[27], text[0], 2);   //�������� ���������� edit'��
		GetWindowText(hEdit[34], text[1], 2);
		GetWindowText(hEdit[43], text[2], 2);
		GetWindowText(hEdit[50], text[3], 2);

		for (int i = 0; i < 4; i++)   //����������� ����� � ���� ������
		{
			answ2[i] = text[i][0];
		}

		answ2[4] = '\0';

		if (!lstrcmpi(answ[8], answ2))  //���� ����� ������
		{
			SendMessage(hEdit[27], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));  //�������� �����
			SendMessage(hEdit[34], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[43], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[50], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			EnableWindow(hBut[8], FALSE);    //��������� ������ �������
			edits[8] = 1;                    //���������� ���������� ������
		}

		//��������� 10 ������

		GetWindowText(hEdit[29], text[0], 2);   //�������� ���������� edit'��
		GetWindowText(hEdit[36], text[1], 2);
		GetWindowText(hEdit[45], text[2], 2);
		GetWindowText(hEdit[52], text[3], 2);

		for (int i = 0; i < 4; i++)   //����������� ����� � ���� ������
		{
			answ2[i] = text[i][0];
		}

		answ2[4] = '\0';

		if (!lstrcmpi(answ[9], answ2))  //���� ����� ������
		{
			SendMessage(hEdit[29], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));  //�������� �����
			SendMessage(hEdit[36], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[45], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[52], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			EnableWindow(hBut[9], FALSE);    //��������� ������ �������
			edits[9] = 1;                    //���������� ���������� ������
		}

		//��������� 11 ������

		GetWindowText(hEdit[31], text[0], 2);   //�������� ���������� edit'��
		GetWindowText(hEdit[38], text[1], 2);
		GetWindowText(hEdit[47], text[2], 2);
		GetWindowText(hEdit[54], text[3], 2);

		for (int i = 0; i < 4; i++)   //����������� ����� � ���� ������
		{
			answ2[i] = text[i][0];
		}

		answ2[4] = '\0';

		if (!lstrcmpi(answ[10], answ2))  //���� ����� ������
		{
			SendMessage(hEdit[31], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));  //�������� �����
			SendMessage(hEdit[38], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[47], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[54], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			EnableWindow(hBut[10], FALSE);    //��������� ������ �������
			edits[10] = 1;                    //���������� ���������� ������
		}

		//��������� 12 ������

		GetWindowText(hEdit[19], text[0], 2);   //�������� ���������� edit'��
		GetWindowText(hEdit[20], text[1], 2);
		GetWindowText(hEdit[21], text[2], 2);

		for (int i = 0; i < 3; i++)   //����������� ����� � ���� ������
		{
			answ2[i] = text[i][0];
		}

		answ2[3] = '\0';

		if (!lstrcmpi(answ[11], answ2))  //���� ����� ������
		{
			SendMessage(hEdit[19], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));  //�������� �����
			SendMessage(hEdit[20], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[21], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			EnableWindow(hBut[11], FALSE);    //��������� ������ �������
			edits[11] = 1;                    //���������� ���������� ������
		}

		//��������� 13 ������

		GetWindowText(hEdit[26], text[0], 2);   //�������� ���������� edit'��
		GetWindowText(hEdit[27], text[1], 2);
		GetWindowText(hEdit[28], text[2], 2);
		GetWindowText(hEdit[29], text[3], 2);
		GetWindowText(hEdit[30], text[4], 2);
		GetWindowText(hEdit[31], text[5], 2);
		GetWindowText(hEdit[32], text[6], 2);

		for (int i = 0; i < 7; i++)   //����������� ����� � ���� ������
		{
			answ2[i] = text[i][0];
		}

		answ2[7] = '\0';

		if (!lstrcmpi(answ[12], answ2))  //���� ����� ������
		{
			SendMessage(hEdit[26], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));  //�������� �����
			SendMessage(hEdit[27], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[28], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[29], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[30], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[31], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[32], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			EnableWindow(hBut[12], FALSE);    //��������� ������ �������
			edits[12] = 1;                    //���������� ���������� ������
		}

		//��������� 14 ������

		GetWindowText(hEdit[34], text[0], 2);   //�������� ���������� edit'��
		GetWindowText(hEdit[35], text[1], 2);
		GetWindowText(hEdit[36], text[2], 2);
		GetWindowText(hEdit[37], text[3], 2);
		GetWindowText(hEdit[38], text[4], 2);
		GetWindowText(hEdit[39], text[5], 2);

		for (int i = 0; i < 6; i++)   //����������� ����� � ���� ������
		{
			answ2[i] = text[i][0];
		}

		answ2[6] = '\0';

		if (!lstrcmpi(answ[13], answ2))  //���� ����� ������
		{
			SendMessage(hEdit[34], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));  //�������� �����
			SendMessage(hEdit[35], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[36], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[37], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[38], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[39], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			EnableWindow(hBut[13], FALSE);    //��������� ������ �������
			edits[13] = 1;                    //���������� ���������� ������
		}

		//��������� 15 ������

		GetWindowText(hEdit[40], text[0], 2);   //�������� ���������� edit'��
		GetWindowText(hEdit[41], text[1], 2);
		GetWindowText(hEdit[42], text[2], 2);
		GetWindowText(hEdit[43], text[3], 2);
		GetWindowText(hEdit[44], text[4], 2);
		GetWindowText(hEdit[45], text[5], 2);
		GetWindowText(hEdit[46], text[6], 2);
		GetWindowText(hEdit[47], text[7], 2);
		GetWindowText(hEdit[48], text[8], 2);

		for (int i = 0; i < 9; i++)   //����������� ����� � ���� ������
		{
			answ2[i] = text[i][0];
		}

		answ2[9] = '\0';

		if (!lstrcmpi(answ[14], answ2))  //���� ����� ������
		{
			SendMessage(hEdit[40], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));  //�������� �����
			SendMessage(hEdit[41], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[42], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[43], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[44], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[45], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[46], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[47], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[48], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			EnableWindow(hBut[14], FALSE);    //��������� ������ �������
			edits[14] = 1;                    //���������� ���������� ������
		}

		//��������� 16 ������

		GetWindowText(hEdit[50], text[0], 2);   //�������� ���������� edit'��
		GetWindowText(hEdit[51], text[1], 2);
		GetWindowText(hEdit[52], text[2], 2);
		GetWindowText(hEdit[53], text[3], 2);
		GetWindowText(hEdit[54], text[4], 2);
		GetWindowText(hEdit[55], text[5], 2);

		for (int i = 0; i < 6; i++)   //����������� ����� � ���� ������
		{
			answ2[i] = text[i][0];
		}

		answ2[6] = '\0';

		if (!lstrcmpi(answ[15], answ2))  //���� ����� ������
		{
			SendMessage(hEdit[50], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));  //�������� �����
			SendMessage(hEdit[51], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[52], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[53], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[54], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendMessage(hEdit[55], WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			EnableWindow(hBut[15], FALSE);    //��������� ������ �������
			edits[15] = 1;                    //���������� ���������� ������
		}
	}
	else if (id == IDC_BUTTON1)
	{
		DisableEdits();                      //��� edit's ���������� disable
		//������������� enable ������ edit'��
		if(edits[6] == 0)                    //���� 7 ������ �� �������
		{
			EnableWindow(hEdit[5], TRUE);    
		}
		if (edits[11] == 0)                   //���� 12 ������ �� �������
		{
			EnableWindow(hEdit[19], TRUE);
		}
		if (edits[14] == 0)                  //���� 15 ������ �� �������
		{
			EnableWindow(hEdit[40], TRUE);
		}
		EnableWindow(hEdit[12], TRUE);		
		EnableWindow(hEdit[25], TRUE);
		EnableWindow(hEdit[33], TRUE);		
		EnableWindow(hEdit[49], TRUE);		
	}
	else if (id == IDC_BUTTON2)
	{
		DisableEdits();
		if (edits[6] == 0)
		{
			EnableWindow(hEdit[7], TRUE);
		}
		if (edits[11] == 0)
		{
			EnableWindow(hEdit[21], TRUE);
		}
		if (edits[12] == 0)
		{
			EnableWindow(hEdit[26], TRUE);
		}		
		EnableWindow(hEdit[0], TRUE);		
		EnableWindow(hEdit[13], TRUE);		
	}
	else if (id == IDC_BUTTON3)
	{
		DisableEdits();
		if (edits[4] == 0)
		{
			EnableWindow(hEdit[1], TRUE);
		}		
		if (edits[5] == 0)
		{
			EnableWindow(hEdit[3], TRUE);
		}
		EnableWindow(hEdit[2], TRUE);
		EnableWindow(hEdit[4], TRUE);
	}
	else if (id == IDC_BUTTON4)
	{
		DisableEdits();
		EnableWindow(hEdit[11], TRUE);
		if (edits[7] == 0)
		{
			EnableWindow(hEdit[18], TRUE);
		}		
		if (edits[12] == 0)
		{
			EnableWindow(hEdit[32], TRUE);
		}
		if (edits[13] == 0)
		{
			EnableWindow(hEdit[39], TRUE);
		}
		if (edits[14] == 0)
		{
			EnableWindow(hEdit[48], TRUE);
		}
		if (edits[15] == 0)
		{
			EnableWindow(hEdit[55], TRUE);
		}
		EnableWindow(hEdit[24], TRUE);
	}
	else if (id == IDC_BUTTON5)
	{
		DisableEdits();
		if (edits[2] == 0)
		{
			EnableWindow(hEdit[1], TRUE);
		}
		if (edits[6] == 0)
		{
			EnableWindow(hEdit[9], TRUE);
		}
		if (edits[7] == 0)
		{
			EnableWindow(hEdit[14], TRUE);
		}		
		if (edits[12] == 0)
		{
			EnableWindow(hEdit[28], TRUE);
		}
		if (edits[13] == 0)
		{
			EnableWindow(hEdit[35], TRUE);
		}
		if (edits[14] == 0)
		{
			EnableWindow(hEdit[44], TRUE);
		}
		if (edits[15] == 0)
		{
			EnableWindow(hEdit[51], TRUE);
		}
		EnableWindow(hEdit[22], TRUE);
	}
	else if (id == IDC_BUTTON6)
	{
		DisableEdits();
		if (edits[2] == 0)
		{
			EnableWindow(hEdit[3], TRUE);
		}		
		if (edits[7] == 0)
		{
			EnableWindow(hEdit[16], TRUE);
		}		
		if (edits[12] == 0)
		{
			EnableWindow(hEdit[30], TRUE);
		}
		if (edits[13] == 0)
		{
			EnableWindow(hEdit[37], TRUE);
		}
		if (edits[14] == 0)
		{
			EnableWindow(hEdit[46], TRUE);
		}
		if (edits[15] == 0)
		{
			EnableWindow(hEdit[53], TRUE);
		}
		EnableWindow(hEdit[10], TRUE);
		EnableWindow(hEdit[23], TRUE);
	}
	else if (id == IDC_BUTTON7)
	{
		DisableEdits();
		if (edits[0] == 0)
		{
			EnableWindow(hEdit[5], TRUE);
		}		
		if (edits[1] == 0)
		{
			EnableWindow(hEdit[7], TRUE);
		}		
		if (edits[4] == 0)
		{
			EnableWindow(hEdit[9], TRUE);
		}
		EnableWindow(hEdit[6], TRUE);
		EnableWindow(hEdit[8], TRUE);
	}
	else if (id == IDC_BUTTON8)
	{
		DisableEdits();
		if (edits[4] == 0)
		{
			EnableWindow(hEdit[14], TRUE);
		}		
		if (edits[5] == 0)
		{
			EnableWindow(hEdit[16], TRUE);
		}		
		if (edits[3] == 0)
		{
			EnableWindow(hEdit[18], TRUE);
		}
		EnableWindow(hEdit[15], TRUE);
		EnableWindow(hEdit[17], TRUE);
	}
	else if (id == IDC_BUTTON9)
	{
		DisableEdits();
		if (edits[12] == 0)
		{
			EnableWindow(hEdit[27], TRUE);
		}
		if (edits[13] == 0)
		{
			EnableWindow(hEdit[34], TRUE);
		}
		if (edits[14] == 0)
		{
			EnableWindow(hEdit[43], TRUE);
		}
		if (edits[15] == 0)
		{
			EnableWindow(hEdit[50], TRUE);
		}
	}
	else if (id == IDC_BUTTON10)
	{
		DisableEdits();
		if (edits[12] == 0)
		{
			EnableWindow(hEdit[29], TRUE);
		}
		if (edits[13] == 0)
		{
			EnableWindow(hEdit[36], TRUE);
		}
		if (edits[14] == 0)
		{
			EnableWindow(hEdit[45], TRUE);
		}
		if (edits[15] == 0)
		{
			EnableWindow(hEdit[52], TRUE);
		}
	}
	else if (id == IDC_BUTTON11)
	{
		DisableEdits();
		if (edits[12] == 0)
		{
			EnableWindow(hEdit[31], TRUE);
		}
		if (edits[13] == 0)
		{
			EnableWindow(hEdit[38], TRUE);
		}
		if (edits[14] == 0)
		{
			EnableWindow(hEdit[47], TRUE);
		}
		if (edits[15] == 0)
		{
			EnableWindow(hEdit[54], TRUE);
		}
	}
	else if (id == IDC_BUTTON12)
	{
		DisableEdits();
		if (edits[0] == 0)
		{
			EnableWindow(hEdit[19], TRUE);
		}		
		if (edits[1] == 0)
		{
			EnableWindow(hEdit[21], TRUE);
		}
		EnableWindow(hEdit[20], TRUE);
	}
	else if (id == IDC_BUTTON13)
	{
		DisableEdits();
		if (edits[1] == 0)
		{
			EnableWindow(hEdit[26], TRUE);
		}
		if (edits[8] == 0)
		{
			EnableWindow(hEdit[27], TRUE);
		}
		if (edits[4] == 0)
		{
			EnableWindow(hEdit[28], TRUE);
		}
		if (edits[9] == 0)
		{
			EnableWindow(hEdit[29], TRUE);
		}
		if (edits[5] == 0)
		{
			EnableWindow(hEdit[30], TRUE);
		}
		if (edits[10] == 0)
		{
			EnableWindow(hEdit[31], TRUE);
		}
		if (edits[3] == 0)
		{
			EnableWindow(hEdit[32], TRUE);
		}
	}
	else if (id == IDC_BUTTON14)
	{
		DisableEdits();
		if (edits[8] == 0)
		{
			EnableWindow(hEdit[34], TRUE);
		}
		if (edits[4] == 0)
		{
			EnableWindow(hEdit[35], TRUE);
		}
		if (edits[9] == 0)
		{
			EnableWindow(hEdit[36], TRUE);
		}
		if (edits[5] == 0)
		{
			EnableWindow(hEdit[37], TRUE);
		}
		if (edits[10] == 0)
		{
			EnableWindow(hEdit[38], TRUE);
		}
		if (edits[3] == 0)
		{
			EnableWindow(hEdit[39], TRUE);
		}
	}
	else if (id == IDC_BUTTON15)
	{
		DisableEdits();
		if (edits[0] == 0)
		{
			EnableWindow(hEdit[40], TRUE);
		}		
		if (edits[8] == 0)
		{
			EnableWindow(hEdit[43], TRUE);
		}
		if (edits[4] == 0)
		{
			EnableWindow(hEdit[44], TRUE);
		}
		if (edits[9] == 0)
		{
			EnableWindow(hEdit[45], TRUE);
		}
		if (edits[5] == 0)
		{
			EnableWindow(hEdit[46], TRUE);
		}
		if (edits[10] == 0)
		{
			EnableWindow(hEdit[47], TRUE);
		}
		if (edits[3] == 0)
		{
			EnableWindow(hEdit[48], TRUE);
		}
		EnableWindow(hEdit[41], TRUE);
		EnableWindow(hEdit[42], TRUE);
	}
	else if (id == IDC_BUTTON16)
	{
		DisableEdits();
		if (edits[8] == 0)
		{
			EnableWindow(hEdit[50], TRUE);
		}
		if (edits[4] == 0)
		{
			EnableWindow(hEdit[51], TRUE);
		}
		if (edits[9] == 0)
		{
			EnableWindow(hEdit[52], TRUE);
		}
		if (edits[5] == 0)
		{
			EnableWindow(hEdit[53], TRUE);
		}
		if (edits[10] == 0)
		{
			EnableWindow(hEdit[54], TRUE);
		}
		if (edits[3] == 0)
		{
			EnableWindow(hEdit[55], TRUE);
		}
	}
}

void Scanword::Cls_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	if (state == SIZE_MINIMIZED)
	{
		ShowWindow(hwnd, SW_HIDE); // ������ ����
		Shell_NotifyIcon(NIM_ADD, pNID); // ��������� ������ � ����
	}
}

// ���������� ����������������� ���������
void Scanword::OnTrayIcon(WPARAM wp, LPARAM lp)
{
	if (lp == WM_LBUTTONDBLCLK)
	{
		Shell_NotifyIcon(NIM_DELETE, pNID); // ������� ������ �� ����
		ShowWindow(hDialog, SW_NORMAL); // ��������������� ����
		SetForegroundWindow(hDialog); // ������������� ���� �� �������� ����
	}
}

BOOL CALLBACK Scanword::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_SIZE, ptr->Cls_OnSize);
	}
	// ���������������� ���������
	if (message == WM_ICON)
	{
		ptr->OnTrayIcon(wParam, lParam);
		return TRUE;
	}
	return FALSE;
}
