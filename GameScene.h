#pragma once


#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"


#include "DebugCamera.h"


/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

private: // �ÓI�����o�ϐ�
	static const int debugTextTexNumber = 0;

public: // �����o�֐�

	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �p�[�e�B�N������
	/// </summary>
	void CreateParticles();
	int bf = 0;
	int bt = 0;
private: // �����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;



	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>
	/// DebugText debugText;	
	DebugCamera* camera = nullptr;
	Sprite* spriteBG = nullptr;
	Sprite* sprite2 = nullptr;


	Model* modelSkydome = nullptr;
	Model* modelGround = nullptr;
	Model* modelFighter = nullptr;
	Model* modelSphere = nullptr;
	Model* modelBullet = nullptr;

	Object3d* objSkydome = nullptr;
	Object3d* objGround = nullptr;
	Object3d* objFighter = nullptr;
	Object3d* objSphere = nullptr;
	Object3d* objBullet = nullptr;

	float ambientColor0[3] = { 1,1,1 };
	// �������������l
	float lightDir0[3] = { 0,0,1 };
	float lightColor0[3] = { 1,0,0 };

	float lightDir1[3] = { 0,1,0 };
	float lightColor1[3] = { 0,1,0 };

	float lightDir2[3] = { 1,0,0 };
	float lightColor2[3] = { 0,0,1 };
};

