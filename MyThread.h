#ifndef __MYTHREAD_H__
#define __MYTHREAD_H__
#include "windows.h"
//装修工、线程类，每个对象实例化一个线程
//1.不能线程函数运行完成后退出
//2.线程运行完后占用的资源要少
//3.线程类对象需要可调整执行的任务
//4.线程已经在干活的时候，不要在指派别的任务

//线程要做的事情
typedef unsigned int(*jobFuntion)(WPARAM wParam, LPARAM lParam);
//线程完成后的通知回调函数
typedef void(*noteCallback)(unsigned int pResult);

class CMyThread
{
public:
	CMyThread();
	~CMyThread();
public:
	bool isWorking();	//判断线程是否在工作
	void doJob(jobFuntion jobProc,WPARAM wParam,LPARAM lParam,noteCallback cb);		//去帮我干点活 cb：表示callback
	void jobDone();		//线程一次的任务做完了
private:
	bool m_bIsWorking;
	jobFuntion m_jobProc;
	noteCallback m_noteCallback;
	WPARAM m_wParam;
	LPARAM m_lParam;
	HANDLE m_hThread;
	static DWORD WINAPI threadProc(LPARAM lParam);	//真正的线程函数
};
#endif	//__MYTHREAD_H__
