#pragma warning(disable:4996)
#pragma once
//-----------------------------------------------------------------------------
//�}�b�v�`�b�v�N���X
//-----------------------------------------------------------------------------
#include "GameEngine_Ver3_7.h"

#define ChipX 100
#define ChipY 100
#define ChipZ 100

enum BoxType
{
	non = -1,
	air = 0,
	floor = 1,
	wall = 2,
	ceiling = 3,
	stairs = 4,
	start = 5,
	goal = 6
};

class Box
{
private:
	//���W
	ML::Vec3	pos_;
	//�����蔻��
	ML::Box3D	hitBase_;
	//�^�C�v
	BoxType		type_;
public:
	//���S�������p�R���X�g���N�^
	Box()
		: pos_(0, 0, 0)
		, hitBase_(0, 0, 0, 0, 0, 0)
		, type_(non)
	{}
	//�ǂݍ��ݗp
	void Initialize_Box(const ML::Vec3&, const ML::Box3D&, const int&);
	//���W��n��
	ML::Vec3 Get_Pos();
	//�����蔻���n��
	ML::Box3D Get_HitBase();
	//��ނ�n��
	BoxType Get_Type();
	//�����蔻��
	bool Box_HitCheck(const ML::Box3D& hitBase);
};