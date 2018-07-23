#pragma once
class CGamemap
{
public:
	CGamemap();
	~CGamemap();
	void Loadgamemap(CString filepath);
	void Loadfrombitmap(int i, CString filepath);
	void Savegamemap(CString filepath);
	int Getpixel(int n, int i, int j);
	void Setpixel(int n, int i, int j, int tex);

private:
	int map[6][81][81];
};

