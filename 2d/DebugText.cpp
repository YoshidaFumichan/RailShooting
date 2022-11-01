#include "DebugText.h"
#include "SafeDelete.h"

#include <cassert>

DebugText* DebugText::GetInstance()
{
	static DebugText instance;

	return &instance;
}

void DebugText::Initialize()
{
	// SpriteCommon�̃C���X�^���X���擾
	spriteCommon = SpriteCommon::GetInstance();

	// �f�o�b�N�e�L�X�g�����[�h
	if (!spriteCommon->LoadTexture(0, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}

	// �S�ẴX�v���C�g�f�[�^�ɂ���
	for (int i = 0; i < _countof(spriteDatas); i++)
	{
		// �X�v���C�g�𐶐�����
		spriteDatas[i] = Sprite::Create(0);
	}
}

void DebugText::Finalize()
{
	for (auto s : spriteDatas) {
		safe_delete(s);
	}
}

void DebugText::Print(const std::string& text, XMFLOAT2 position, float scale)
{
	// �S�Ă̕����ɂ���
	for (int i = 0; i < text.size(); i++)
	{
		// �ő啶��������
		if (spriteIndex >= maxCharCount) {
			break;
		}

		// 1�������o��(��ASCII�R�[�h�ł������藧���Ȃ�)
		const unsigned char& character = text[i];

		// ASCII�R�[�h��2�i����΂����ԍ����v�Z
		int fontIndex = character - 32;
		if (character >= 0x7f) {
			fontIndex = 0;
		}

		int fontIndexY = fontIndex / fontLineCount;
		int fontIndexX = fontIndex % fontLineCount;

		// ���W�v�Z
		spriteDatas[spriteIndex]->SetPosition({ position.x + fontWidth * scale * i, position.y });
		spriteDatas[spriteIndex]->SetTexLeftTop({ (float)fontIndexX * fontWidth, (float)fontIndexY * fontHeight });
		spriteDatas[spriteIndex]->SetTexSize({ fontWidth, fontHeight });
		spriteDatas[spriteIndex]->SetSize({ fontWidth * scale, fontHeight * scale });
		// ���_�o�b�t�@�]��
		spriteDatas[spriteIndex]->TransferVertexBuffer();
		// �X�V
		spriteDatas[spriteIndex]->Update();

		// �������P�i�߂�
		spriteIndex++;
	}
}

// �܂Ƃ߂ĕ`��
void DebugText::DrawAll(ID3D12GraphicsCommandList* cmdList)
{
	// �S�Ă̕����̃X�v���C�g�ɂ���
	for (int i = 0; i < spriteIndex; i++)
	{
		// �X�v���C�g�`��
		spriteDatas[i]->Draw();
	}

	spriteIndex = 0;
}