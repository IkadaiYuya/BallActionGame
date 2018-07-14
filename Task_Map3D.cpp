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

		//マップ仮処理
		for (int z = 0; z < MapSizeZ; ++z)
		{
			for (int x = 0; x < MapSizeX; ++x)
			{
				ML::Vec3 pos(x * ChipX + ChipX / 2.0f, 0 * ChipY + ChipY / 2.0f, z * ChipZ + ChipZ / 2.0f);
				ML::Box3D hit(0, 0, 0, ChipX, ChipY, ChipZ);
				int type = int(box);
				this->arr[0][z][x].Initialize_Box(pos, hit, type);
				this->arr[0][z][x].Set_MeshName("Box");
			}
		}
		auto pl = Player::Object::Create(true);
		ML::Vec3 pos(3 * ChipX + ChipX / 2.0f, 1 * ChipY + ChipY / 2.0f, 3 * ChipZ + ChipZ / 2.0f);
		pl->Set_Pos(pos);

		this->fPath = "";

		DG::Mesh_CreateFromSOBFile("Box", "./data/mesh/Box.SOB");
		//★タスクの生成

		return  true;
	}
	//-------------------------------------------------------------------
	//「終了」タスク消滅時に１回だけ行う処理
	bool  Object::Finalize()
	{
		//★データ＆タスク解放
		DG::Mesh_Erase("Box");

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
		auto pl = ge->GetTask_One_G<Player::Object>("プレイヤ");
		//描画範囲をプレイヤを中心に　マス分に限定
		int sx, sy, sz, ex, ey, ez;
		sx = max(0, int(pl->Get_Pos().x / ChipX) - (MapSizeX / MapRenPar));
		sy = max(0, int(pl->Get_Pos().y / ChipY) - (MapSizeY / MapRenPar));
		sz = max(0, int(pl->Get_Pos().z / ChipZ) - (MapSizeZ / MapRenPar));
		ex = min(MapSizeX, int(pl->Get_Pos().x / ChipX) + (MapSizeX / MapRenPar));
		ey = min(MapSizeY, int(pl->Get_Pos().y / ChipY) + (MapSizeY / MapRenPar));
		ez = min(MapSizeZ, int(pl->Get_Pos().z / ChipZ) + (MapSizeZ / MapRenPar));
		for (int y = sy; y < ey; ++y)
		{
			for (int z = sz; z < ez; ++z)
			{
				for (int x = sx; x < ex; ++x)
				{
					if (this->arr[y][z][x].Check_Rendering())
					{
						this->arr[y][z][x].Render3D();
					}
				}
			}
		}

	}
	//-------------------------------------------------------------------
	//マップチップの読み込み
	bool Object::MapChip_Load(const string filePath)
	{
		ifstream fin(filePath);
		if (!fin)// 
		{
			return false;
		}
		
		return false;
	}
	//-------------------------------------------------------------------
	//マップの読み込み
	bool Object::Map_Load(const string filePath)
	{
		ifstream fin(filePath);
		if (!fin)//読み込み失敗
		{
			return false;
		}

		//次のファイルパスを読み込み
		fin >> this->fPath;
		
		int in = 0;
		for (int y = 0; y < MapSizeY; ++y)
		{
			for (int z = 0; z < MapSizeZ; ++z)
			{
				for (int x = 0; x < MapSizeX; ++x)
				{
					fin >> in;

					ML::Vec3 pos(float(x) * ChipX, float(y) * ChipY, float(z) * ChipZ);
					ML::Box3D hitBase(0, 0, 0, ChipX, ChipY, ChipZ);

					switch ((BoxType)in)
					{
					case BoxType::box:
						this->arr[y][z][x].Initialize_Box(pos, hitBase, in);
						this->arr[y][z][x].Set_MeshName("Box");
						break;
					case BoxType::stairs:
						this->arr[y][z][x].Initialize_Box(pos, hitBase, in);
						this->arr[y][z][x].Set_MeshName("Stairs");
						break;
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
		return true;
	}
	//-------------------------------------------------------------------
	//あたり判定
	bool Object::Map_HitCheck(const ML::Box3D& hit)
	{
		return false;
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