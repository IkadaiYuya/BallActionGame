//-------------------------------------------------------------------
//�}�b�v
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Map3D.h"
#include  "Task_Player.h"

namespace Map3D
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//���\�[�X�̏�����
	bool  Resource::Initialize()
	{
		return true;
	}
	//-------------------------------------------------------------------
	//���\�[�X�̉��
	bool  Resource::Finalize()
	{
		return true;
	}
	//-------------------------------------------------------------------
	//�u�������v�^�X�N�������ɂP�񂾂��s������
	bool  Object::Initialize()
	{
		//�X�[�p�[�N���X������
		__super::Initialize(defGroupName, defName, true);
		//���\�[�X�N���X����or���\�[�X���L
		this->res = Resource::Create();

		//���f�[�^������
		//�}�b�v�̏�����
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

		//�}�b�v������
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
		//���^�X�N�̐���

		return  true;
	}
	//-------------------------------------------------------------------
	//�u�I���v�^�X�N���Ŏ��ɂP�񂾂��s������
	bool  Object::Finalize()
	{
		//���f�[�^���^�X�N���
		DG::Mesh_Erase("Box");

		if (!ge->QuitFlag() && this->nextTaskCreate)
		{
			//�������p���^�X�N�̐���		
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//�u�X�V�v1�t���[�����ɍs������
	void  Object::UpDate()
	{
	}
	//-------------------------------------------------------------------
	//�u2D�`��v1�t���[�����ɍs������
	void  Object::Render2D_AF()
	{

	}
	//-------------------------------------------------------------------
	//�u3D�`��v1�t���[�����ɍs������
	void  Object::Render3D_L0()
	{
		auto pl = ge->GetTask_One_G<Player::Object>("�v���C��");
		//�`��͈͂��v���C���𒆐S�Ɂ@�}�X���Ɍ���
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
	//�}�b�v�`�b�v�̓ǂݍ���
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
	//�}�b�v�̓ǂݍ���
	bool Object::Map_Load(const string filePath)
	{
		ifstream fin(filePath);
		if (!fin)//�ǂݍ��ݎ��s
		{
			return false;
		}

		//���̃t�@�C���p�X��ǂݍ���
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
	//�����蔻��
	bool Object::Map_HitCheck(const ML::Box3D& hit)
	{
		return false;
	}
	//������������������������������������������������������������������������������������
	//�ȉ��͊�{�I�ɕύX�s�v�ȃ��\�b�h
	//������������������������������������������������������������������������������������
	//-------------------------------------------------------------------
	//�^�X�N��������
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//�Q�[���G���W���ɓo�^
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//�C�j�V�����C�Y�Ɏ��s������Kill
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
	//���\�[�X�N���X�̐���
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