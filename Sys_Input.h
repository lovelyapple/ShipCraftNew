//=============================================================================
//
// ���͏��� [input.h]
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "Sys_Include.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_CONTROLER		(2)				// �R���g���[���ő吔(�g�����ɉ����ĕύX���邱��)
typedef enum
{
	INPUT_KEY_UP = 0,
	INPUT_KEY_DOWN,
	INPUT_KEY_LEFT,
	INPUT_KEY_RIGHT,
	INPUT_KEY_1,
	INPUT_KEY_2,
	INPUT_KEY_3,
	INPUT_KEY_4,
	INPUT_KEY_L1,
	INPUT_KEY_L2,
	INPUT_KEY_R1,
	INPUT_KEY_R2,
	INPUT_KEY_START,
	INPUT_KEY_MAX,
}INPUT_KEY;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

bool GetKeyboardPress(int key);
bool GetKeyboardTrigger(int key);
bool GetKeyboardRepeat(int key);
bool GetKeyboardRelease(int key);

// �}�E�X�p
bool GetMouseLeftPress(void);
bool GetMouseLeftTrigger(void);
bool GetMouseRightPress(void);
bool GetMouseRightTrigger(void);
bool GetMouseCenterPress(void);
bool GetMouseCenterTrigger(void);
long GetMouseAxisX(void);
long GetMouseAxisY(void);
long GetMouseAxisZ(void);

// �W���C�X�e�B�b�N�p
bool GetJoyStickPress( int button );
bool GetJoyStickTrigger( int button );
LONG GetJoyStickPositionX();
LONG GetJoyStickPositionY();
LONG GetJoyStickPositionRX();
LONG GetJoyStickPositionRY();
LONG GetJoyStickSlider( int number );
DWORD GetJoyStickRgdwPOV( int number );


void SetUseController(bool bInput);
bool GetInputPressPOV(int nKey);
bool GetInputTriggerPOV(int nKey);
#endif