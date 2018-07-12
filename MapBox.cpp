//-----------------------------------------------------------------------------
//マップチップクラス
//-----------------------------------------------------------------------------
#include "MapBox.h"
#include "MyPG.h"

//読み込み用
void Box::Initialize_Box(const ML::Vec3& pos, const ML::Box3D& hitBase, const int& type)
{
	this->pos_ = pos;
	this->hitBase_ = hitBase;
	this->type_ = (BoxType)type;
}
//座標を渡す
ML::Vec3 Box::Get_Pos()
{
	return this->pos_;
}
//あたり判定を渡す
ML::Box3D Box::Get_HitBase()
{
	return this->hitBase_;
}
//
BoxType Box::Get_Type()
{
	return this->type_;
}
//あたり判定
bool Box::Box_HitCheck(const ML::Box3D& hitBase)
{
	return this->hitBase_.OffsetCopy(this->pos_).Hit(hitBase);
}