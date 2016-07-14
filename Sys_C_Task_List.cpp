//============================================================================
//TaskList.h
//============================================================================
//-----------------------------------
//システムインクルード
#include "Sys_C_Task_List.h"
//-----------------------------------
//マスターズインクルード
//-----------------------------------
//インスタンスインクルード
c_TaskList::c_TaskList()
{
	InitTaskList();
}
c_TaskList::~c_TaskList()
{
}
void c_TaskList::InitTaskList(void)
{
	m_pActive.InitArray();
	m_pRecycle.InitArray();
}
void c_TaskList::UninitTaskList(void)
{
	//残ったものをすべてリサイクルリストの中に入れる
	for(c_Task* pActive	= m_pActive.m_pNext;
		pActive != &m_pActive;)
	{
		c_Task* Backup = pActive->m_pNext;
		pActive->MoveOut();
		pActive = Backup;
	}
	//リサイクルを一回実行
	RunRecycleList();

	//安全開放
	if(&m_pActive)
	{
		m_pActive.CleanArray();
	}
	if(&m_pRecycle)
	{
		m_pRecycle.CleanArray();
	}
}
void c_TaskList::RunActiveList(void)
{
#ifdef _DEBUG
	int nCntTask = 0;
#endif

	for(c_Task* pActive	= m_pActive.m_pNext;
		pActive != &m_pActive;)
	{
		c_Task* Backup = pActive->m_pNext;
		pActive->UpdateTask();
		pActive = Backup;
#ifdef _DEBUG
		 nCntTask++;
#endif
	}
}
void c_TaskList::RunRecycleList(void)
{
#ifdef _DEBUG
	int nCntRecycle = 0;
#endif

	for(c_Task* pActive = m_pRecycle.m_pNext;
		pActive != &m_pRecycle;)
	{

#ifdef _DEBUG
		nCntRecycle++;
#endif
		c_Task* Backup = pActive->m_pNext;
		m_pRecycle.m_pNext = pActive->m_pNext;//リサイクル自身の指すを修正
		pActive->m_pNext->m_pPrev = &m_pRecycle;

		pActive->CleanArray();
		pActive->UninitTask();
		SAFE_DELETE( pActive);
		pActive = Backup;
	}
}
void c_TaskList::DrawTaskList(void)
{
	for(c_Task* pActive = m_pActive.m_pNext;
		pActive!= &m_pActive;
		pActive	= pActive->m_pNext)
	{
		pActive->DrawTask();
	}
}


