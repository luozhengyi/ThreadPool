#ifndef __MYPOOL_H__
#define __MYPOOL_H__
//线程池管理类，作为包工头管理n个线程
#include "MyThread.h"
#include <vector>
class CMyPool
{
public:
	CMyPool(int iSize);
	~CMyPool();
public:
	unsigned GetThreadCount();	//获取当前线程数据
	bool DispatchJob(jobFuntion jobProc, WPARAM wParam, LPARAM lParam, noteCallback cb);			//分派工作
private:
	std::vector<CMyThread*> m_pThreadVec;	//管理线程(工人)
};

#endif	//__MYPOOL_H__
