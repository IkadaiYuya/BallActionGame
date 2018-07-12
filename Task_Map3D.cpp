//-------------------------------------------------------------------
//マップ
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Map3D.h"
#include  "Task_Player.h"

namespace Map3D
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//リソースの初期化
	bool  Resource::Initialize()
	{
		this->wallMesh = "Wall";
		this->floorMesh = "Floor";
		this->ceilingMesh = "Ceiling";
		this->stairsMesh = "Stairs";

		return true;
	}
	//-------------------------------------------------------------------
	//リソースの解放
	bool  Resource::Finalize()
	{
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
		//マップの初期化
		for (int y = 0; y < MapSizeY; ++y)
		{
			for (int z = 0; z < MapSizeZ; ++z)
			{
				for (int x = 0; x < MapSizeX; ++x)
				{
					this->arr[y][z][x] = Box();
				}
			}
		}
		this->fPath = "";
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
			
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//「更新」1フレーム毎に行う処理
	void  Object::UpDate()
	{
	}
	//-------------------------------------------------------------------
	//「2D描画」1フレーム毎に行う処理
	void  Object::Render2D_AF()
	{
	}
	//-------------------------------------------------------------------
	//「3D描画」1フレーム毎に行う処理
	void  Object::Render3D_L0()
	{
		ML::Mat4x4 matT, matS;
		matS.Scaling(100);
		for (int y = 0; y < MapSizeY; ++y)
		{
			for (int z = 0; z < MapSizeZ; ++z)
			{
				for (int x = 0; x < MapSizeX; ++x)
				{
					matT.Translation(this->arr[y][z][x].Get_Pos());
					DG::EffectState().param.matWorld = matS * matT;
					switch (this->arr[y][z][x].Get_Type())
					{

					}
				}
			}
		}
	}
	//-------------------------------------------------------------------
	//マップの読み込み
	bool Object::Map_Load(const string& filePath, int y)
	{
		ifstream fin(filePath);
		if (!fin)//読み込み失敗
		{
			return false;
		}

		//次のファイルパスを読み込み
		fin >> this->fPath;
		
		int in = 0;
		for (int z = 0; z < MapSizeZ; ++z)
		{
			for (int x = 0; x < MapSizeX; ++x)
			{
				fin >> in;

				ML::Vec3 pos(x * ChipX, y * ChipY, z * ChipZ);
				ML::Box3D hitBase(0, 0, 0, ChipX, ChipY, ChipZ);

				switch ((BoxType)in)
				{
				case BoxType::floor:
				case BoxType::ceiling:
				case BoxType::wall:
				case BoxType::stairs:
				case BoxType::goal:
					this->arr[y][z][x].Initialize_Box(pos, hitBase, in);
					break;
				case BoxType::start:
					auto pl = Player::Object::Create(true);
					pl->Set_Pos(pos + ML::Vec3(ChipX / 2, ChipY / 2, ChipZ / 2));
				}
			}
		}
	}
	//-------------------------------------------------------------------
	//あたり判定
	bool Object::Map_HitCheck(const ML::Box3D& hit)
	{

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