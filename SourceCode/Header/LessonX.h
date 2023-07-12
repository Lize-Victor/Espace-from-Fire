/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include "CommonClass.h"
#include "Floor.h"
#include "Prop.h"
#include "Win.h"
#include "View.h"
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

/////////////////////////////////////////////////////////////////////////////////
//
// 游戏总管类。负责处理游戏主循环、游戏初始化、结束等工作
class CGameMain
{
private:
	int m_iGameState; // 游戏状态，0：结束或者等待开始；1：初始化；2：游戏进行中

	int m_jumpFlag1;
	int m_jumpFlag2;
	CSprite *Player1;
	CSprite *Player2;
	float Player1_x1;
	float Player1_y1;
	int Player1_Blood;
	CTextSprite *m_pP1Blood;
	int m_iPropNumInTable; // 人物持有的道具编码
	int m_iPlayer1InFloorNum; // 人物所在楼层位置，范围1~9

	float player2_x2;
	float player2_y2;
	float stair_x;
	float stair_y;
	int   Player2_Blood;
	CTextSprite *m_pP2Blood;
	int m_iPlayer2InFloorNum;
	int iPosX, iPosY;
	float m_fScreenLeft;
	float m_fScreenRight;
	float m_fScreenTop;
	float m_fScreenBottom;//人物所在楼层位置，范围1-9

	float m_fSpeedUP;
	float m_fSpeedDOWN;
	float m_fSpeedLEFT;
	float m_fSpeedRIGHT;
	float m_fSpeedUp;
	float m_fSpeedDown;
	float m_fSpeedLeft;
	float m_fSpeedRight;

	prop *m_pProp; // 道具
	Win *m_pWin; // 窗户

	float m_fTime;		  // 计时器
	CTextSprite *m_pTime; // 计时器

	CSprite *m_pElevatorMap;	// 电梯地图
	CSprite *m_pElevatorPerson; // 电梯地图中的角色

	view *m_pView;

	bool m_bGameMode; // 单人： 0     双人：1
	int m_iGameSorce;
	int m_iGameLevel; // 范围1~3
	bool m_bGameResult; // 游戏状态 0：失败 1：胜利

public:
	CGameMain();  // 构造函数
	~CGameMain(); // 析构函数

	// Get方法
	int GetGameState() { return m_iGameState; }

	// Set方法
	void SetGameState(const int iState) { m_iGameState = iState; }

	// 游戏主循环等
	void GameMainLoop(float fDeltaTime);
	void GameInit();
	void GameRun(float fDeltaTime);
	void GameEnd();
	void OnMouseMove(const float fMouseX, const float fMouseY);
	void OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY);
	void OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY);
	void OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress);
	void OnKeyUp(const int iKey);
	void OnSpriteColSprite(const char *szSrcName, const char *szTarName);
	void OnSpriteColWorldLimit(const char *szName, const int iColSide);
};

/////////////////////////////////////////////////////////////////////////////////
//
extern CGameMain g_GameMain;

#endif // _LESSON_X_H_