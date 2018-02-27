#include<iostream>
#include<stdlib.h>
#include<fstream>
#include"define.h"
#include"mnist.h"
#include"mlp.h"
#include<intrin.h>
using namespace std;

int main()
{
	
	float i;
	MLP mlp;
	MLPInit(mlp);
	ifstream ftrainl, ftraini, ftestl, ftesti;
	MnistInit(ftesti, ftestl, ftrainl, ftraini);
	for (int c = 0; c < Epoch; c++)
	{
		MnistRefresh(ftesti, ftestl, ftrainl, ftraini);
		cout << "Epoch" << c << ":";
		MLPTrain(mlp,ftrainl,ftraini);
		i = MLPCorrectRatio(mlp,ftestl,ftesti);
		cout << i << endl;
		MLPClear(mlp);
	}
	MnistClose(ftesti, ftestl, ftrainl, ftraini);
	return 0;
}
