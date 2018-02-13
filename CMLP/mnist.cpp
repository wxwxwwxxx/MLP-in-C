#include<iostream>
#include<fstream>
#include"define.h"
#include"mnist.h"
using namespace std;
//读取测试图片
int ReadImages(ifstream& f1,float Pic[784])
{
	unsigned char b;
	//读取图片信息
	for (int i = 0; i < 784; i++)
	{
		f1.read((char*)(&b), 1);
		Pic[i] = (float)b/ (float)255.0;
	}
	return 0;
}
void SaveTrainImages(ifstream& f1)
{
	unsigned char b;
	ofstream fs;
	char a[] = "trainimage0.cpp";
	for (int t = 0; t < 1; t++)
	{
		a[10]++;
		fs.open(a, ios::out);
		fs << "int trainimage"<<t+1<<"[60000][784]=" << endl;
		fs << "{";
		//读取图片信息
		for (int s = 0; s < 60000; s++)
		{
			cout << s << endl;
			fs << "{";
			for (int i = 0; i < 784; i++)
			{
				f1.read((char*)(&b), 1);
				fs << (int)b;
				//			if (i != 783)
				fs << ',';
			}
			fs << "}," << endl;
		}
		fs << "};";
		fs.close();
	}
}
void SaveTestImages(ifstream& f1)
{
	unsigned char b;
	ofstream fs;
	char a[] = "testimage.cpp";
	fs.open(a, ios::out);
	fs << "int testimage[10000][784]=" << endl;
	fs << "{";
	//读取图片信息
	for (int s = 0; s < 10000; s++)
	{
		cout << s << endl;
		fs << "{";
		for (int i = 0; i < 784; i++)
		{
			f1.read((char*)(&b), 1);
			fs << (int)b;
				//			if (i != 783)
			fs << ',';
		}
		fs << "}," << endl;
	}
	fs << "};";
	fs.close();
}
//读取训练标签
int ReadLabels(ifstream& f1)
{
	unsigned char b;
	//读取图片信息
	f1.read((char*)(&b), 1);
	return (int)b;
}
void SaveTrainLabels(ifstream& f1)
{
	unsigned char b;
	//读取图片信息
	ofstream fs;
	char a[] = "trainlabel.cpp";
	fs.open(a, ios::out);
	fs << "int trainlabel[60000]={" << endl;
		//读取图片信息
	for (int s = 0; s < 60000; s++)
	{
		cout << s << endl;
		f1.read((char*)(&b), 1);
		fs << (int)b;
		fs << ',';
	}
	fs << "};" << endl;
	fs.close();
}
void SaveTestLabels(ifstream& f1)
{
	unsigned char b;
	//读取图片信息
	ofstream fs;
	char a[] = "testlabel.cpp";
	fs.open(a, ios::out);
	fs << "int testlabel[10000]={" << endl;
	//读取图片信息
	for (int s = 0; s < 10000; s++)
	{
		cout << s << endl;
		f1.read((char*)(&b), 1);
		fs << (int)b;
		fs << ',';
	}
	fs << "};" << endl;
	fs.close();
}
int MnistInit(ifstream& ftesti, ifstream& ftestl, ifstream& ftrainl, ifstream& ftraini)
{
	ftestl.open(testlabels, ios::binary);
	ftesti.open(testimages, ios::binary);
	ftrainl.open(trainlabels, ios::binary);
	ftraini.open(trainimages, ios::binary);
	return 0;
}
int Mnistclose(ifstream& ftesti, ifstream& ftestl, ifstream& ftrainl, ifstream& ftraini)
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

/*
int ReadTrainImages(int No, float Pic[784])
{
	//读取图片信息
	if (No <= 9999)
	{
		for (int i = 0; i < 784; i++)
		{
			Pic[i] = (float)trainimage1[No][i]/ (float)255.0;
		}
	}
	else if(No<=19999)
	{
		No -= 10000;
		for (int i = 0; i < 784; i++)
		{
			Pic[i] = (float)trainimage2[No][i] / (float)255.0;
		}
	}
	else if (No <= 29999)
	{
		No -= 20000;
		for (int i = 0; i < 784; i++)
		{
			Pic[i] = (float)trainimage3[No][i] / (float)255.0;
		}
	}
	else if (No <= 39999)
	{
		No -= 30000;
		for (int i = 0; i < 784; i++)
		{
			Pic[i] = (float)trainimage4[No][i] / (float)255.0;
		}
	}
	else if (No <= 49999)
	{
		No -= 40000;
		for (int i = 0; i < 784; i++)
		{
			Pic[i] = (float)trainimage5[No][i] / (float)255.0;
		}
	}
	else if (No <= 59999)
	{
		No -= 50000;
		for (int i = 0; i < 784; i++)
		{
			Pic[i] = (float)trainimage6[No][i] / (float)255.0;
		}
	}
	return 0;
}
int ReadTestImages(int No, float Pic[784])
{
	//读取图片信息
	for (int i = 0; i < 784; i++)
	{
		Pic[i] = (float)testimage[No][i] / (float)255.0;
	}
	return 0;
}
int ReadTrainLabel(int No)
{
	//读取图片信息
	
	return trainlabel[No];
}
int ReadTestLabel(int No)
{
	//读取图片信息
	return testlabel[No];
}*/