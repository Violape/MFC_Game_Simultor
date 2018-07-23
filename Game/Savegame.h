#pragma once
#include "Player.h"
#include "Gamemap.h"
struct Save
{
	int month;
	int day;
	int dayofweek;
	int mapnow;
	CPlayer Theplayer;
	CGamemap Themap;
	double students[10][5];
	int taskstat[5];
};
class CSavegame
{
public:
	CSavegame();
	~CSavegame();
	Save Thesave;
	void SaveGame(CString filepath);
	void LoadGame(CString filepath);
};

