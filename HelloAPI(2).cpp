#include <windows.h>	// �����쿡���� ���� ����� �̰� �ϳ�

#define ID_OK_BTN	2000

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // ���� ���� �޸� �� �������� �� ������?
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"HelloAPI";
LPCTSTR ChildClassName = L"ChildWin";

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) // �����쿡���� main��� WinMain
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	// �������� ������
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //���α׷����� ����ϴ� Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //���α׷����� ����ϴ� ������
	WndClass.hInstance = hInstance; //���α׷��� ��ü �ڵ�
	WndClass.lpfnWndProc = (WNDPROC)WndProc; //������ ���ν��� ����
	WndClass.lpszClassName = lpszClass; //Ŭ���� �̸�
	WndClass.lpszMenuName = NULL; //�޴�
	WndClass.style = CS_HREDRAW | CS_VREDRAW; //Ŭ������ ��Ÿ��
	RegisterClass(&WndClass);					// ���� ������ Ŭ���� ���

	WndClass.lpfnWndProc = ChildWndProc;
	WndClass.lpszClassName = ChildClassName;
	RegisterClass(&WndClass);				// ���ϵ�� Ŭ������ ����� Create�� ���⼭ �� ��.

	hWnd = CreateWindow(lpszClass, //������ Ŭ���� �̸�
		L"������ ���α׷���", //������ Ÿ��Ʋ
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, //������ ��Ÿ��
		200, 200, //�����찡 ���� �� X, Y ��ǥ
		600, 600, //�������� ���� ����
		(HWND)NULL, //�θ� ������ �ڵ�
		(HMENU)NULL, //�����찡 ���� �޴� �ڵ�
		hInstance, //��ü �ڵ�
		NULL); //������ ������
	ShowWindow(hWnd, nCmdShow);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"���� ������ ����";
	switch (iMessage)
	{
	case WM_PAINT: //WM_PAINT �����쿡 ������ �׸��� �Ҷ� �߻��Ǵ� �޽���
	{
		PAINTSTRUCT ps;
		//PAINTSTRUCTURE: ������ Ŭ���̾�Ʈ ������ �����ΰ��� �׸����� �Ҷ� �ʿ��� ����(�ڵ�, ����� ���� ������ ����, Ŭ���̾�Ʈ ���� ��ǥ ��)�� ��� �ִ� ����ü�̴�.

		HDC hdc = BeginPaint(hWnd, &ps);
		//PAINTSTRUCT ����ü�� �׸��� �� �ʿ��� ������ ä��� �����쿡 �׸� �غ� �� �� ���ϰ����� DC �ڵ��� ��ȯ

		TextOut(hdc, 100, 100, text, lstrlen(text));   //DC�� �ؽ�Ʈ�� ���, DOS�� printf�� ���� ����
		EndPaint(hWnd, &ps); // EndPaint( ) �Լ��� DC �ڵ��� ����
		return 0;
	}
	case WM_CREATE:
	{ //���ϵ� �����찡 ������� �� ������ �ڵ鰪�� ����ȴ�.
		HWND hChildWnd = CreateWindow(
			ChildClassName, //���ϵ� ������ Ŭ���� �̸�
			L"���ϵ� ������", //������ Ÿ��Ʋ
			WS_OVERLAPPEDWINDOW | WS_CHILD, //������ ��Ÿ��
			150, //�����찡 ���� �� x ��ǥ
			150, //�����찡 ���� �� y ��ǥ
			260, //������ ��
			200, //������ ����
			hWnd, //�θ� ������
			(HMENU) 1000, //���ϵ� ������ ID
			g_hInst, //��ü �ڵ�
			(LPVOID) NULL); //������ ������

		ShowWindow(hChildWnd, SW_SHOW); // ���ϵ� �����츦 ȭ�鿡 ���� �ش�.

		hChildWnd = CreateWindow(
			L"button", //��ư�� ������ Ŭ���� �̸�
			L"��������", //������ Ÿ��Ʋ
			WS_CHILD | WS_VISIBLE, //������ ��Ÿ��
			20, //�����찡 ���� �� x ��ǥ
			400, //�����찡 ���� �� y ��ǥ
			100, //������ ��
			30, //������ ����
			hWnd, //�θ� ������
			(HMENU) ID_OK_BTN, //��Ʈ�� ID
			g_hInst, //��ü �ڵ�
			(LPVOID) NULL); //������ ������
		if (!hChildWnd) return -1; //��ư�� ��������� ������ �����Ѵ�.
		return 0;
	}
	case WM_COMMAND:
	{
		//WM_COMMAND �޽����� �߻���Ų ��Ʈ���� ID�� �˻��Ѵ�.
		if (LOWORD(wParam) == ID_OK_BTN)
		{ //�޽��� �ڽ��� ����.
			MessageBox(hWnd, L"[��������] ��ư�� Ŭ���Ǿ���", L"��������", MB_OK);
		}
		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"���ϵ� ������ ����";
	switch (message)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps; //����Ʈ ���� ����ü
			HDC hdc = BeginPaint(hWnd, &ps); //DC �ڵ� ��� ����
			TextOut(hdc, 10, 10, text, lstrlen(text)); //���ڿ� ��� �Լ�
			EndPaint(hWnd, &ps); //�ڵ� ����		 
			return 0;
		}
	}
	// ��� �޽����� ����Ʈ ���ν������� ó���ϵ��� �Ѵ�.
	return DefWindowProc(hWnd, message, wParam, lParam);
}

