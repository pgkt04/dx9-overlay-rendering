#include "Header.h"

cRender Render;

void cRender::Text(char *text, int x, int y, int orientation, DWORD color, ID3DXFont* pFont)
{
	RECT rect = { x, y, x + 120, y + 16 };

	switch (orientation)
	{
	case lefted:
		pFont->DrawTextA(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, color);
		break;
	case centered:
		pFont->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, color);
		break;
	case righted:
		pFont->DrawTextA(NULL, text, -1, &rect, DT_RIGHT | DT_NOCLIP, color);
		break;
	}
}


void cRender::initFonts() {

	IDirect3DDevice9* pDevice;
	pDevice = d3ddev;

	D3DXCreateFont(pDevice, 20, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "Tahoma", &Tahoma);
}

void cRender::initD3D(HWND hwnd)
{
	// create the Direct3D interface
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	// create a struct to hold various device information
	D3DPRESENT_PARAMETERS d3dpp;    
	// clear out the struct for use
	ZeroMemory(&d3dpp, sizeof(d3dpp));   
	// program windowed, not fullscreen
	d3dpp.Windowed = TRUE;    
	// discard old frames
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	// set the window to be used by Direct3D
	d3dpp.hDeviceWindow = hwnd;


	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);

	// Initialise all fonts to be used.
	initFonts();
}

void cRender::render(HWND* targetHwnd) {
	d3ddev->BeginScene();    // begins the 3D scene
	// clear the window alpha
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	IDirect3DDevice9* pDevice;
	pDevice = d3ddev;

	D3DVIEWPORT9 screen;

	// Get the screen
	pDevice->GetViewport(&screen);

	if (Tahoma) {
		Tahoma->OnLostDevice();
	}

	if (*targetHwnd == GetForegroundWindow())
	{
		// Call Rendering here.
		Text((char*)"kitto d3d overlay", 10, +50, lefted, D3DCOLOR_RGBA(255, 0, 0, 255), Tahoma);

	}


	d3ddev->EndScene();    // ends the 3D scene
	d3ddev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
}

void cRender::cleanD3D()
{
	d3ddev->Release();    // close and release the 3D device
	d3d->Release();    // close and release Direct3D
}
