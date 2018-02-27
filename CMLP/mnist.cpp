#include<iostream>
#include<fstream>
#include"define.h"
#include"mnist.h"
using namespace std;
//∂¡»°≤‚ ‘Õº∆¨

int ReadImages(ifstream& f1,float Pic[784])
{
	unsigned char b;
	//∂¡»°Õº∆¨–≈œ¢
	for (int i = 0; i < 784; i++)
	{
		f1.read((char*)(&b), 1);
		Pic[i] = (float)b/ (float)255.0;
	}
	return 0;
}
//∂¡»°—µ¡∑±Í«©
int ReadLabels(ifstream& f1)
{
	unsigned char b;
	//∂¡»°Õº∆¨–≈œ¢
	f1.read((char*)(&b), 1);
	return (int)b;
}

int MnistInit(ifstream& ftesti, ifstream& ftestl, ifstream& ftrainl, ifstream& ftraini)
{
	ftestl.open(testlabels, ios::binary);
	ftesti.open(testimages, ios::binary);
	ftrainl.open(trainlabels, ios::binary);
	ftraini.open(trainimages, ios::binary);
	return 0;
}
int MnistClose(ifstream& ftesti, ifstream& ftestl, ifstream& ftrainl, ifstream& ftraini)
{
	ftestl.close();
	ftesti.close();
	ftrainl.close();
	ftraini.close();
	return 0;
}
int MnistRefresh(ifstream& ftesti, ifstream& ftestl, ifstream& ftrainl, ifstream& ftraini)
{
	ftesti.seekg(16, ios::beg);
	ftestl.seekg(8, ios::beg);
	ftrainl.seekg(8, ios::beg);
	ftraini.seekg(16, ios::beg);
	return 0;
}
