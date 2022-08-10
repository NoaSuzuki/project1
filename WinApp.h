#pragma once
#include <windows.h>

//�E�B���h�E�Y�A�v���P�[�V����
class WinApp
{
	//�萔
public:
	static const int window_width = 1280;
	static const int window_height = 720;
	static const wchar_t windowClassName[];
	// �ėp�@�\
	//WinApp* win = nullptr;
	//�|�C���^�u����


public:
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:
	//������
	void Initialize();
	//�X�V
	void Update();
	void CreateGameWindow();
	//�I��
	void Finalize();

	//���b�Z�[�W�̏���
	bool ProcessMessage();
	HWND GetHwnd() { return hwnd; }
	HINSTANCE GetHInstance() { return w.hInstance; }
	HINSTANCE GetInstance() { return wndClass.hInstance; }
private:
	HWND hwnd = nullptr;
	WNDCLASSEX w{};
	
private: // �����o�ϐ�
	// Window�֘A
	HWND hwnd = nullptr;	// �E�B���h�E�n���h��
	WNDCLASSEX wndClass{};			// �E�B���h�E�N���X
};
