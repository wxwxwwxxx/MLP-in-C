#pragma once
#include"define.h"
#include<iostream>
using namespace std;
struct HiddenLayer
{
	float w[784];
	float b;
	float output;
	float d;
};
struct OutputLayer
{
	float w[LayerNum];
	float b;
	float output;
	float d;
};
struct MLP
{
	HiddenLayer HL[LayerNum];
	OutputLayer OL[10];
	float e[10];
	float alpha;
};
float sigmoid(float b);
float dsigmoid(float b);
void MLPInit(MLP& mlp);
int MLPTest(MLP& mlp, float image[784]);
void MLPOutput(float output[10], MLP& mlp);
int MLPOutput(MLP& mlp);
void MLPBp(MLP& mlp,int ans);
void MLPFeedForward(MLP& mlp, float image[784]);
void MLPTrainOnePic(MLP& mlp, float image[784], int ans);
void MLPUpdate(MLP& mlp, float image[784]);
void MLPTrain(MLP& mlp, ifstream& ftrainl, ifstream& ftraini);
float MLPCorrectRatio(MLP& mlp, ifstream& ftestl, ifstream& ftesti);
void MLPClear(MLP& mlp);