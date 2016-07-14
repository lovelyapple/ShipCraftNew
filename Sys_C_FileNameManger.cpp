//-----------------------------------------------------------
//SYS_CLASS_FILE_NAME_MANANGER
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
#include "Sys_C_FileNameManger.h"

const char* FileNameBLock[] = {
	"data/Model/Block/Block_Normal.x",
	"data/Model/Block/Block_Metal.x",
	"data/Model/Block/Block_Engine.x",
	"data/Model/Block/Block_Wood.x",
	"data/Model/Block/Block_Active.x",
};
const char* FileNameEditorModel[] = {
	"data/Model/Stationary/CraftTable.x",
};
const char* FileNameBLockMenu[] = {
	"data/Model/Block/Block_Normal.bmp",
	"data/Model/Block/Block_Metal.bmp",
	"data/Model/Block/Block_Engine.bmp",
	"data/Model/Block/Block_Wood.bmp",
};
LPCSTR c_FileNameMgr::GetFileName(int FileType, int NameNum)
{
	LPCSTR FileName ;
	switch(FileType)
	{
	case FILE_TYPE_BLOCK:
		FileName =  FileNameBLock[NameNum];
		break;
	case FILE_TYPE_EDITOR:
		FileName = FileNameEditorModel[NameNum];
		break;
	case FILE_TYPE_BLOCK_MENU:
		FileName = FileNameBLockMenu[NameNum];
		break;
	}
	return FileName;
}
//-----------------------------------------------------------
//End of File
//-----------------------------------------------------------