# Dll项目创建与调用

## 创建
1.新建win32 dll项目,命名为"MyDLL"，在分别添加三个文件
testdll.h
```
#ifndef TestDll_H_
#define TestDll_H_
#ifdef MYLIBDLL
#define MYLIBDLL extern "C" _declspec(dllimport) 
#else
#define MYLIBDLL extern "C" _declspec(dllexport) 
#endif
MYLIBDLL int Add(int plus1, int plus2);
//You can also write like this:
//extern "C" {
//_declspec(dllexport) int Add(int plus1, int plus2);
//};
#endif
```
testdll.cpp
```
#include "stdafx.h"
#include "testdll.h"
#include <iostream>
using namespace std;
int Add(int plus1, int plus2)
{
int add_result = plus1 + plus2;
return add_result;
}
```
mydll.def (模块定义文件)
```
LIBRARY "MyDLL"
EXPORTS
Add @1
```
MyDLL.cpp会自动生成
2. 编译并生成

## 显示调用
新建一个控制台项目,将MyDLL.dll拷贝到当前目录下,在main函数里加如下代码：
```
	typedef int(*PF_ADD)(int a,int b);
	HINSTANCE hDLL;
	hDLL = LoadLibrary("MyDLL.dll");//加载动态链接库MyDll.dll文件；

	PF_ADD Add = (PF_ADD)GetProcAddress(hDLL,"Add");

	int a;
	a = Add(5 , 8);

	std::cout<<"比较的结果为"<<a;
	FreeLibrary(hDLL);//卸载MyDll.dll文件；
```
如果有报错，可能是：
(1).unicode字节变为多字节
(2)."配置属性"-"调试"-"环境"里填入dll路径，默认是exe路径可不填。
