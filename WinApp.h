#pragma once
#include <windows.h>

//ウィンドウズアプリケーション
class WinApp
{
	//定数
public:
	static const int window_width = 1280;
	static const int window_height = 720;
	static const wchar_t windowClassName[];
	// 汎用機能
	//WinApp* win = nullptr;
	//ポインタ置き場


public:
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:
	//初期化
	void Initialize();
	//更新
	void Update();
	void CreateGameWindow();
	//終了
	void Finalize();

	//メッセージの処理
	bool ProcessMessage();
	HWND GetHwnd() { return hwnd; }
	HINSTANCE GetHInstance() { return w.hInstance; }
	HINSTANCE GetInstance() { return wndClass.hInstance; }
private:
	HWND hwnd = nullptr;
	WNDCLASSEX w{};
	
private: // メンバ変数
	// Window関連
	HWND hwnd = nullptr;	// ウィンドウハンドル
	WNDCLASSEX wndClass{};			// ウィンドウクラス
};
