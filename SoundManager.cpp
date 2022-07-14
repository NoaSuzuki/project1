#include "SoundManager.h"
#include <fstream>
#include <cassert>

#pragma comment(lib,"xaudio2.lib")

SoundManager::~SoundManager()
{
	//�ǂݍ��ݍς݃T�E���h�̔g�`�f�[�^�����
	for (auto& pair : soundDatas) {
		delete pair.second.pBuffer;
	}
}

void SoundManager::Initialize()
{
	HRESULT result;

	//�C���X�^���X�𐶐�
	result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	assert(SUCCEEDED(result));
	// �}�X�^�[�{�C�X�𐶐�
	result = xAudio2->CreateMasteringVoice(&masterVoice);
	assert(SUCCEEDED(result));

}

void SoundManager::LoadWave(int number,const char* filename)
{
	SoundData soundData{};

	HRESULT result;
	// �t�@�C���X�g���[��
	std::ifstream file;
	// Wave�t�@�C�����J��
	file.open(filename, std::ios_base::binary);
	// �t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail()) {
		assert(0);
	}
	// RIFF�w�b�_�[�̓ǂݍ���
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	// �t�@�C����RIFF���`�F�b�N
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}
	// Format�`�����N�̓ǂݍ���
	FormatChunk format;
	file.read((char*)&format, sizeof(format));
	// Data�`�����N�̓ǂݍ���
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));
	// Data�`�����N�̃f�[�^���i�g�`�f�[�^�j�̓ǂݍ���
	soundData.pBuffer = new char[data.size];
	file.read(soundData.pBuffer, data.size);
	//�g�`�f�[�^�̃T�C�Y���L�^
	soundData.datasize = data.size;
	// Wave�t�@�C�������
	file.close();
	// �g�`�t�H�[�}�b�g�̐ݒ�
	memcpy(&soundData.wfex, &format.fmt, sizeof(format.fmt));
	soundData.wfex.wBitsPerSample = format.fmt.nBlockAlign * 8 / format.fmt.nChannels;

	//�A�z�z��ɗv�f��ǉ�
	soundDatas.insert(std::make_pair(number, soundData));
}

void SoundManager::PlayWave(int number)
{
	SoundData& soundData = soundDatas[number];
	HRESULT result;

	// �g�`�t�H�[�}�b�g������SourceVoice�̐���
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	result = xAudio2->CreateSourceVoice(&pSourceVoice, &soundData.wfex, 0, 2.0f, nullptr);
	assert(SUCCEEDED(result));
	// �Đ�����g�`�f�[�^�̐ݒ�
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = (BYTE*)soundData.pBuffer;
	buf.pContext = soundData.pBuffer;
	buf.Flags = XAUDIO2_END_OF_STREAM;
	buf.AudioBytes = soundData.datasize;

	// �g�`�f�[�^�̍Đ�
	result = pSourceVoice->SubmitSourceBuffer(&buf);
	//XAUDIO2_VOICE_STATE xaudio2state;
	//pSourceVoice->GetState(&xaudio2state);
	result = pSourceVoice->Start();

}
