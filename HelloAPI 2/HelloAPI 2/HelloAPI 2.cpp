#include <windows.h>	// 윈도우에서는 보통 헤더가 이거 하나

#define ID_OK_BTN	2000

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // 여긴 위와 달리 왜 변수명을 다 적었지?
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"HelloAPI";
LPCTSTR ChildClassName = L"ChildWin";

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
	RegisterClass(&WndClass);					// 메인 윈도우 클래스 등록

	WndClass.lpfnWndProc = ChildWndProc;
	WndClass.lpszClassName = ChildClassName;
	RegisterClass(&WndClass);				// 차일드는 클래스만 만들고 Create는 여기서 안 함.

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
	case WM_CREATE:
	{ //차일드 윈도우가 만들어진 후 윈도우 핸들값이 저장된다.
		HWND hChildWnd = CreateWindow(
			ChildClassName, //차일드 윈도우 클래스 이름
			L"차일드 윈도우", //윈도우 타이틀
			WS_OVERLAPPEDWINDOW | WS_CHILD, //윈도우 스타일
			150, //윈도우가 보일 때 x 좌표
			150, //윈도우가 보일 때 y 좌표
			260, //윈도우 폭
			200, //윈도우 높이
			hWnd, //부모 윈도우
			(HMENU)1000, //차일드 윈도우 ID
			g_hInst, //객체 핸들
			(LPVOID)NULL); //여분의 데이터

		ShowWindow(hChildWnd, SW_SHOW); // 차일드 윈도우를 화면에 보여 준다.

		hChildWnd = CreateWindow(
			L"button", //버튼의 윈도우 클래스 이름
			L"지역대학", //윈도우 타이틀
			WS_CHILD | WS_VISIBLE, //윈도우 스타일
			20, //윈도우가 보일 때 x 좌표
			400, //윈도우가 보일 때 y 좌표
			100, //윈도우 폭
			30, //윈도우 높이
			hWnd, //부모 윈도우
			(HMENU)ID_OK_BTN, //컨트롤 ID
			g_hInst, //객체 핸들
			(LPVOID)NULL); //여분의 데이터
		if (!hChildWnd) return -1; //버튼이 만들어지지 않으면 종료한다.
		return 0;
	}
	case WM_COMMAND:
	{
		//WM_COMMAND 메시지를 발생시킨 컨트롤의 ID를 검사한다.
		if (LOWORD(wParam) == ID_OK_BTN)
		{ //메시지 박스를 띄운다.
			MessageBox(hWnd, L"[지역대학] 버튼이 클릭되었다", L"지역대학", MB_OK);
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
	LPCTSTR text = L"차일드 윈도우 생성";
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps; //페인트 정보 구조체
		HDC hdc = BeginPaint(hWnd, &ps); //DC 핸들 얻어 오기
		TextOut(hdc, 10, 10, text, lstrlen(text)); //문자열 출력 함수
		EndPaint(hWnd, &ps); //핸들 해제		 
		return 0;
	}
	}
	// 모든 메시지는 디폴트 프로시저에서 처리하도록 한다.
	return DefWindowProc(hWnd, message, wParam, lParam);
}

