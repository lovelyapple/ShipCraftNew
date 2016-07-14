//-----------------------------------------------------------
//タスクシステムマスタh
//-----------------------------------------------------------
#ifndef _TASK_H_
#define _TASK_H_
//-----------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_Macro.h"
//-----------------------------------
//マスターズインクルード
class c_Task
{
public:	
	c_Task();
	c_Task(c_Task& pStart,c_Task& pRecycle);		//コンストラクタ
	~c_Task();										//デストラクタ
	void SetList(c_Task& pStart,c_Task& pRecycle);	//リストをセットする
	void InitArray(void);							//ポインタを初期化する
	void AddTask(void);								//タスクをアクティブリストに挿入
	void CleanArray(void);							//内部の指しアドレスをクリアする
	void MoveOutFromActive(void);					//アクティブリストから根ケル
	void MoveOut(void);								//アクティブリストからリサイクルリストへ移動

	virtual void UpdateTask();
	virtual void DrawTask();	
	virtual void UninitTask();	


	c_Task* m_pPrev;		//前のクラスへのポインタ
	c_Task* m_pNext;		//後のクラスへのポインタ
	c_Task* m_pStart;		//アクティブへのポインタ
	c_Task* m_pRecycle;		//リサイクルへのポインタ

private:
protected:
};
#endif

