#ifndef _SYS_INCLUDE_
#define _SYS_INCLUDE_

//-------------------------------------------------
//SysInclude
//-------------------------------------------------
#define STRICT
#include <windows.h>		// Windowsプログラムにはこれを付ける
#include <tchar.h>			// 汎用テキスト マッピング
#include <stdio.h>			// 文字列処理で必要
#include <stdlib.h>
#include <time.h>
#include <crtdbg.h>
#include <mmsystem.h>		// 時間管理で使用
#include <d3d9.h>			// DirectX Graphics 関連のヘッダー
#include <d3dx9.h>			// DirectX Graphics 関連のヘッダー
#include <string.h>
#include <dsound.h>

#include <conio.h>

#define DIRECTINPUT_VERSION 0x0800		// DirectX8 を明示
#include <dinput.h>						// DirectInput 関連のヘッダー



//-------- ライブラリのリンク（こう記述しておけば別途リンク設定が不要となる）
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dsound.lib")

#pragma warning( disable : 4996 ) // disable deprecated warning 
#pragma warning( default : 4996 ) //無視する警告


//------------------------------------------------
//SysObjectInclude 
#include "Sys_Global_Variable.h"	//グローバル変数
#include "Sys_Macro.h"				//システムマクロ
#include "Sys_Input.h"				//システム入力
#endif