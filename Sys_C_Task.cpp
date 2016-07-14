//-----------------------------------------------------------
//タスクシステムマスタcpp
//-----------------------------------------------------------

#include "Sys_C_Task.h"
c_Task::c_Task()
{
	m_pPrev		= NULL;
	m_pNext		= NULL;
	m_pStart	= NULL;
	m_pRecycle	= NULL;

	m_pPrev = m_pNext = this;
}

c_Task::c_Task(c_Task& pStart,c_Task& pRecycle)
{
	m_pPrev		= NULL;
	m_pNext		= NULL;
	m_pStart	= NULL;
	m_pRecycle	= NULL;

	m_pPrev = m_pNext = this;

	m_pStart	= &pStart;
	m_pRecycle	= &pRecycle;

}
c_Task::~c_Task()
{
	m_pPrev		= NULL;
	m_pNext		= NULL;
	m_pStart	= NULL;
	m_pRecycle	= NULL;
}
void c_Task::InitArray(void)
{
	m_pPrev = m_pNext = this;
}
void c_Task::SetList(c_Task& pStart,c_Task& pRecycle)
{
	m_pStart	= &pStart;
	m_pRecycle	= &pRecycle;
}

void c_Task::AddTask(void)
{
		//自分を入れる
	m_pNext	= m_pStart->m_pNext;
	m_pPrev	= m_pStart;

	//リスト前後の調整
	m_pStart->m_pNext->m_pPrev	= this;
	m_pStart->m_pNext			= this;
}
void c_Task::MoveOutFromActive(void)
{
	//自分をリストから取り出す
	m_pPrev->m_pNext	= m_pNext;//前オブジェクトのNext　を自分の次に指す
	m_pNext->m_pPrev	= m_pPrev;//後オブジェクトのPrev　を自分の前に指す
}

void c_Task::MoveOut(void)
{
	//自分をリストから取り出す
	m_pPrev->m_pNext	= m_pNext;//前オブジェクトのNext　を自分の次に指す
	m_pNext->m_pPrev	= m_pPrev;//後オブジェクトのPrev　を自分の前に指す

	//自分をリサイクルの中に入れる
	m_pRecycle->m_pNext->m_pPrev = this;
	m_pNext	= m_pRecycle->m_pNext;

	m_pRecycle->m_pNext = this;
	m_pPrev = m_pRecycle;
}
void c_Task::CleanArray(void)
{
	if(m_pPrev)
		m_pPrev = NULL;
	if(m_pNext)
		m_pNext = NULL;
	if(m_pStart)
		m_pStart = NULL;
	if(m_pRecycle)
		m_pRecycle = NULL;
}
void c_Task::UninitTask(void)
{
}
void c_Task::UpdateTask(void)
{
}
void c_Task::DrawTask(void)
{
}
