#include "stdafx.h"
#include "MyPool.h"


CMyPool::CMyPool(int iSize)
{
	for (int i = 0; i < iSize; ++i)
	{
		CMyThread *pNewThread = new CMyThread();
		m_pThreadVec.push_back(pNewThread);
	}
}


CMyPool::~CMyPool()
{
	//�ͷ������߳�
	std::vector<CMyThread*>::iterator it = m_pThreadVec.begin();
	for (; it != m_pThreadVec.end();)
	{
		CMyThread *pThread = *it++;
		delete pThread;
	}
}

unsigned CMyPool::GetThreadCount()
{
	return m_pThreadVec.size();
}

bool CMyPool::DispatchJob(jobFuntion jobProc, WPARAM wParam, LPARAM lParam, noteCallback cb)
{
	std::vector<CMyThread*>::iterator it = m_pThreadVec.begin();
	for (; it != m_pThreadVec.end(); ++it)
	{
		if (!(*it)->isWorking())
		{
			(*it)->doJob(jobProc, wParam, lParam, cb);
			return true;
		}
	}

	//������е��̶߳���æ������һ���µ��߳�
	CMyThread* pThread = new CMyThread();
	m_pThreadVec.push_back(pThread);
	pThread->doJob(jobProc, wParam, lParam, cb);
	return true;
}