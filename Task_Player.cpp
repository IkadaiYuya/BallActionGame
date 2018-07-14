//-------------------------------------------------------------------
//�v���C��
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Player.h"
#include  "Task_Camera.h"

namespace Player
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//���\�[�X�̏�����
	bool  Resource::Initialize()
	{
		this->playerMesh = "PlayerMesh";
		DG::Mesh_CreateFromSOBFile(this->playerMesh, "./data/mesh/Player.SOB");
		return true;
	}
	//-------------------------------------------------------------------
	//���\�[�X�̉��
	bool  Resource::Finalize()
	{
		DG::Mesh_Erase(this->playerMesh);
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
		this->pos = ML::Vec3(0, 0, 0);
		this->hitBase = ML::Box3D(0, 0, 0, 100, 100, 100);
		this->angle = ML::Vec3(0, 0, 0);
		//���^�X�N�̐���
		Camera::Object::Create(true);

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
		auto in = DI::GPad_GetState("P1");

		if (in.LStick.volume > 0)
		{
			this->pos.x -= in.LStick.axis.y * 5;
			this->pos.z -= in.LStick.axis.x * 5;
		}

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
		matT.Translation(this->pos);
		matS.Scaling(100);
		DG::EffectState().param.matWorld = matS * matT;
		DG::Mesh_Draw(this->res->playerMesh);
	}
	//-------------------------------------------------------------------
	//�v���C���̏����ʒu�w��
	void Object::Set_Pos(const ML::Vec3& pos)
	{
		this->pos = pos;
	}
	//-------------------------------------------------------------------
	//
	ML::Vec3 Object::Get_Pos()
	{
		return this->pos;
	}
	//-------------------------------------------------------------------
	//�A�j���[�V����
	void Object::Anim_Player()
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