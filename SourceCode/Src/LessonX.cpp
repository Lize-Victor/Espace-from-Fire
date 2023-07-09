/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////

#include <Stdio.h>
#include <ctime>
#include "CommonClass.h"
#include "LessonX.h"
#include "NewClass.h"
#include "CustomFunction.h"
#include <vector>
using std::vector;

////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain g_GameMain;

vector<Floor *> l_Floor;
//==============================================================================
//
// 大体的程序流程为：GameMainLoop函数为主循环函数，在引擎每帧刷新屏幕图像之后，都会被调用一次。

//==============================================================================
//
// 构造函数
CGameMain::CGameMain()
{
	m_iGameState = 1;
    Player1 = new CSprite("Player1");
    iPosX=5;
	iPosY=-15;
	m_fScreenBottom = 0.f;
	m_fScreenLeft = 0.f;
	m_fScreenRight = 0.f;
	m_fScreenTop = 0.f;
	
}
//==============================================================================
//
// 析构函数
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// 游戏主循环，此函数将被不停的调用，引擎每刷新一次屏幕，此函数即被调用一次
// 用以处理游戏的开始、进行中、结束等各种状态.
// 函数参数fDeltaTime : 上次调用本函数到此次调用本函数的时间间隔，单位：秒
void CGameMain::GameMainLoop(float fDeltaTime)
{
	switch (GetGameState())
	{
		// 初始化游戏，清空上一局相关数据
	case 1:
	{
		GameInit();
		SetGameState(2); // 初始化之后，将游戏状态设置为进行中
		PlaySound("D:\\Espace-from-Fire\\Music\\新建文件夹\\Music.wav",NULL,SND_ASYNC|SND_LOOP);
	}
	break;

		// 游戏进行中，处理各种游戏逻辑
	case 2:
	{
		// TODO 修改此处游戏循环条件，完成正确游戏逻辑
		if (true)
		{
			GameRun(fDeltaTime);
		}
		else // 游戏结束。调用游戏结算函数，并把游戏状态修改为结束状态
		{
			SetGameState(0);
			GameEnd();
		}
	}
	break;

		// 游戏结束/等待按空格键开始
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// 每局开始前进行初始化，清空上一局相关数据
void CGameMain::GameInit()
{

	for (int i = 0; i < FLOOR_HEIGHT_NUM; i++)
	{
		Floor *tmp_Floor;
		tmp_Floor = new Floor;
		tmp_Floor->FloorInit(i + 1);
		l_Floor.push_back(tmp_Floor);
	}

	// 寻找中心点
	srand(time(nullptr));
	int l_FloorNumStart = rand() % FLOOR_HEIGHT_NUM + 1; // 范围 1~9

	FloorMove(0 * FLOOR_Y, l_Floor);

	// 火焰和烟雾的初始化
	for (int i = 0; i < FLOOR_HEIGHT_NUM; i++)
	{
		l_Floor[i]->FireInit();
		l_Floor[i]->SmogInit();
	}

	int l_FireFloorNum = rand() % FLOOR_HEIGHT_NUM;

	l_Floor[1]->FireBoom();

	for (int i = 0; i < FLOOR_HEIGHT_NUM; i++)
	{
		l_Floor[i]->SmogWarningInit();
	}

	m_iGameState = 1;
	m_fScreenLeft = CSystem::GetScreenLeft();
	m_fScreenRight = CSystem::GetScreenRight();
	m_fScreenTop = CSystem::GetScreenTop();
	m_fScreenBottom = CSystem::GetScreenBottom();
	Player1->SetSpriteWorldLimit(WORLD_LIMIT_NULL, m_fScreenLeft,m_fScreenTop, m_fScreenRight, m_fScreenBottom);
	Player1->SetSpriteLinearVelocity( 0, 0);
	
}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun(float fDeltaTime)
{

	for (int i = 0; i < FLOOR_HEIGHT_NUM; i++)
	{
	l_Floor[i]->FireProduceSmog(fDeltaTime);
	l_Floor[i]->FireDiffusionY(fDeltaTime);
	l_Floor[i]->FireDiffusionX(fDeltaTime);
	l_Floor[i]->SmogDiffusionX(fDeltaTime);
	}
    Player1->SetSpriteConstantForceY(0);
	//l_Floor[1]->FireDiffusionX(fDeltaTime);


}
//=============================================================================
//
// 本局游戏结束
void CGameMain::GameEnd()
{
}
//==========================================================================
//
// 鼠标移动
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseMove(const float fMouseX, const float fMouseY)
{
}
//==========================================================================
//
// 鼠标点击
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY)
{
}
//==========================================================================
//
// 鼠标弹起
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY)
{
}
//==========================================================================
//
// 键盘按下
// 参数 iKey：被按下的键，值见 enum KeyCodes 宏定义
// 参数 iAltPress, iShiftPress，iCtrlPress：键盘上的功能键Alt，Ctrl，Shift当前是否也处于按下状态(0未按下，1按下)
void CGameMain::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress)
{
	float fSpeedUP = 0, fSpeedDOWN = 0, fSpeedLEFT = 0, fSpeedRIGHT = 0;
	switch (iKey)
	{
	case KEY_W: // W向上
	fSpeedUP = -10.f;
	break;
	case KEY_A: // A向左
	fSpeedLEFT = -15.f;
	break;
	case KEY_S: // S向下
	fSpeedDOWN = 10.f;
	break;
	case KEY_D: // D向右
	fSpeedRIGHT = 15.f;
	break;
	}
	if ((fSpeedLEFT + fSpeedRIGHT) > 0) // 如果向左则要转向
	Player1->SetSpriteFlipX(false);
	else if ((fSpeedLEFT + fSpeedRIGHT) < 0) // 如果向右则不转向
	Player1->SetSpriteFlipX(true);
	Player1->SetSpriteLinearVelocity(fSpeedLEFT + fSpeedRIGHT, fSpeedUP +fSpeedDOWN);
	if (iKey == KEY_SPACE)
	{ // 向上跳
	if (m_jumpFlag == 0)
	{ // 未在跳跃过程中
			Player1->SetSpriteLinearVelocityY(-30);
			Player1->SetSpriteImpulseForce(0, -5, false); // 防止跳不上去，给一个瞬时的推力
			m_jumpFlag = 1;								  // jumping
	}
	}
}
//==========================================================================
//
// 键盘弹起
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
void CGameMain::OnKeyUp(const int iKey)
{
	if(iKey == KEY_W || iKey == KEY_A || iKey == KEY_S || iKey == KEY_D)
    Player1->SetSpriteLinearVelocity(0,0);
}
//===========================================================================
//
// 精灵与精灵碰撞
// 参数 szSrcName：发起碰撞的精灵名字
// 参数 szTarName：被碰撞的精灵名字
void CGameMain::OnSpriteColSprite(const char *szSrcName, const char *szTarName)
{
	if(strstr(szSrcName,"Smog") != 0 && strstr(szTarName,"SmogWarning"))
	{
		for (int i = 0; i < FLOOR_HEIGHT_NUM; i++)
		{
			l_Floor[i]->SmogWarningBing();
		}

	}
}
//===========================================================================
//
// 精灵与世界边界碰撞
// 参数 szName：碰撞到边界的精灵名字
// 参数 iColSide：碰撞到的边界 0 左边，1 右边，2 上边，3 下边
void CGameMain::OnSpriteColWorldLimit(const char *szName, const int iColSide)
{
	if (strcmp(szName, "Player1") == 0)
	{
		Player1->SetSpriteLinearVelocity(0, 0);
	}
}
