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
#include "Floor.h"
#include "CustomFunction.h"
#include <vector>
using std::vector;

////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain g_GameMain;

vector<Floor *> g_Floor;

//==============================================================================
//
// 大体的程序流程为：GameMainLoop函数为主循环函数，在引擎每帧刷新屏幕图像之后，都会被调用一次。

//==============================================================================
//
// 构造函数
CGameMain::CGameMain()
{
	m_iGameState = 0;
    Player1 = new CSprite("Player1");
	Player2 = new CSprite("Player2");
    iPosX=5;
	iPosY=-15;
	m_fScreenBottom = 0.f;
	m_fScreenLeft = 0.f;
	m_fScreenRight = 0.f;
	m_fScreenTop = 0.f;
	a=0;
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
						 // PlaySound("E:\\FunCode_CppProject\\FunCode_Project\\Music\\新建文件夹\\Music.wav", NULL, SND_ASYNC | SND_LOOP);
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

		// 人物在电梯当中
	case 3:
	{
		m_pElevatorMap->SetSpriteVisible(true);
		m_pElevatorPerson->SetSpriteVisible(true);
		GameRun(fDeltaTime);
	}
	break;
		// 游戏结束/等待按空格键开始
	case 0:
	{
		CSystem::LoadMap("elevator_map.t2d"); // 载入开始界面
	}
	break;
	};
}
//=============================================================================
//
// 每局开始前进行初始化，清空上一局相关数据
void CGameMain::GameInit()
{
	// 计时器的初始化
	m_fTime = 0.f;
	m_pTime = new CTextSprite("time");

	// 血量的初始化
	Player1_Blood = 100;
	Player2_Blood = 100;
	m_pP1Blood = new CTextSprite("blood");
	m_pP2Blood = new CTextSprite("blood2");


	// 电梯地图的初始化
	m_pElevatorMap = new CSprite("elevator_map");
	m_pElevatorPerson = new CSprite("elevator_person");
	m_pElevatorMap->SetSpriteVisible(false);
	m_pElevatorPerson->SetSpriteVisible(false);

	for (int i = 0; i < FLOOR_HEIGHT_NUM; i++)
	{
		Floor *tmp_Floor;
		tmp_Floor = new Floor;
		tmp_Floor->FloorInit(i + 1);
		g_Floor.push_back(tmp_Floor);
	}

	// 寻找中心点
	srand(time(nullptr));
	m_iPlayer1InFloorNum = rand() % FLOOR_HEIGHT_NUM + 1; // 范围 1~9
	m_iPlayer2InFloorNum = m_iPlayer1InFloorNum;
    FloorMove(2, m_iPlayer1InFloorNum - 2, g_Floor);

	// 道具的初始化
	m_pProp = new prop;
	m_pProp->PropInit(g_Floor[m_iPlayer1InFloorNum - 1]->GetPropNum());

	// 窗户的初始化
	m_pWin = new Win;
	m_pWin->WindowInit(g_Floor[m_iPlayer1InFloorNum - 1]->GetWinLockState());

	// 火焰和烟雾的初始化
	for (int i = 0; i < FLOOR_HEIGHT_NUM; i++)
	{
		g_Floor[i]->FireInit();
		g_Floor[i]->SmogInit();
	}

	// 烟雾报警初始化
	for (int i = 0; i < FLOOR_HEIGHT_NUM; i++)
	{
		g_Floor[i]->SmogWarningInit();
	}

	// 火焰爆发 游戏开始
	int l_FireFloorNum = rand() % FLOOR_HEIGHT_NUM;
	g_Floor[1]->FireBoom();
	m_iGameState = 1;

	// 设置人物边界
	m_fScreenLeft = 0.f;
	m_fScreenRight = 150.f;
	m_fScreenTop = -56.f;
	m_fScreenBottom = -32.f;

	// 人物属性的初始化
	Player1->SetSpriteCollisionReceive(true);
	Player2->SetSpriteCollisionReceive(true);
	Player1->SetSpriteCollisionSend(true);
	Player2->SetSpriteCollisionSend(true);
	Player1->SetSpriteWorldLimit(WORLD_LIMIT_NULL, m_fScreenLeft,m_fScreenTop, m_fScreenRight, m_fScreenBottom);
	Player1->SetSpriteLinearVelocity( 0, 0);
	Player2->SetSpriteWorldLimit(WORLD_LIMIT_NULL, m_fScreenLeft,m_fScreenTop, m_fScreenRight, m_fScreenBottom);
	Player2->SetSpriteLinearVelocity( 0, 0);

}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun(float fDeltaTime)
{
	// 计时器更新
	m_fTime += fDeltaTime;
	m_pTime->SetTextValue((int)m_fTime);

	// 血量更新
	m_pP1Blood->SetTextValue(Player1_Blood);
	m_pP2Blood->SetTextValue(Player2_Blood);

	for (int i = 0; i < FLOOR_HEIGHT_NUM; i++)
	{
		g_Floor[i]->FireProduceSmog(fDeltaTime);
		g_Floor[i]->FireDiffusionY(fDeltaTime);
		g_Floor[i]->FireDiffusionX(fDeltaTime);
		g_Floor[i]->SmogDiffusionX(fDeltaTime);
	}

	Player2->SetSpriteConstantForceY(0);
	// g_Floor[1]->FireDiffusionX(fDeltaTime);
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
	if (m_iGameState == 0)
	{
		m_iGameState = 1;
		CSystem::LoadMap("text.t2d");
	}
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
{ // 游戏正常运行时
	if (m_iGameState == 2)
	{

		// 实现人物运动
		switch (iKey)
		{
		case KEY_W: // W向上
			m_fSpeedUP = -10.f;
			break;
		case KEY_A: // A向左
			if (bShiftPress)
			{
				m_fSpeedLEFT = -30.f;
			}
			m_fSpeedLEFT = -15.f;
			break;
		case KEY_S: // S向下
			m_fSpeedDOWN = 10.f;
			break;
		case KEY_D: // D向右
			if (bShiftPress)
			{
				m_fScreenRight = 30.f;
			}
			m_fSpeedRIGHT = 15.f;
			break;
		}
		if ((m_fSpeedLEFT + m_fSpeedRIGHT) > 0) // 如果向左则要转向
			Player1->SetSpriteFlipX(false);
		else if ((m_fSpeedLEFT + m_fSpeedRIGHT) < 0) // 如果向右则不转向
			Player1->SetSpriteFlipX(true);
		Player1->SetSpriteLinearVelocity(m_fSpeedLEFT + m_fSpeedRIGHT, m_fSpeedUP + m_fSpeedDOWN);

		switch (iKey)
		{
		case KEY_UP: // W向上
			m_fSpeedUp = -10.f;
			break;
		case KEY_LEFT: // A向左
		    if(bShiftPress)
			{
				m_fSpeedLeft = -30.f;
			}
			m_fSpeedLeft = -15.f;
			break;
		case KEY_DOWN: // S向下
			m_fSpeedDown = 10.f;
			break;
		case KEY_RIGHT: // D向右
		    if(bShiftPress)
			{
				m_fSpeedRight = -30.f;
			}
			m_fSpeedRight = 15.f;
			break;
		}
		if ((m_fSpeedLeft + m_fSpeedRight) > 0) // 如果向左则要转向
			Player2->SetSpriteFlipX(false);
		else if ((m_fSpeedLeft + m_fSpeedRight) < 0) // 如果向右则不转向
			Player2->SetSpriteFlipX(true);
		Player2->SetSpriteLinearVelocity(m_fSpeedLeft + m_fSpeedRight, m_fSpeedUp + m_fSpeedDown);
		if (iKey == KEY_K)
			a == 1;

		if (iKey == KEY_0)
		{ // 向上跳
			if (m_jumpFlag == 0)
			{ // 未在跳跃过程中
				Player2->SetSpriteLinearVelocityY(-30);
				Player2->SetSpriteImpulseForce(0, -5, false); // 防止跳不上去，给一个瞬时的推力
				Player2->SetSpriteConstantForceY(20);
				m_jumpFlag = 1;								  // jumping
			}
		}

		if (iKey == KEY_SPACE)
		{ // 向上跳
			if (m_jumpFlag == 0)
			{ // 未在跳跃过程中
				Player1->SetSpriteLinearVelocityY(-30);
				Player1->SetSpriteImpulseForce(0, -5, false); // 防止跳不上去，给一个瞬时的推力
				Player1->SetSpriteConstantForceY(20);
				m_jumpFlag = 1; // jumping
			}
		}

		// 响应灭火
		if (m_iPropNumInTable == 5 && iKey == KEY_J)
		{
			g_Floor[m_iPlayer1InFloorNum - 1]->ExtinguisherOutFire();
		}
		// 丢弃道具
		if (m_iPropNumInTable && iKey == KEY_K)
		{
			m_pProp->OutPropTable(Player1->GetSpritePositionX() + 10, Player1->GetSpritePositionY());
			m_iPropNumInTable = 0;
		}
		// 人物进入电梯
		if (Player1->GetSpritePositionX() < 80.f && Player1->GetSpritePositionX() > 60.125 && iKey == KEY_U)
		{
			m_pElevatorMap->SetSpriteVisible(true);
			m_pElevatorPerson->SetSpriteVisible(true);
			m_iGameState = 3;
		}
	}

	// 实现电梯的楼层移动
	if (m_iGameState == 3)
	{
		switch (iKey)
		{
		case KEY_1:
			m_iGameState = 2;
			FloorMove(m_iPlayer1InFloorNum, -1, g_Floor);
			m_iPlayer1InFloorNum = 1;
			m_pProp->PropUpdate(g_Floor[0]->GetPropNum());
			m_pElevatorMap->SetSpriteVisible(false);
			m_pElevatorPerson->SetSpriteVisible(false);
			break;
		case KEY_2:
			m_iGameState = 2;
			FloorMove(m_iPlayer1InFloorNum, 0, g_Floor);
			m_iPlayer1InFloorNum = 2;
			m_pProp->PropUpdate(g_Floor[1]->GetPropNum());
			m_pElevatorMap->SetSpriteVisible(false);
			m_pElevatorPerson->SetSpriteVisible(false);
			break;
		case KEY_3:
			m_iGameState = 2;
			FloorMove(m_iPlayer1InFloorNum, 1, g_Floor);
			m_iPlayer1InFloorNum = 3;
			m_pProp->PropUpdate(g_Floor[2]->GetPropNum());
			m_pElevatorMap->SetSpriteVisible(false);
			m_pElevatorPerson->SetSpriteVisible(false);
			break;
		case KEY_4:
			m_iGameState = 2;
			FloorMove(m_iPlayer1InFloorNum, 2, g_Floor);
			m_iPlayer1InFloorNum = 4;
			m_pProp->PropUpdate(g_Floor[3]->GetPropNum());
			m_pElevatorMap->SetSpriteVisible(false);
			m_pElevatorPerson->SetSpriteVisible(false);
			break;
		case KEY_5:
			m_iGameState = 2;
			FloorMove(m_iPlayer1InFloorNum, 3, g_Floor);
			m_iPlayer1InFloorNum = 5;
			m_pProp->PropUpdate(g_Floor[4]->GetPropNum());
			m_pElevatorMap->SetSpriteVisible(false);
			m_pElevatorPerson->SetSpriteVisible(false);
			break;
		case KEY_6:
			m_iGameState = 2;
			FloorMove(m_iPlayer1InFloorNum, 4, g_Floor);
			m_iPlayer1InFloorNum = 6;
			m_pProp->PropUpdate(g_Floor[5]->GetPropNum());
			m_pElevatorMap->SetSpriteVisible(false);
			m_pElevatorPerson->SetSpriteVisible(false);
			break;
		case KEY_7:
			m_iGameState = 2;
			FloorMove(m_iPlayer1InFloorNum, 5, g_Floor);
			m_iPlayer1InFloorNum = 7;
			m_pProp->PropUpdate(g_Floor[6]->GetPropNum());
			m_pElevatorMap->SetSpriteVisible(false);
			m_pElevatorPerson->SetSpriteVisible(false);
			break;
		case KEY_8:
			m_iGameState = 2;
			FloorMove(m_iPlayer1InFloorNum, 6, g_Floor);
			m_iPlayer1InFloorNum = 8;
			m_pProp->PropUpdate(g_Floor[7]->GetPropNum());
			m_pElevatorMap->SetSpriteVisible(false);
			m_pElevatorPerson->SetSpriteVisible(false);
			break;
		case KEY_9:
			m_iGameState = 2;
			FloorMove(m_iPlayer1InFloorNum, 7, g_Floor);
			m_iPlayer1InFloorNum = 9;
			m_pProp->PropUpdate(g_Floor[8]->GetPropNum());
			m_pElevatorMap->SetSpriteVisible(false);
			m_pElevatorPerson->SetSpriteVisible(false);
			break;
		default:
			break;
		}
	}
}
//==========================================================================
//
// 键盘弹起
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
void CGameMain::OnKeyUp(const int iKey)
{
	if (m_iGameState == 2)
	{
		switch (iKey)
		{
		case KEY_W: // W向上
			m_fSpeedUP = 0.f;
			break;
		case KEY_A: // A向左
			m_fSpeedLEFT = 0.f;
			break;
		case KEY_S: // S向下
			m_fSpeedDOWN = 0.f;
			break;
		case KEY_D: // D向右
			m_fSpeedRIGHT = 0.f;
			break;
		}
		if ((m_fSpeedLEFT + m_fSpeedRIGHT) > 0) // 如果向左则要转向
			Player1->SetSpriteFlipX(false);
		else if ((m_fSpeedLEFT + m_fSpeedRIGHT) < 0) // 如果向右则不转向
			Player1->SetSpriteFlipX(true);
		Player1->SetSpriteLinearVelocity(m_fSpeedLEFT + m_fSpeedRIGHT, m_fSpeedUP + m_fSpeedDOWN);

		if (iKey == KEY_SPACE)
		{
			if (m_jumpFlag == 1)
			{
				m_jumpFlag = 0;
			}
		}
	}
}
//===========================================================================
//
// 精灵与精灵碰撞
// 参数 szSrcName：发起碰撞的精灵名字
// 参数 szTarName：被碰撞的精灵名字
void CGameMain::OnSpriteColSprite(const char *szSrcName, const char *szTarName)
{
	if (strstr(szSrcName, "Smog") != 0 && strstr(szTarName, "SmogWarning"))
	{
		for (int i = 0; i < FLOOR_HEIGHT_NUM; i++)
		{
			g_Floor[i]->SmogWarningBing();
		}
	}

	if (strcmp(szTarName, "Player1") == 0 && strstr(szSrcName, "Fire"))
	{
		FireHurt(Player1_Blood);
	}

	if (strcmp(szTarName, "Player1") == 0 && strstr(szSrcName, "Smog"))
	{
		SmogHurt(Player1_Blood, m_iPropNumInTable);
	}

	// 人物碰到道具的响应
	if (m_pProp->GetPropNumByName(szTarName) && !strcmp(szSrcName, "Player1") && !m_iPropNumInTable)
	{
		m_pProp->IntoPropTable();
		m_iPropNumInTable = m_pProp->GetPropNumByName(szTarName);
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
		m_fSpeedDOWN = 0;
		m_fScreenBottom = 0;
		Player1->SetSpriteLinearVelocity(m_fSpeedLEFT + m_fSpeedRIGHT, 0);
		Player1->SetSpriteConstantForceY(0);
	}
}
