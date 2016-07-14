#ifndef _SYS_INCLUDE_
#define _SYS_INCLUDE_

//-------------------------------------------------
//SysInclude
//-------------------------------------------------
#define STRICT
#include <windows.h>		// Windows�v���O�����ɂ͂����t����
#include <tchar.h>			// �ėp�e�L�X�g �}�b�s���O
#include <stdio.h>			// �����񏈗��ŕK�v
#include <stdlib.h>
#include <time.h>
#include <crtdbg.h>
#include <mmsystem.h>		// ���ԊǗ��Ŏg�p
#include <d3d9.h>			// DirectX Graphics �֘A�̃w�b�_�[
#include <d3dx9.h>			// DirectX Graphics �֘A�̃w�b�_�[
#include <string.h>
#include <dsound.h>

#include <conio.h>

#define DIRECTINPUT_VERSION 0x0800		// DirectX8 �𖾎�
#include <dinput.h>						// DirectInput �֘A�̃w�b�_�[



//-------- ���C�u�����̃����N�i�����L�q���Ă����Εʓr�����N�ݒ肪�s�v�ƂȂ�j
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dsound.lib")

#pragma warning( disable : 4996 ) // disable deprecated warning 
#pragma warning( default : 4996 ) //��������x��


//------------------------------------------------
//SysObjectInclude 
#include "Sys_Global_Variable.h"	//�O���[�o���ϐ�
#include "Sys_Macro.h"				//�V�X�e���}�N��
#include "Sys_Input.h"				//�V�X�e������
#endif