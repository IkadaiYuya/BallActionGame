#pragma once
#include "MyPG.h"

enum TaskFlag
{
	Task_Non,		//�^�X�N�����I�����
	Task_Title,		//�^�C�g��
	Task_Game,		//�Q�[���{��

	//�ȉ��K�v�ɉ����Ēǉ�
};

extern  void  MyGameMain_Finalize( );
extern  void  MyGameMain_Initalize( );
extern  void  MyGameMain_UpDate( );
extern  void  MyGameMain_Render2D_BF();
extern  void  MyGameMain_Render2D_AF();
extern  void  MyGameMain_Render3D_L0();
extern  void  MyGameMain_Render3D_L1();
extern  void  MyGameMain_Render3D_L2();
extern  void  MyGameMain_Render3D_L3();