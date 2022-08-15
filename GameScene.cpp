#include "GameScene.h"
#include <cassert>
#include <sstream>
#include <iomanip>


using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{

}
 
void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);



	// �e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(1, L"Resources/background.png")) {
		assert(0);
		return;
	}
	// �w�i�X�v���C�g����
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	sprite2 = Sprite::Create(2, { 0.0f,0.0f });



	// �e�N�X�`��2�Ԃɓǂݍ���
	Sprite::LoadTexture(2, L"Resources/tex1.png");


	objFighter->SetPosition({ +10, 0, 0 });
	objSphere->SetPosition({ -1, 1, 0 });
	objSphere->SetScale({ 0.1,0.1,0.1 });
	// �J���������_���Z�b�g
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(3.0f);

	modelFighter = Model::CreateFromOBJ("enemy_kinoko", true);
	modelBullet = Model::CreateFromOBJ("enemybullet", true);
	objFighter = Object3d::Create(modelFighter);
	objBullet = Object3d::Create(modelSphere);
}

void GameScene::Update()
{
	// �p�[�e�B�N������
	//CreateParticles();

	lightGroup->Update();
	camera->Update();
	particleMan->Update();

	// �I�u�W�F�N�g�̉�]
	{
		XMFLOAT3 rot = objSphere->GetRotation();
		rot.z += 1.0f;
		objSphere->SetRotation(rot);
	}

	//{ // imgui����̃��C�g�p�����[�^�𔽉f		
	//	lightGroup->SetAmbientColor(XMFLOAT3(ambientColor0));
	//	lightGroup->SetDirLightDir(0, XMVECTOR({ lightDir0[0], lightDir0[1], lightDir0[2], 0 }));
	//	lightGroup->SetDirLightColor(0, XMFLOAT3(lightColor0));
	//	lightGroup->SetDirLightDir(1, XMVECTOR({ lightDir1[0], lightDir1[1], lightDir1[2], 0 }));
	//	lightGroup->SetDirLightColor(1, XMFLOAT3(lightColor1));
	//	lightGroup->SetDirLightDir(2, XMVECTOR({ lightDir2[0], lightDir2[1], lightDir2[2], 0 }));
	//	lightGroup->SetDirLightColor(2, XMFLOAT3(lightColor2));
	//}
	debugText->Print("A: SENSITIVITY DOWN", 50, 50, 1.5f);
	debugText->Print("D: SENSITIVITY UP", 50, 75, 1.5f);
	objSkydome->Update();
	objGround->Update();
	objFighter->Update();
	objSphere->Update();

	if (input->PushMouseLeft()) {
		bf = 1;
	}
	if (bf == 1) {
		bt++;
	}
	if (bt > 100) {
		bf = 0;
		bt = 0;
	}

}

void GameScene::Draw()
{
	//ImGui::Begin("Light");
	//ImGui::SetWindowPos(ImVec2(0, 0));
	//ImGui::SetWindowSize(ImVec2(500, 200));
	//ImGui::ColorEdit3("ambientColor", ambientColor0, ImGuiColorEditFlags_Float);
	//ImGui::InputFloat3("lightDir0", lightDir0);
	//ImGui::ColorEdit3("lightColor0", lightColor0, ImGuiColorEditFlags_Float);
	//ImGui::InputFloat3("lightDir1", lightDir1);
	//ImGui::ColorEdit3("lightColor1", lightColor1, ImGuiColorEditFlags_Float);
	//ImGui::InputFloat3("lightDir2", lightDir2);
	//ImGui::ColorEdit3("lightColor2", lightColor2, ImGuiColorEditFlags_Float);
	//ImGui::End();



#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����

	// �w�i�X�v���C�g�`��
	//spriteBG->Draw();

	/// <summary>
	/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>

	// �X�v���C�g�`��㏈��

	// �[�x�o�b�t�@�N���A
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3D�`��
	// 3D�I�u�W�F�N�g�̕`��

	objSkydome->Draw();
	//objGround->Draw();
	objFighter->Draw();
	if (bf == 1) {
		objSphere->Draw();
	}
	Object3d::PostDraw();



#pragma endregion

#pragma region �O�i�X�v���C�g�`��

	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>
		//�X�v���C�g�`��
	/*sprite2->Draw();*/



#pragma endregion
}

void GameScene::CreateParticles()
{
	for (int i = 0; i < 10; i++) {
		// X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
		const float rnd_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		XMFLOAT3 acc{};
		const float rnd_acc = 0.001f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		// �ǉ�
		particleMan->Add(60, pos, vel, acc, 1.0f, 0.0f);
	}
}
