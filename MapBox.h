#pragma warning(disable:4996)
#pragma once
//-----------------------------------------------------------------------------
//マップチップクラス
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
	//座標
	ML::Vec3	pos_;
	//あたり判定
	ML::Box3D	hitBase_;
	//タイプ
	BoxType		type_;
	//メッシュ名
	string		meshName_;
public:
	//完全初期化用コンストラクタ
	Box()
		: pos_(0, 0, 0)
		, hitBase_(0, 0, 0, 0, 0, 0)
		, type_(non)
		, meshName_("")
	{}

	//解放処理
	~Box()
	{
		if (this->meshName_ != "")
		{
			DG::Mesh_Erase(this->meshName_);
		}
	}
	//読み込み用
	void Initialize_Box(const ML::Vec3&, const ML::Box3D&, const int&);
	//メッシュ名指定
	void Set_MeshName(const string);
	//座標を渡す
	ML::Vec3 Get_Pos();
	//あたり判定を渡す
	ML::Box3D Get_HitBase();
	//種類を渡す
	BoxType Get_Type();
	//スケーリング
	ML::Vec3 Get_Scaring();
	//描画するものか判断
	bool Check_Rendering();
	//あたり判定
	bool Box_HitCheck(const ML::Box3D& hitBase);
	//描画
	void Render3D();
};