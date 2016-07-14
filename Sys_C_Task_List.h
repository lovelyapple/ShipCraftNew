//-----------------------------------------------------------
//タスクリストh
//-----------------------------------------------------------
#ifndef _TASK_LIST_H
#define _TASK_LIST_H
//-----------------------------------
//システムインクルード
#include "Sys_Include.h"
//-----------------------------------
//マスターズインクルード
#include "Sys_C_Task.h"

class c_TaskList
{
public:
	c_TaskList();
	~c_TaskList();
	void	InitTaskList(void);
	void	UninitTaskList(void);
	void	RunActiveList(void);
	void	RunRecycleList(void);
	void	DrawTaskList(void);
	c_Task	m_pActive;
	c_Task	m_pRecycle;
private:

};

#endif