// ThreadPool.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "MyPool.h"
#include <iostream>
#include "stdlib.h"
#include "stdio.h"
//线程要做的事情
//pedef unsigned int(*jobFuntion)(WPARAM wParam, LPARAM lParam);
//线程完成后的通知回调函数
//pedef void(*noteCallback)(unsigned int pResult);

unsigned int job(WPARAM wParam, LPARAM lParam)
{
	std::cout<<"iob doing: "<<wParam <<" + " << lParam <<" =?"<<std::endl;
	//Sleep(1000);	//睡眠1000ms，增长线程执行的时间
	return wParam + lParam;
}

void cb(unsigned int pResult)
{
	std::cout << "job result: " << pResult << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	CMyPool* pMyPool = new CMyPool(2);
	//MyPool.DispatchJob(job, 10, 20, cb);

	while (true)	//每按一次按键就投递一个任务
	{
		char cmd = getchar();
		if (cmd == 'q' || cmd == 'q')
			break;
		printf("Thread Pool Size: %u\n", pMyPool->GetThreadCount());
		pMyPool->DispatchJob(job, 10, 20, cb);

	}

	//释放资源
	delete pMyPool;	//不能用直接释放内存，会导致线程的内存崩溃
	printf("process exit...\n");
	return 0;
}

