// ThreadPool.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "windows.h"
#include "MyPool.h"
#include <iostream>
#include "stdlib.h"
#include "stdio.h"
//�߳�Ҫ��������
//pedef unsigned int(*jobFuntion)(WPARAM wParam, LPARAM lParam);
//�߳���ɺ��֪ͨ�ص�����
//pedef void(*noteCallback)(unsigned int pResult);

unsigned int job(WPARAM wParam, LPARAM lParam)
{
	std::cout<<"iob doing: "<<wParam <<" + " << lParam <<" =?"<<std::endl;
	//Sleep(1000);	//˯��1000ms�������߳�ִ�е�ʱ��
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

	while (true)	//ÿ��һ�ΰ�����Ͷ��һ������
	{
		char cmd = getchar();
		if (cmd == 'q' || cmd == 'q')
			break;
		printf("Thread Pool Size: %u\n", pMyPool->GetThreadCount());
		pMyPool->DispatchJob(job, 10, 20, cb);

	}

	//�ͷ���Դ
	delete pMyPool;	//������ֱ���ͷ��ڴ棬�ᵼ���̵߳��ڴ����
	printf("process exit...\n");
	return 0;
}

