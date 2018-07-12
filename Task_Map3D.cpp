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
		this->wallMesh = "Wall";
		this->floorMesh = "Floor";
		this->ceilingMesh = "Ceiling";
		this->stairsMesh = "Stairs";

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
		this->fPath = "";
		//���^�X�N�̐���

		return  true;
	}
	//-------------------------------------------------------------------
	//�u�I���v�^�X�N���Ŏ��ɂP�񂾂��s������
	bool  Object::Finalize()
	{
		//���f�[�^���^�X�N���


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
	//�}�b�v�̓ǂݍ���
	bool Object::Map_Load(const string& filePath, int y)
	{
		ifstream fin(filePath);
		if (!fin)//�ǂݍ��ݎ��s
		{
			return false;
		}

		//���̃t�@�C���p�X��ǂݍ���
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
	//�����蔻��
	bool Object::Map_HitCheck(const ML::Box3D& hit)
	{

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