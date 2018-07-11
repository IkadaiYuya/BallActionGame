#pragma warning(disable:4996)
#pragma once
//-----------------------------------------------------------------------------
//マップチップクラス
//-----------------------------------------------------------------------------
#include "GameEngine_Ver3_7.h"

#define ChipX 100
#define ChipY 100
#define ChipZ 100

class Box
{
private:
	//座標
	ML::Vec3	pos_;
	//チップサイズ
	ML::Vec3	chipSize_;
	//あたり判定
	ML::Box3D	hitBase_;

public:
	//完全初期化用コンストラクタ
	Box()
		: pos_(0, 0, 0)
		, chipSize_(0, 0, 0)
		, hitBase_(0, 0, 0, 0, 0, 0)
	{}
	//マップ初期化用コンストラクタ
	Box(ML::Vec3& pos, ML::Box3D& hitBase)
		: pos_(pos)
		, chipSize_(ChipX, ChipY, ChipZ)
		, hitBase_(hitBase)
	{}
	//床等の初期化用コンストラクタ
	Box(ML::Vec3& pos, ML::Vec3& chipSize, ML::Box3D& hitBase)
		: pos_(pos)
		, chipSize_(chipSize)
		, hitBase_(hitBase)
	{}
	//座標を渡す
	ML::Vec3 Get_Pos();
	//チップサイズを渡す
	ML::Vec3 Get_ChipSize();
	//スケーリングの数値を渡す
	ML::Vec3 Get_Scaling();
	//あたり判定を渡す
	ML::Box3D Get_HitBase();
	//あたり判定
	bool Box_HitCheck(const ML::Box3D& hitBase);
};