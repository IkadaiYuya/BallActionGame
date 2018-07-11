//-------------------------------------------------------------------
//�^�C�g�����
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Title.h"
#include  "Task_Game.h"

namespace Title
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//���\�[�X�̏�����
	bool  Resource::Initialize()
	{
		this->meshName = "PlayerMesh";
		DG::Mesh_CreateFromSOBFile(this->meshName, "./data/mesh/Player.SOB");
		this->imageName = "TitleLogoImg";
		DG::Image_Create(this->imageName, "./data/image/TitleLogo.png");
		
		DG::Font_Create("fon", "MS ����", 8, 16);
		return true;
	}
	//-------------------------------------------------------------------
	//���\�[�X�̉��
	bool  Resource::Finalize()
	{
		DG::Mesh_Erase(this->meshName);
		DG::Image_Erase(this->imageName);
		DG::Font_Erase("fon");
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
		this->playerAngle = ML::ToRadian(-45.0f);
		this->timeCnt = 0;

		//�J�����̐���
		ge->camera[0] = MyPG::Camera::Create(
			ML::Vec3(0.0f, 0.0f, 0.0f),						//	�^�[�Q�b�g�ʒu
			ML::Vec3(0.0f, 0.0f, -300.0f),						//	�J�����ʒu
			ML::Vec3(0.0f, 1.0f, 0.0f),								//	�J�����̏�����x�N�g��
			ML::ToRadian(35), 10.0f, 4000.0f,						//	����p�E���싗��
			(float)ge->screenWidth / (float)ge->screenHeight);		//	��ʔ䗦		
		DG::EffectState().param.bgColor = ML::Color(1, 1, 1, 1);	//�@�w�i�̕`��F

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
			//auto nextTask = Game::Object::Create(true);
		}
		return  true;
	}
	//-------------------------------------------------------------------
	//�u�X�V�v1�t���[�����ɍs������
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
	//�u2D�`��v1�t���[�����ɍs������
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
	//�u3D�`��v1�t���[�����ɍs������
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