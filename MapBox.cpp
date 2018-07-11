//-----------------------------------------------------------------------------
//マップチップクラス
//-----------------------------------------------------------------------------
#include "MapBox.h"
#include "MyPG.h"

//座標を渡す
ML::Vec3 Box::Get_Pos()
{
	return this->pos_;
}
//チップサイズを渡す
ML::Vec3 Box::Get_ChipSize()
{
	return this->chipSize_;
}
//スケーリングの数値を渡す
ML::Vec3 Box::Get_Scaling()
{
	return this->chipSize_;
}
//あたり判定を渡す
ML::Box3D Box::Get_HitBase()
{
	return this->hitBase_;
}
//あたり判定
bool Box::Box_HitCheck(const ML::Box3D& hitBase)
{
	return this->hitBase_.OffsetCopy(this->pos_).Hit(hitBase);
}