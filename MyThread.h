#ifndef __MYTHREAD_H__
#define __MYTHREAD_H__
#include "windows.h"
//װ�޹����߳��࣬ÿ������ʵ����һ���߳�
//1.�����̺߳���������ɺ��˳�
//2.�߳��������ռ�õ���ԴҪ��
//3.�߳��������Ҫ�ɵ���ִ�е�����
//4.�߳��Ѿ��ڸɻ��ʱ�򣬲�Ҫ��ָ�ɱ������

//�߳�Ҫ��������
typedef unsigned int(*jobFuntion)(WPARAM wParam, LPARAM lParam);
//�߳���ɺ��֪ͨ�ص�����
typedef void(*noteCallback)(unsigned int pResult);

class CMyThread
{
public:
	CMyThread();
	~CMyThread();
public:
	bool isWorking();	//�ж��߳��Ƿ��ڹ���
	void doJob(jobFuntion jobProc,WPARAM wParam,LPARAM lParam,noteCallback cb);		//ȥ���Ҹɵ�� cb����ʾcallback
	void jobDone();		//�߳�һ�ε�����������
private:
	bool m_bIsWorking;
	jobFuntion m_jobProc;
	noteCallback m_noteCallback;
	WPARAM m_wParam;
	LPARAM m_lParam;
	HANDLE m_hThread;
	static DWORD WINAPI threadProc(LPARAM lParam);	//�������̺߳���
};
#endif	//__MYTHREAD_H__
