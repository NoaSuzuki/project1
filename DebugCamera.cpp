#include "DebugCamera.h"
#include <cassert>

using namespace DirectX;

DebugCamera::DebugCamera(int window_width, int window_height, Input* input)
	: Camera(window_width, window_height)
{
	assert(input);

	this->input = input;




}

void DebugCamera::Update()
{
	// ��ʃT�C�Y�ɑ΂��鑊�ΓI�ȃX�P�[���ɒ���
	scaleX = sensitivity / (float)1920;
	scaleY = sensitivity / (float)1080;
	bool dirty = false;
	float angleX = 0;
	float angleY = 0;

	// �}�E�X�̓��͂��擾
	Input::MouseMove mouseMove = input->GetMouseMove();

	// �}�E�X�̍��{�^����������Ă�����J��������]������
	if (input->PushMouseMiddle())
	{

		float dy = mouseMove.lX * scaleY;
		float dx = mouseMove.lY * scaleX;
		angleX = -dx * XM_PI;
		angleY = -dy * XM_PI;
		dirty = true;

	}
	if (input->TriggerKey(DIK_A)) {
		sensitivity -= 0.1f;
	}
	if (input->TriggerKey(DIK_D)) {
		sensitivity += 0.1f;
	}
	if (sensitivity <= 0) {
		sensitivity = 0.1f;
	}
	//// �}�E�X�̒��{�^����������Ă�����J��������s�ړ�������
	//if (input->PushMouseMiddle())
	//{
	//	float dx = mouseMove.lX / 100.0f;
	//	float dy = mouseMove.lY / 100.0f;

	//	XMVECTOR move = {-dx, +dy, 0, 0};
	//	move = XMVector3Transform(move, matRot);

	//	MoveVector(move);
	//	dirty = true;
	//}

	//// �z�C�[�����͂ŋ�����ύX
	//if (mouseMove.lZ != 0) {
	//	distance -= mouseMove.lZ / 100.0f;
	//	distance = max(distance, 1.0f);
	//	dirty = true;
	//}

	if (dirty || viewDirty) {
		// �ǉ���]���̉�]�s��𐶐�
		XMMATRIX matRotNew = XMMatrixIdentity();
		matRotNew *= XMMatrixRotationX(-angleX);
		matRotNew *= XMMatrixRotationY(-angleY);
		// �ݐς̉�]�s�������
		// ����]�s���ݐς��Ă����ƁA�덷�ŃX�P�[�����O��������댯�������
		// �N�H�[�^�j�I�����g�p��������]�܂���
		matRot = matRotNew * matRot;

		// �����_���王�_�ւ̃x�N�g���ƁA������x�N�g��
		XMVECTOR vTargetEye = { 0.0f, 0.0f, -distance, 1.0f };
		XMVECTOR vUp = { 0.0f, 1.0f, 0.0f, 0.0f };

		// �x�N�g������]
		vTargetEye = XMVector3Transform(vTargetEye, matRot);
		vUp = XMVector3Transform(vUp, matRot);

		// �����_���炸�炵���ʒu�Ɏ��_���W������
		const XMFLOAT3& target = GetTarget();
		SetEye({ target.x + vTargetEye.m128_f32[0], target.y + vTargetEye.m128_f32[1], target.z + vTargetEye.m128_f32[2] });
		SetUp({ vUp.m128_f32[0], vUp.m128_f32[1], vUp.m128_f32[2] });
	}

	Camera::Update();
}
