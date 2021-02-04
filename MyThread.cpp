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

	//��ӡ��Ϣ
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
		//TerminateThread(m_hThread, 0);	//�����̷߳���1��ǿ�ƽ����߳�(���ã��������ܻ�ûִ����)��
		
		//�����̷߳�ʽ2��
		m_jobProc = (jobFuntion)INVALID_HANDLE_VALUE;
		m_noteCallback = (noteCallback)INVALID_HANDLE_VALUE;
		ResumeThread(m_hThread);
		WaitForSingleObject(m_hThread, INFINITE);

		//��ӡ��Ϣ
		printf("thread %08Xd Terminated!\n", m_hThread);

		CloseHandle(m_hThread);


		
	}
}

bool CMyThread::isWorking()
{
	return this->m_bIsWorking;
}

/************************************************************************/
/* �ָ����̣߳���ȥִ��һ�����������                                   */
/************************************************************************/
void CMyThread::doJob(jobFuntion jobProc, WPARAM wParam, LPARAM lParam, noteCallback cb)
{
	this->m_jobProc = jobProc;
	this->m_wParam = wParam;
	this->m_lParam = lParam;

	this->m_noteCallback = cb;

	//��ӡ��Ϣ
	printf("thread %08Xd Start to work......wParam:%d, lParam:%d\n", m_hThread, wParam, lParam);
	ResumeThread(m_hThread);	//�ָ��̣߳���װ�޹��ɻ�

}
	
	

/************************************************************************/
/* �������̺߳���                                                       */
/************************************************************************/
DWORD WINAPI CMyThread::threadProc(LPARAM lParam)
{//ע�⾲̬�������๫����,���Բ���thisָ�����ֲ�ͬ�Ķ���
	CMyThread *pThis = (CMyThread*)lParam;
	while (true)
	{
		//������һ��Ҫ���������������ǰ�棬��Ϊ�߳��Ǵӹ���ĵط���ʼ�ָ��ģ��������˳���ˣ���������������
		//��һ���̴߳Ӵ����Ϳ�ʼ����ֱ�������������ô�ڹر��̵߳�ʱ���̴߳ӹ����λ�ûָ�(��ʱ��������Ѿ���ָ��ΪINVALID_HANDLE_VALUE)������ִ�г���
		if (pThis->m_noteCallback == 0 || pThis->m_jobProc == 0)
		{//�߳����ڹ��캯��������ģ���ʱ��û��ָ�ɾ����������Բ��ܸɻ�
			pThis->jobDone();
		}

		if (pThis->m_jobProc == INVALID_HANDLE_VALUE || pThis->m_noteCallback == INVALID_HANDLE_VALUE)
		{
			break;	//������ѭ���������߳�
		}

		//ִ�й���
		pThis->m_bIsWorking = true;
		unsigned int uiResult = pThis->m_jobProc(pThis->m_wParam, pThis->m_lParam);
		pThis->m_noteCallback(uiResult);

		//������ɣ���ӡ��Ϣ��
		printf("thread %08Xd job done\n", pThis->m_hThread);
		pThis->jobDone();
	}
	return 0;
}

void CMyThread::jobDone()
{
	m_bIsWorking = false;
	SuspendThread(m_hThread);	//�̹߳���

}
		