#pragma warning(disable:4996)
#pragma once
//-----------------------------------------------------------------------------
//�}�b�v�`�b�v�N���X
//-----------------------------------------------------------------------------
#include "GameEngine_Ver3_7.h"

enum BoxType
{
	non = -1,
	air = 0,
	box = 1,
	stairs = 2,
	start = 3,
	goal = 4
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
	//���b�V����
	string		meshName_;
public:
	//���S�������p�R���X�g���N�^
	Box()
		: pos_(0, 0, 0)
		, hitBase_(0, 0, 0, 0, 0, 0)
		, type_(non)
		, meshName_("")
	{}

	//�������
	~Box()
	{
		if (this->meshName_ != "")
		{
			DG::Mesh_Erase(this->meshName_);
		}
	}
	//�ǂݍ��ݗp
	void Initialize_Box(const ML::Vec3&, const ML::Box3D&, const int&);
	//���b�V�����w��
	void Set_MeshName(const string);
	//���W��n��
	ML::Vec3 Get_Pos();
	//�����蔻���n��
	ML::Box3D Get_HitBase();
	//��ނ�n��
	BoxType Get_Type();
	//�X�P�[�����O
	ML::Vec3 Get_Scaring();
	//�`�悷����̂����f
	bool Check_Rendering();
	//�����蔻��
	bool Box_HitCheck(const ML::Box3D& hitBase);
	//�`��
	void Render3D();
};