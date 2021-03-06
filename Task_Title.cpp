//-------------------------------------------------------------------
//^CgζΚ
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Title.h"
#include  "Task_Game.h"

namespace Title
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//\[XΜϊ»
	bool  Resource::Initialize()
	{
		this->meshName = "Player";
		DG::Mesh_CreateFromSOBFile(this->meshName, "./data/mesh/Player.SOB");
		this->imageName = "TitleLogoImg";
		DG::Image_Create(this->imageName, "./data/image/TitleLogo.png");
		
		DG::Font_Create("fon", "MS Ύ©", 8, 16);
		return true;
	}
	//-------------------------------------------------------------------
	//\[XΜπϊ
	bool  Resource::Finalize()
	{
		DG::Mesh_Erase(this->meshName);
		DG::Image_Erase(this->imageName);
		DG::Font_Erase("fon");
		return true;
	}
	//-------------------------------------------------------------------
	//uϊ»v^XNΆ¬ΙPρΎ―s€
	bool  Object::Initialize()
	{
		//X[p[NXϊ»
		__super::Initialize(defGroupName, defName, true);
		//\[XNXΆ¬or\[X€L
		this->res = Resource::Create();

		//f[^ϊ»
		this->pos = ML::Vec3(0, 0, 0);
		this->playerAngle = ML::ToRadian(-45.0f);
		this->timeCnt = 0;

		//JΜΆ¬
		ge->camera[0] = MyPG::Camera::Create(
			ML::Vec3(0.0f, 0.0f, 0.0f),						//	^[QbgΚu
			ML::Vec3(0.0f, 0.0f, -300.0f),						//	JΚu
			ML::Vec3(0.0f, 1.0f, 0.0f),								//	JΜγϋόxNg
			ML::ToRadian(35), 10.0f, 4000.0f,						//	μpEμ£
			(float)ge->screenWidth / (float)ge->screenHeight);		//	ζΚδ¦		
		DG::EffectState().param.bgColor = ML::Color(1, 1, 1, 1);	//@wiΜ`ζF

		//^XNΜΆ¬

		return  true;
	}
	//-------------------------------------------------------------------
	//uIΉv^XNΑΕΙPρΎ―s€
	bool  Object::Finalize()
	{
		//f[^^XNπϊ

		if (!ge->QuitFlag() && this->nextTaskCreate)
		{
			//ψ«p¬^XNΜΆ¬
			auto nextTask = Game::Object::Create(true);
		}
		return  true;
	}
	//-------------------------------------------------------------------
	//uXVv1t[Ιs€
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
	//u2D`ζv1t[Ιs€
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
	//u3D`ζv1t[Ιs€
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
	//
	//ΘΊΝξ{IΙΟXsvΘ\bh
	//
	//-------------------------------------------------------------------
	//^XNΆ¬ϋ
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//Q[GWΙo^
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//CjVCYΙΈs΅½ηKill
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
	//\[XNXΜΆ¬
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