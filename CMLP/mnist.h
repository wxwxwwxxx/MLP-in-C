#pragma once
#include"define.h"
#include<iostream>
#include<fstream>
using namespace std;
int ReadImages(ifstream&, float c[784]);
int ReadLabels(ifstream&);
int MnistInit(ifstream& ftesti, ifstream& ftestl, ifstream& ftrainl, ifstream& ftraini);
int MnistClose(ifstream& ftesti, ifstream& ftestl, ifstream& ftrainl, ifstream& ftraini);
int MnistRefresh(ifstream& ftesti, ifstream& ftestl, ifstream& ftrainl, ifstream& ftraini);
void SaveTrainImages(ifstream& f1);
void SaveTestImages(ifstream& f1);
void SaveTrainLabels(ifstream& f1);
void SaveTestLabels(ifstream& f1);