#pragma warning(disable:4996)
#pragma once
//-----------------------------------------------------------------------------
//マップチップクラス
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
	//座標
	ML::Vec3	pos_;
	//あたり判定
	ML::Box3D	hitBase_;
	//タイプ
	BoxType		type_;
public:
	//完全初期化用コンストラクタ
	Box()
		: pos_(0, 0, 0)
		, hitBase_(0, 0, 0, 0, 0, 0)
		, type_(non)
	{}
	//読み込み用
	void Initialize_Box(const ML::Vec3&, const ML::Box3D&, const int&);
	//座標を渡す
	ML::Vec3 Get_Pos();
	//あたり判定を渡す
	ML::Box3D Get_HitBase();
	//種類を渡す
	BoxType Get_Type();
	//あたり判定
	bool Box_HitCheck(const ML::Box3D& hitBase);
};