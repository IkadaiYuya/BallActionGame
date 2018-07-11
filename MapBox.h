#pragma warning(disable:4996)
#pragma once
//-----------------------------------------------------------------------------
//�}�b�v�`�b�v�N���X
//-----------------------------------------------------------------------------
#include "GameEngine_Ver3_7.h"

#define ChipX 100
#define ChipY 100
#define ChipZ 100

class Box
{
private:
	//���W
	ML::Vec3	pos_;
	//�`�b�v�T�C�Y
	ML::Vec3	chipSize_;
	//�����蔻��
	ML::Box3D	hitBase_;

public:
	//���S�������p�R���X�g���N�^
	Box()
		: pos_(0, 0, 0)
		, chipSize_(0, 0, 0)
		, hitBase_(0, 0, 0, 0, 0, 0)
	{}
	//�}�b�v�������p�R���X�g���N�^
	Box(ML::Vec3& pos, ML::Box3D& hitBase)
		: pos_(pos)
		, chipSize_(ChipX, ChipY, ChipZ)
		, hitBase_(hitBase)
	{}
	//�����̏������p�R���X�g���N�^
	Box(ML::Vec3& pos, ML::Vec3& chipSize, ML::Box3D& hitBase)
		: pos_(pos)
		, chipSize_(chipSize)
		, hitBase_(hitBase)
	{}
	//���W��n��
	ML::Vec3 Get_Pos();
	//�`�b�v�T�C�Y��n��
	ML::Vec3 Get_ChipSize();
	//�X�P�[�����O�̐��l��n��
	ML::Vec3 Get_Scaling();
	//�����蔻���n��
	ML::Box3D Get_HitBase();
	//�����蔻��
	bool Box_HitCheck(const ML::Box3D& hitBase);
};