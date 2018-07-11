//-------------------------------------------------------------------
//タイトル画面
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Title.h"
#include  "Task_Game.h"

namespace Title
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//リソースの初期化
	bool  Resource::Initialize()
	{
		this->meshName = "PlayerMesh";
		DG::Mesh_CreateFromSOBFile(this->meshName, "./data/mesh/Player.SOB");
		this->imageName = "TitleLogoImg";
		DG::Image_Create(this->imageName, "./data/image/TitleLogo.png");
		
		DG::Font_Create("fon", "MS 明朝", 8, 16);
		return true;
	}
	//-------------------------------------------------------------------
	//リソースの解放
	bool  Resource::Finalize()
	{
		DG::Mesh_Erase(this->meshName);
		DG::Image_Erase(this->imageName);
		DG::Font_Erase("fon");
		return true;
	}
	//-------------------------------------------------------------------
	//「初期化」タスク生成時に１回だけ行う処理
	bool  Object::Initialize()
	{
		//スーパークラス初期化
		__super::Initialize(defGroupName, defName, true);
		//リソースクラス生成orリソース共有
		this->res = Resource::Create();

		//★データ初期化
		this->pos = ML::Vec3(0, 0, 0);
		this->playerAngle = ML::ToRadian(-45.0f);
		this->timeCnt = 0;

		//カメラの生成
		ge->camera[0] = MyPG::Camera::Create(
			ML::Vec3(0.0f, 0.0f, 0.0f),						//	ターゲット位置
			ML::Vec3(0.0f, 0.0f, -300.0f),						//	カメラ位置
			ML::Vec3(0.0f, 1.0f, 0.0f),								//	カメラの上方向ベクトル
			ML::ToRadian(35), 10.0f, 4000.0f,						//	視野角・視野距離
			(float)ge->screenWidth / (float)ge->screenHeight);		//	画面比率		
		DG::EffectState().param.bgColor = ML::Color(1, 1, 1, 1);	//　背景の描画色

		//★タスクの生成

		return  true;
	}
	//-------------------------------------------------------------------
	//「終了」タスク消滅時に１回だけ行う処理
	bool  Object::Finalize()
	{
		//★データ＆タスク解放

		if (!ge->QuitFlag() && this->nextTaskCreate)
		{
			//★引き継ぎタスクの生成
			//auto nextTask = Game::Object::Create(true);
		}
		return  true;
	}
	//-------------------------------------------------------------------
	//「更新」1フレーム毎に行う処理
	void  Object::UpDate()
	{
		auto in = DI::GPad_GetState("P1");
		if (in.ST.down)
		{
			this->Kill();
		}
		ge->camera[0]->target = this->pos;

		this->timeCnt++;
	}
	//-------------------------------------------------------------------
	//「2D描画」1フレーム毎に行う処理
	void  Object::Render2D_AF()
	{
		ML::Box2D draw(ge->screen2DWidth / 2 - ge->screen2DWidth / 3, ge->screen2DHeight / 8,
			ge->screen2DWidth * 2 / 3, ge->screen2DHeight / 4);
		ML::Box2D src(0, 0, 900, 200);
		DG::Image_Draw(this->res->imageName, draw, src);

		ML::Box2D tb(100, 100, 500, 20);
		string text = "X:" + to_string(ge->camera[0]->target.x) + "Y:" + to_string(ge->camera[0]->target.y) + "Z:" + to_string(ge->camera[0]->target.z);
		DG::Font_Draw("fon", tb, text,ML::Color(1,1,0,0));
	}
	//-------------------------------------------------------------------
	//「3D描画」1フレーム毎に行う処理
	void  Object::Render3D_L0()
	{
		ML::Mat4x4 matS, matRY, matRZ, matT;
		matT.Translation(this->pos);
		matS.Scaling(100.0f);
		matRY.RotationY(this->playerAngle);
		matRZ.RotationZ(ML::ToRadian(this->timeCnt * 10.0f));
		DG::EffectState().param.matWorld = matS * (matRZ * matRY) * matT;
		DG::Mesh_Draw(this->res->meshName);
	}
	//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	//以下は基本的に変更不要なメソッド
	//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	//-------------------------------------------------------------------
	//タスク生成窓口
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//ゲームエンジンに登録
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//イニシャライズに失敗したらKill
			}
			return  ob;
		}
		return nullptr;
	}
	//-------------------------------------------------------------------
	bool  Object::B_Initialize()
	{
		return  this->Initialize();
	}
	//-------------------------------------------------------------------
	Object::~Object() { this->B_Finalize(); }
	bool  Object::B_Finalize()
	{
		auto  rtv = this->Finalize();
		return  rtv;
	}
	//-------------------------------------------------------------------
	Object::Object() {	}
	//-------------------------------------------------------------------
	//リソースクラスの生成
	Resource::SP  Resource::Create()
	{
		if (auto sp = instance.lock()) {
			return sp;
		}
		else {
			sp = Resource::SP(new  Resource());
			if (sp) {
				sp->Initialize();
				instance = sp;
			}
			return sp;
		}
	}
	//-------------------------------------------------------------------
	Resource::Resource() {}
	//-------------------------------------------------------------------
	Resource::~Resource() { this->Finalize(); }
}