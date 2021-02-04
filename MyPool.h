#ifndef __MYPOOL_H__
#define __MYPOOL_H__
//�̳߳ع����࣬��Ϊ����ͷ����n���߳�
#include "MyThread.h"
#include <vector>
class CMyPool
{
public:
	CMyPool(int iSize);
	~CMyPool();
public:
	unsigned GetThreadCount();	//��ȡ��ǰ�߳�����
	bool DispatchJob(jobFuntion jobProc, WPARAM wParam, LPARAM lParam, noteCallback cb);			//���ɹ���
private:
	std::vector<CMyThread*> m_pThreadVec;	//�����߳�(����)
};

#endif	//__MYPOOL_H__
