#include "CompressionDialog.h"
#include "resource.h"
#include <windows.h>

IntelPlugin *CompressionDialog::sPlugin = nullptr;

// Registry key for storing preferences
#define REGISTRY_KEY "Software\\Intel\\TextureWorks"
#define REGISTRY_FORMAT_VALUE "CompressionFormat"
#define REGISTRY_REMEMBER_VALUE "RememberFormat"

int CompressionDialog::DoModal(IntelPlugin *plugin)
{
	sPlugin = plugin;
	
	// Load last used format from registry (but always show dialog)
	HKEY hKey;
	if (RegOpenKeyExA(HKEY_CURRENT_USER, REGISTRY_KEY, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		DWORD savedFormat = 0;
		DWORD dataSize = sizeof(DWORD);
		if (RegQueryValueExA(hKey, REGISTRY_FORMAT_VALUE, NULL, NULL, (LPBYTE)&savedFormat, &dataSize) == ERROR_SUCCESS)
		{
			plugin->ps.data->encoding_g = (DXGI_FORMAT)savedFormat;
		}
		RegCloseKey(hKey);
	}
	
	return (int)DialogBox((HINSTANCE)GetDLLInstance(), MAKEINTRESOURCE(IDD_COMPRESSIONDIALOG), (HWND)((PlatformData*)plugin->ps.formatRecord->platformData)->hwnd, DialogProc);
}

INT_PTR CALLBACK CompressionDialog::DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		// Center the dialog on screen
		RECT rc;
		GetWindowRect(hDlg, &rc);
		int dialogWidth = rc.right - rc.left;
		int dialogHeight = rc.bottom - rc.top;
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);
		int x = (screenWidth - dialogWidth) / 2;
		int y = (screenHeight - dialogHeight) / 2;
		SetWindowPos(hDlg, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		
		// Set default to DXT5
		if (sPlugin->ps.data->encoding_g == DXGI_FORMAT_BC3_UNORM || 
		    sPlugin->ps.data->encoding_g == DXGI_FORMAT_BC3_UNORM_SRGB)
		{
			CheckDlgButton(hDlg, IDC_RADIO_DXT5, BST_CHECKED);
		}
		else if (sPlugin->ps.data->encoding_g == DXGI_FORMAT_BC1_UNORM || 
		         sPlugin->ps.data->encoding_g == DXGI_FORMAT_BC1_UNORM_SRGB)
		{
			CheckDlgButton(hDlg, IDC_RADIO_DXT1, BST_CHECKED);
		}
		else if (sPlugin->ps.data->encoding_g == DXGI_FORMAT_R8G8B8A8_UNORM)
		{
			CheckDlgButton(hDlg, IDC_RADIO_BGRA8, BST_CHECKED);
		}
		else
		{
			// Default to DXT5
			CheckDlgButton(hDlg, IDC_RADIO_DXT5, BST_CHECKED);
		}
		return TRUE;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			// Get selected compression format
			DXGI_FORMAT selectedFormat;
			if (IsDlgButtonChecked(hDlg, IDC_RADIO_DXT5) == BST_CHECKED)
			{
				selectedFormat = DXGI_FORMAT_BC3_UNORM;
			}
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO_DXT1) == BST_CHECKED)
			{
				selectedFormat = DXGI_FORMAT_BC1_UNORM;
			}
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO_BGRA8) == BST_CHECKED)
			{
				selectedFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
			}
			else
			{
				selectedFormat = DXGI_FORMAT_BC3_UNORM; // Default
			}
			
			sPlugin->ps.data->encoding_g = selectedFormat;
			
			// Always save the last used format to registry (for next time)
			HKEY hKey;
			if (RegCreateKeyExA(HKEY_CURRENT_USER, REGISTRY_KEY, 0, NULL, 0, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS)
			{
				DWORD format = (DWORD)selectedFormat;
				RegSetValueExA(hKey, REGISTRY_FORMAT_VALUE, 0, REG_DWORD, (LPBYTE)&format, sizeof(DWORD));
				RegCloseKey(hKey);
			}
			
			EndDialog(hDlg, IDOK);
			return TRUE;
		}
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

