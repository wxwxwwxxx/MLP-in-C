#include<math.h>
#include "define.h"
#include "mlp.h"
#include "time.h"
#include "mnist.h"
//#include<intrin.h>
#include<iostream>
using namespace std;
float sigmoid(float b)
{
	return (float)1.0 / ((float)1.0 + (float)exp(-b));
}
float dsigmoid(float b)
{
	return b*(1 - b); // 这里y是指经过激活函数的输出值，而不是自变量
}

//初始化MLP
void MLPInit(MLP& mlp)
{
	float randnum;
	srand(unsigned(time(0)));
	mlp.alpha =(float) Alpha;
	for (int i = 0; i < LayerNum;i++)
	{
		for (int j = 0; j < 784; j++)
		{
			randnum = (((float)rand() / (float)RAND_MAX) - 0.5f) * 2.0f;
			mlp.HL[i].w[j] = randnum/ (float)sqrt(784);
		}
		mlp.HL[i].b = 0;
		mlp.HL[i].output = 0;
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < LayerNum; j++)
		{
			randnum = (((float)rand() / (float)RAND_MAX) - 0.5f) * 2.0f;
			mlp.OL[i].w[j] = randnum/ (float)sqrt(LayerNum);
		}
		mlp.OL[i].b = 0;
		mlp.OL[i].output = 0;
	}
	MLPClear(mlp);
}
//对MLP进行一次测试
int MLPTest(MLP& mlp,float image[784])
{
	MLPFeedForward(mlp, image);
	return MLPOutput(mlp);
}
//测试MLP神经网络的正确率
float MLPCorrectRatio(MLP& mlp, ifstream& ftestl, ifstream& ftesti)
{
	int correct = 0;
	float image[784];
	int ans,t;
	for (int i = 0; i < TestNum; i++)
	{
		ReadImages(ftesti, image);
		ans = ReadLabels(ftestl);
		t = MLPTest(mlp, image);
		if (t == ans)
		{
			correct++;
		}
	}
	return (float)correct / (float)TestNum;
}
//一次前向传播
void MLPFeedForward(MLP& mlp, float image[784])
{
	float sigma;
	for (int i = 0; i < LayerNum; i++)
	{
		sigma = 0;
		for (int j = 0; j < 784; j++)
		{
			sigma += mlp.HL[i].w[j] * image[j];
		}
		sigma += mlp.HL[i].b;
		mlp.HL[i].output = sigmoid(sigma);
		
	}
	
	for (int i = 0; i < 10; i++)
	{
		sigma = 0;
		for (int j = 0; j < LayerNum; j++)
		{
			sigma += mlp.OL[i].w[j] * mlp.HL[j].output;

		}
		sigma += mlp.OL[i].b;
		mlp.OL[i].output = sigmoid(sigma);
	}
}
//对MLP神经网络进行训练（训练次数由宏定义设置）
void MLPTrain(MLP& mlp,ifstream& ftrainl,ifstream& ftraini)
{
	int ans;
	int jump;
	float image[784];
	for (int i = 0; i < TrainNum; i++)
	{
		jump = (int)rand() % Jumpnum;
		for (int d = 0; d < jump; d++)
		{
			ReadImages(ftraini, image);
			ReadLabels(ftrainl);
		}
		ReadImages(ftraini, image);
		ans=ReadLabels(ftrainl);
		MLPTrainOnePic(mlp, image, ans);
	}
}
//训练一张图片
void MLPTrainOnePic(MLP& mlp, float image[784],int ans)
{
	MLPFeedForward(mlp, image);
	MLPBp(mlp, ans);
	MLPUpdate(mlp, image);
}
//反向传播（计算差分值）
void MLPBp(MLP& mlp,int ans)
{
	float output[10],sigma;
	for (int i = 0; i < 10; i++)
	{
		output[i] = 0;
	}
	output[ans] = 1;
	//计算差分值
	for (int i = 0; i<10; i++)
	{
		mlp.e[i] = mlp.OL[i].output - output[i];
		mlp.OL[i].d= mlp.e[i] * dsigmoid(mlp.OL[i].output);
	}
	for (int j = 0; j < LayerNum; j++)
	{
		sigma = 0;
		for (int i = 0; i<10; i++)
		{
			sigma += mlp.OL[i].w[j]*mlp.OL[i].d;
		}
		mlp.HL[j].d= sigma*dsigmoid(mlp.HL[j].output);
	}
}
//清除差分值
void MLPClear(MLP& mlp)
{
	for (int i = 0; i<10; i++)
	{
		mlp.OL[i].d = 0;
	}
	for (int j = 0; j < LayerNum; j++)
	{
		mlp.HL[j].d = 0;
	}
}
//权值更新
void MLPUpdate(MLP& mlp,float image[784])
{
	for (int i = 0; i < LayerNum; i++)
	{
		for (int j = 0; j < 784; j++)
		{
			mlp.HL[i].w[j] = mlp.HL[i].w[j] -mlp.alpha*mlp.HL[i].d*image[j];
		}
		mlp.HL[i].b = mlp.HL[i].b - mlp.alpha*mlp.HL[i].d ;
	}
	for (int i = 0; i <10; i++)
	{
		for (int j = 0; j < LayerNum; j++)
		{
			mlp.OL[i].w[j] = mlp.OL[i].w[j] -mlp.alpha*mlp.OL[i].d*mlp.HL[j].output ;
		}
		mlp.OL[i].b = mlp.OL[i].b - mlp.alpha*mlp.OL[i].d ;
	}		
}
//MLP输出（将输出层写入output数组）
void MLPOutput(float output[10],MLP& mlp)
{
	for (int i = 0; i < 10; i++)
	{
		output[i]= mlp.OL[i].output;
	}
}
//MLP输出（输出神经网络运算结果）
int  MLPOutput(MLP& mlp)
{
	float max = mlp.OL[0].output;
	int maxindex = 0;
	for (int i = 0; i < 10; i++)
	{
		if (mlp.OL[i].output > max)
		{
			max = mlp.OL[i].output;
			maxindex = i;
		}
	}
	return maxindex;
}