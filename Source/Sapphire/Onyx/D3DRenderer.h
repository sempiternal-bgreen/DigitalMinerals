#ifndef D3D9RENDERER_H_
#define D3D9RENDERER_H_

#include <Windows.h>

HRESULT InitializeD3DRender( HWND hWnd );
void UpdateD3DRender();
void RenderD3DRender();
void ShutDownD3DRender();
void ResetD3DRender();

void ToggleVSync( bool toggle );

#endif
