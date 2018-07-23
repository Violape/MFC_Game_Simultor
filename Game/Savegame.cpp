#include "stdafx.h"
#include "Savegame.h"


CSavegame::CSavegame()
{
}


CSavegame::~CSavegame()
{
}

void CSavegame::LoadGame(CString filepath)
{
	CFile file;
	file.Open(filepath, CFile::modeRead | CFile::shareExclusive);
	file.Read(&Thesave, sizeof(Save));
	file.Close();
}

void CSavegame::SaveGame(CString filepath)
{
	CFile file;
	file.Open(filepath, CFile::modeWrite | CFile::modeCreate | CFile::modeNoTruncate | CFile::shareExclusive);
	file.Write(&Thesave, sizeof(Save));
	file.Close();
}
