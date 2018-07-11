//-----------------------------------------------------------------------------
//�}�b�v�`�b�v�N���X
//-----------------------------------------------------------------------------
#include "MapBox.h"
#include "MyPG.h"

//���W��n��
ML::Vec3 Box::Get_Pos()
{
	return this->pos_;
}
//�`�b�v�T�C�Y��n��
ML::Vec3 Box::Get_ChipSize()
{
	return this->chipSize_;
}
//�X�P�[�����O�̐��l��n��
ML::Vec3 Box::Get_Scaling()
{
	return this->chipSize_;
}
//�����蔻���n��
ML::Box3D Box::Get_HitBase()
{
	return this->hitBase_;
}
//�����蔻��
bool Box::Box_HitCheck(const ML::Box3D& hitBase)
{
	return this->hitBase_.OffsetCopy(this->pos_).Hit(hitBase);
}