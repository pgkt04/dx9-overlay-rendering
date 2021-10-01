#pragma once

class cRender {
public:
#pragma region Window Properties
	uintptr_t RenderWidth;
	uintptr_t RenderHeight;
#pragma endregion

#pragma region DXD


	LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class

	void initD3D(HWND hwnd);
	void render(HWND* targetHwnd);
	void cleanD3D();



#pragma region fonts
	LPD3DXFONT Tahoma;
	void initFonts();
#pragma endregion

#pragma region drawing

	enum text_alignment
	{
		lefted,
		centered,
		righted
	};

	void Text(char *text, int x, int y, int orientation, DWORD color, ID3DXFont* pFont);


#pragma endregion 

#pragma endregion
};

extern cRender Render;