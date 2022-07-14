#pragma once
#include <Windows.h>
#include <xaudio2.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include<map>

class SoundManager
{
public:
	//namespace�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	template<class T1, class T2> using map = std::map<T1, T2>;

public:
	
	//�`�����N�w�b�_
	struct ChunkHeader
	{
		char id[4];//�`�����N����ID
		int size;//�`�����N�T�C�Y
	};

	//RIFF�w�b�_�`�����N
	struct RiffHeader
	{
		ChunkHeader chunk;//RIFF
		char type[4];//WAVE
	};

	//FMT�`�����N
	struct FormatChunk
	{
		ChunkHeader chunk;//fmt
		WAVEFORMAT fmt;//�g�`�t�H�[�}�b�g
	};

	struct SoundData
	{
		WAVEFORMATEX wfex{};//�g�`�t�H�[�}�b�g
		char* pBuffer;//�g�`�f�[�^
		unsigned int datasize;//�g�`�f�[�^�̃T�C�Y
	};

public:
	//�f�X�N�g���N�^
	~SoundManager();
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �T�E���h�ǂݍ���
	/// </summary>
	/// <param name="filename"></param>
	void LoadWave(int number ,const char* filename);
	
	//�T�E���h�̍Đ�
	void PlayWave(int number);
private:
	//xAudio2�̃C���X�^���X
	ComPtr<IXAudio2> xAudio2;
	//�}�X�^�[�{�C�X
	IXAudio2MasteringVoice* masterVoice;
	//�g�`�f�[�^�̘A�z�z��
	map<int, SoundData>soundDatas;
};

