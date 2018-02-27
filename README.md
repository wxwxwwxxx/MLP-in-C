# MLP-in-C
使用C语言编写的简单多层感知器，使用MNIST作为测试集和验证集。

**编译工具**：Visual Studio

**项目构建方法**：运行项目目录下的CMLP.sln即可

**代码目录**：MLP-in-C/CMLP/

**代码说明**：

main.cpp：主函数

define.h：宏定义文件，定义了神经网络需要的超参数
	
mlp.cpp/mlp.h：MLP神经网络具体实现
	
mnist.cpp/mnist.h：MNIST数据集的相关函数

test-images.idx3-ubyte：MNIST数据集，测试集图片

test-labels.idx1-ubyte：MNIST数据集，测试集标签

train-images.idx3-ubyte：MNIST数据集，训练集图片

train-labels.idx1-ubyte	：MNIST数据集，训练集标签