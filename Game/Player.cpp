#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
	bskl = 0;
	pfkl = 0;
	yati = 0;
	topp = 0;
	back = 0;
	comm = 0;
	pres = 0;
	stam = 0;
	money = 10000;
	energy = 0;
	burden = 0;
	name[0] = '\0';
}

CPlayer::~CPlayer()
{

}

void CPlayer::Initenergy()
{
	srand(time(0));
	energy = stam*4.5 + rand() / 32768.0;
	return;
}
BOOL CPlayer::Onchange(int code, double value)
{
	switch (code)
	{
		//-10到10均为创建人物的事件
	case -8:
		stam -= 2;
		pres -= 1;
		break;
	case -7:
		pfkl -= 3;
		pres -= 1;
		stam += 2;
		comm += 2;
		topp -= 2;
		back += 2;
		break;
	case -6:
		stam -= 4;
		bskl += 1;
		pfkl += 1;
		yati += 2;
		break;
	case -5:
		comm -= 4;
		pres += 2;
		topp += 1;
		back += 1;
		break;
	case -4:
		bskl -= 10;
		pfkl -= 10;
		yati -= 10;
		topp -= 10;
		back -= 10;
		comm -= 12;
		pres -= 8;
		stam -= 10;
		subj = 0;
		break;
	case -3:
		bskl -= 10;
		pfkl -= 10;
		yati -= 10;
		topp -= 14;
		back -= 6;
		comm -= 10;
		pres -= 10;
		stam -= 10;
		subj = 0;
		break;
	case -2:
		bskl -= 10;
		pfkl -= 10;
		yati -= 10;
		topp -= 6;
		back -= 14;
		comm -= 12;
		pres -= 10;
		stam -= 8;
		subj = 0;
		break;
	case -1:
		comm -= 3;
		break;
	case 0:
		stam += 2;
		pres += 1;
		break;
	case 1:
		comm += 3;
		break;
	case 2:
		bskl += 10;
		pfkl += 10;
		yati += 10;
		topp += 6;
		back += 14;
		comm += 12;
		pres += 10;
		stam += 8;
		subj = 1;
		break;
	case 3:
		bskl += 10;
		pfkl += 10;
		yati += 10;
		topp += 14;
		back += 6;
		comm += 10;
		pres += 10;
		stam += 10;
		subj = 2;
		break;
	case 4:
		bskl += 10;
		pfkl += 10;
		yati += 10;
		topp += 10;
		back += 10;
		comm += 12;
		pres += 8;
		stam += 10;
		subj = 3;
		break;
	case 5:
		comm += 4;
		pres -= 2;
		topp -= 1;
		back -= 1;
		break;
	case 6:
		stam += 4;
		bskl -= 1;
		pfkl -= 1;
		yati -= 2;
		break;
	case 7:
		pfkl += 3;
		pres += 1;
		stam -= 2;
		comm -= 2;
		topp += 2;
		back -= 2;
		break;
		//出差出发精力减少，压力增加
	case 11:
		if (energy > 20)
		{
			energy -= 20;
			burden += 5;
		}
		else
		{
			AfxMessageBox(_T("精力不足！无法出差！"));
			return FALSE;
		}
		break;
		//移动消耗精力
	case 12:
		if (energy > 1)
			energy -= 1;
		else
		{
			AfxMessageBox(_T("精力严重不足！请尽快就寝！"));
			return FALSE;
		}
		break;
		//睡眠增加精力，减缓压力
	case 13:
		if (energy < 50 - stam)
			energy += 50 + stam;
		else
			energy = 100;
		if (burden < 5)
			burden = 0;
		else
			burden -= 5;
		break;
	case 21:
		money += 2000;
		break;
	case 31:
		if (energy < value)
		{
			AfxMessageBox(_T("精力不足！"));
			return FALSE;
		}
		else
			energy -= value;
			
	default:
		break;
	}
	return TRUE;
}