#include <windows.h>	// �����쿡���� ���� ����� �̰� �ϳ�
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"HelloAPI";
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
	RegisterClass(&WndClass);
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
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}