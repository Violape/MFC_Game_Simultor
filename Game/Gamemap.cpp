#include "stdafx.h"
#include "Gamemap.h"


CGamemap::CGamemap()
{

}


CGamemap::~CGamemap()
{
	;
}

void CGamemap::Loadgamemap(CString filepath)
{
	CFile file;
	file.Open(filepath, CFile::modeRead | CFile::shareExclusive);
	file.Read(&map, sizeof(map));
	file.Close();
}

void CGamemap::Loadfrombitmap(int i, CString filepath)
{
	CImage bitmap;
	bitmap.Load(filepath);
	for (int x = 0; x < 81; x++)
		for (int y = 0; y < 81; y++)
		{
			COLORREF color = bitmap.GetPixel(x, y);
			if (color == RGB(0, 0, 0))
				map[i][x][y] = 1;
			else if (color == RGB(181, 230, 29))
				map[i][x][y] = 2;
			else if (color == RGB(34, 177, 76))
				map[i][x][y] = 3;
			else if (color == RGB(136, 0, 21))
				map[i][x][y] = 4;
			else if (color == RGB(63, 72, 204))
				map[i][x][y] = 5;
			else if (color == RGB(239, 228, 176))
				map[i][x][y] = 6;
			else if (color == RGB(153, 217, 234))
				map[i][x][y] = 7;
			else if (color == RGB(255, 255, 255))
				map[i][x][y] = 8;
			else if (color == RGB(0, 255, 0))
				map[i][x][y] = 9;
			else if (color == RGB(255, 0, 0))
				map[i][x][y] = 10;
			else if (color == RGB(255, 255, 0))
				map[i][x][y] = 11;
			else
				map[i][x][y] = 0;
		}
}

void CGamemap::Savegamemap(CString filepath)
{
	CFile file;
	file.Open(filepath, CFile::modeWrite | CFile::modeCreate | CFile::modeNoTruncate | CFile::shareExclusive);
	file.Write(&map, sizeof(map));
	file.Close();
}

int CGamemap::Getpixel(int n, int i, int j)
{
	return map[n][i][j];
}

void CGamemap::Setpixel(int n, int i, int j, int tex)
{
	map[n][i][j] = tex;
}