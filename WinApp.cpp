#include "WinApp.h"
#include "windows.h"

const wchar_t WinApp::windowClassName[] = L"DirectXGame";


LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void WinApp::Initialize()
{
	// �Q�[���E�B���h�E�̍쐬
	//win = new WinApp();
	//win->CreateGameWindow();
	//WNDCLASSEX w{};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;
	w.lpszClassName = L"Engine";
	w.hInstance = GetModuleHandle(nullptr);
	w.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&w);

	RECT wrc = { 0,0,window_width,window_height };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	hwnd = CreateWindow(w.lpszClassName,
		L"Engine",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		w.hInstance,
		nullptr
	);

	ShowWindow(hwnd, SW_SHOW);


}

void WinApp::Update()
{

}

void WinApp::Finalize()
{
	UnregisterClass(w.lpszClassName, w.hInstance);
}

bool WinApp::ProcessMessage()
{
	MSG msg{};
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_QUIT)
	{
		return true;
	}
	return false;
}

void WinApp::CreateGameWindow()
{
	// �E�B���h�E�N���X�̐ݒ�
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc = (WNDPROC)WindowProc; // �E�B���h�E�v���V�[�W��
	wndClass.lpszClassName = windowClassName; // �E�B���h�E�N���X��
	wndClass.hInstance = GetModuleHandle(nullptr); // �E�B���h�E�n���h��
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // �J�[�\���w��

	RegisterClassEx(&wndClass); // �E�B���h�E�N���X��OS�ɓo�^

	// �E�B���h�E�T�C�Y{ X���W Y���W ���� �c�� }
	RECT wrc = { 0, 0, window_width, window_height };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false); // �����ŃT�C�Y�␳

	// �E�B���h�E�I�u�W�F�N�g�̐���
	hwnd = CreateWindow(wndClass.lpszClassName, // �N���X��
		windowClassName,			// �^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,	// �^�C�g���o�[�Ƌ��E��������E�B���h�E
		CW_USEDEFAULT,			// �\��X���W�iOS�ɔC����j
		CW_USEDEFAULT,			// �\��Y���W�iOS�ɔC����j
		wrc.right - wrc.left,	// �E�B���h�E����
		wrc.bottom - wrc.top,	// �E�B���h�E�c��
		nullptr,				// �e�E�B���h�E�n���h��
		nullptr,				// ���j���[�n���h��
		wndClass.hInstance,			// �Ăяo���A�v���P�[�V�����n���h��
		nullptr);				// �I�v�V����

	// �E�B���h�E�\��
	ShowWindow(hwnd, SW_SHOW);
}