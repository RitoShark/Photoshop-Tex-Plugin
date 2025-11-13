#pragma once

#include "IntelPlugin.h"

class CompressionDialog
{
public:
	static int DoModal(IntelPlugin *plugin);
	
private:
	static INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static IntelPlugin *sPlugin;
};

