//-------------------------------------------------------------------
//J
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Camera.h"
#include  "Task_Player.h"

namespace Camera
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//\[XΜϊ»
	bool  Resource::Initialize()
	{
		return true;
	}
	//-------------------------------------------------------------------
	//\[XΜπϊ
	bool  Resource::Finalize()
	{
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
		ge->camera[0] = MyPG::Camera::Create(
			ML::Vec3(0.0f, 0.0f, 0.0f),						//	^[QbgΚu
			ML::Vec3(0.0f, 0.0f, 0.0f),					//	JΚu
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
			
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//uXVv1t[Ιs€
	void  Object::UpDate()
	{
		auto pl = ge->GetTask_One_G<Player::Object>("vC");
		ge->camera[0]->pos = pl->Get_Pos() + ML::Vec3(10, 800, 0);
		ge->camera[0]->target = pl->Get_Pos();
	}
	//-------------------------------------------------------------------
	//u2D`ζv1t[Ιs€
	void  Object::Render2D_AF()
	{
	}
	//-------------------------------------------------------------------
	//u3D`ζv1t[Ιs€
	void  Object::Render3D_L0()
	{
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