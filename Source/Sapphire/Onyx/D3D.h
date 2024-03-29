#ifndef D3D9_H_
#define D3D9_H

#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

class D3D
{
public:
	IDirect3D9				*d3dObject;
	IDirect3DDevice9		*d3dDevice;
	D3DPRESENT_PARAMETERS	d3dPresentParameters;

	bool					m_bVSync;
	float					m_fScreenWidth;
	float					m_fScreenHeight;

	HRESULT InitializeD3D( HWND hWnd );
	void ShutDownD3D();
	void ResetD3D();

	void SetScreenWidth( float width )	{ m_fScreenWidth = width; }
	void SetScreenHeight( float height ){ m_fScreenHeight = height; }

	float GetScreenWidth( void )		{ return m_fScreenWidth; }
	float GetScreenHeight( void )		{ return m_fScreenHeight; }
};

#endif
