#include <windows.h>	// 윈도우에서는 보통 헤더가 이거 하나
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"HelloAPI";
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) // 윈도우에서는 main대신 WinMain
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	// 윈도우의 바탕색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //프로그램에서 사용하는 커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //프로그램에서 사용하는 아이콘
	WndClass.hInstance = hInstance; //프로그램의 객체 핸들
	WndClass.lpfnWndProc = (WNDPROC)WndProc; //윈도우 프로시저 지정
	WndClass.lpszClassName = lpszClass; //클래스 이름
	WndClass.lpszMenuName = NULL; //메뉴
	WndClass.style = CS_HREDRAW | CS_VREDRAW; //클래스의 스타일
	RegisterClass(&WndClass);
	hWnd = CreateWindow(lpszClass, //윈도우 클래스 이름
		L"윈도우 프로그래밍", //윈도우 타이틀
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, //윈도우 스타일
		200, 200, //윈도우가 보일 때 X, Y 좌표
		600, 600, //윈도우의 폭과 높이
		(HWND)NULL, //부모 윈도우 핸들
		(HMENU)NULL, //윈도우가 갖는 메뉴 핸들
		hInstance, //객체 핸들
		NULL); //여분의 데이터
	ShowWindow(hWnd, nCmdShow);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"메인 윈도우 생성";
	switch (iMessage)
	{
	case WM_PAINT: //WM_PAINT 윈도우에 뭔가를 그리려 할때 발생되는 메시지
	{
		PAINTSTRUCT ps;
		//PAINTSTRUCTURE: 윈도우 클라이언트 영역에 무엇인가를 그리려고 할때 필요한 정보(핸들, 배경을 지울 것인지 여부, 클라이언트 영역 좌표 등)를 담고 있는 구조체이다.

		HDC hdc = BeginPaint(hWnd, &ps);
		//PAINTSTRUCT 구조체에 그리는 데 필요한 정보를 채우고 윈도우에 그릴 준비를 한 후 리턴값으로 DC 핸들을 반환

		TextOut(hdc, 100, 100, text, lstrlen(text));   //DC로 텍스트를 출력, DOS의 printf와 같은 성격
		EndPaint(hWnd, &ps); // EndPaint( ) 함수는 DC 핸들을 해제
		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}