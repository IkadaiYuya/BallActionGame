//-----------------------------------------------------------------------------
//�}�b�v�`�b�v�N���X
//-----------------------------------------------------------------------------
#include "MapBox.h"
#include "MyPG.h"

//�ǂݍ��ݗp
void Box::Initialize_Box(const ML::Vec3& pos, const ML::Box3D& hitBase, const int& type)
{
	this->pos_ = pos;
	this->hitBase_ = hitBase;
	this->type_ = (BoxType)type;
}

//
void Box::Set_MeshName(const string meshName)
{
	this->meshName_ = meshName;
}

//���W��n��
ML::Vec3 Box::Get_Pos()
{
	return this->pos_;
}

//�����蔻���n��
ML::Box3D Box::Get_HitBase()
{
	return this->hitBase_;
}

//
BoxType Box::Get_Type()
{
	return this->type_;
}

//
ML::Vec3 Box::Get_Scaring()
{
	return ML::Vec3(ChipX, ChipY, ChipZ);
}

//
bool Box::Check_Rendering()
{
	return this->meshName_ != "";
}

//�����蔻��
bool Box::Box_HitCheck(const ML::Box3D& hitBase)
{
	return this->hitBase_.OffsetCopy(this->pos_).Hit(hitBase);
}

//
void Box::Render3D()
{
	if (this->type_ == box)
	{
		ML::Mat4x4 matT, matS;
		matT.Translation(this->pos_);
		matS.Scaling(this->Get_Scaring());
		DG::EffectState().param.matWorld = matS * matT;
		DG::Mesh_Draw(this->meshName_);
	}
}