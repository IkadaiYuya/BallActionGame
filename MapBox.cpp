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
//�����蔻��
bool Box::Box_HitCheck(const ML::Box3D& hitBase)
{
	return this->hitBase_.OffsetCopy(this->pos_).Hit(hitBase);
}