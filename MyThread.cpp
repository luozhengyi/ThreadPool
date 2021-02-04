#include "stdafx.h"
#include "MyThread.h"
#include <iostream>

CMyThread::CMyThread()
{
	m_bIsWorking = false;
	m_jobProc = 0;
	m_noteCallback = 0;
	m_wParam = 0;
	m_lParam = 0;
	m_hThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)threadProc,this,0,0);

	//打印消息
	std::cout << "thread ";
	std::cout << "0X";
	std::cout.fill('0');
	std::cout.width(8);
	std::cout << m_hThread;
	std::cout << " successfully create!" << std::endl;
}


CMyThread::~CMyThread()
{
	if (m_hThread != INVALID_HANDLE_VALUE)
	{
		//TerminateThread(m_hThread, 0);	//结束线程方法1：强制结束线程(不好，工作可能还没执行完)，
		
		//结束线程方式2：
		m_jobProc = (jobFuntion)INVALID_HANDLE_VALUE;
		m_noteCallback = (noteCallback)INVALID_HANDLE_VALUE;
		ResumeThread(m_hThread);
		WaitForSingleObject(m_hThread, INFINITE);

		//打印消息
		printf("thread %08Xd Terminated!\n", m_hThread);

		CloseHandle(m_hThread);


		
	}
}

bool CMyThread::isWorking()
{
	return this->m_bIsWorking;
}

/************************************************************************/
/* 恢复子线程，并去执行一个具体的任务                                   */
/************************************************************************/
void CMyThread::doJob(jobFuntion jobProc, WPARAM wParam, LPARAM lParam, noteCallback cb)
{
	this->m_jobProc = jobProc;
	this->m_wParam = wParam;
	this->m_lParam = lParam;

	this->m_noteCallback = cb;

	//打印消息
	printf("thread %08Xd Start to work......wParam:%d, lParam:%d\n", m_hThread, wParam, lParam);
	ResumeThread(m_hThread);	//恢复线程，叫装修工干活

}
	
	

/************************************************************************/
/* 真正的线程函数                                                       */
/************************************************************************/
DWORD WINAPI CMyThread::threadProc(LPARAM lParam)
{//注意静态函数是类公共的,所以产地this指针区分不同的对象
	CMyThread *pThis = (CMyThread*)lParam;
	while (true)
	{
		//该条件一定要放在下面的条件的前面，因为线程是从挂起的地方开始恢复的；如果二者顺序反了，会出现如下情况：
		//当一个线程从创建就开始挂起，直到程序结束，那么在关闭线程的时该线程从挂起的位置恢复(此时函数句柄已经被指定为INVALID_HANDLE_VALUE)，继续执行出错
		if (pThis->m_noteCallback == 0 || pThis->m_jobProc == 0)
		{//线程是在构造函数中申请的，暂时还没有指派具体任务，所以不能干活
			pThis->jobDone();
		}

		if (pThis->m_jobProc == INVALID_HANDLE_VALUE || pThis->m_noteCallback == INVALID_HANDLE_VALUE)
		{
			break;	//跳出死循环，结束线程
		}

		//执行工作
		pThis->m_bIsWorking = true;
		unsigned int uiResult = pThis->m_jobProc(pThis->m_wParam, pThis->m_lParam);
		pThis->m_noteCallback(uiResult);

		//工作完成；打印消息；
		printf("thread %08Xd job done\n", pThis->m_hThread);
		pThis->jobDone();
	}
	return 0;
}

void CMyThread::jobDone()
{
	m_bIsWorking = false;
	SuspendThread(m_hThread);	//线程挂起

}
		