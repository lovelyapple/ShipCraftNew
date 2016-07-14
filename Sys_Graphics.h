//=========================================================================
//DirectX Base Graphics.h
//=========================================================================
#ifndef _SYS_GRAHPICS_H_
#define _SYS_GRAHPICS_H_

#include "Sys_Include.h"
#include "Sys_Mgr_Game.h"

HRESULT	InitDXGraphics(void);
HRESULT Render(void);
HRESULT	Init3DObject(void);
HRESULT CleanupD3DObject(void);
bool UninitDXGraphics(void);



#endif