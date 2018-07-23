#pragma once
class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	double bskl;
	double pfkl;
	double yati;
	double topp;
	double back;
	double comm;
	double pres;
	double stam;
	int loca;
	int subj;
	int money = 10000;
	double energy;
	double burden = 0;
	char name[100];
	void Initenergy();
	BOOL Onchange(int code, double value = 0);
};

