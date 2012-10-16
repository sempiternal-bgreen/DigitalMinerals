#include "D3DRenderer.h"

#include "D3D.h"
#include "Shape.h"
#include "Camera.h"
#include "Timer.h"
#include "PostProcess.h"

D3D		d3d;
Camera  camera;
Shape	shape;

HRESULT InitializeD3DRender( HWND hWnd )
{
	d3d.InitializeD3D( hWnd );
	PostProcess::GetInstance()->Initialize( d3d.d3dDevice );
	camera.Initialize();
	shape.InitializeShape( d3d.d3dDevice );

	return S_OK;
}
void UpdateD3DRender()
{
	Timer::GetInstance()->Update();
	if( PostProcess::GetInstance()->m_bPostProcess )	{ PostProcess::GetInstance()->Update(); }
	shape.UpdateShape( Timer::GetInstance()->GetDeltaTime() );
	camera.Update( Timer::GetInstance()->GetDeltaTime() );
}
void RenderD3DRender()
{
	if( NULL == d3d.d3dDevice ) { return; }

	d3d.d3dDevice->Clear( 0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0,0,0 ), 1.0f, 0 );

	if( PostProcess::GetInstance()->m_bPostProcess )	{ PostProcess::GetInstance()->BeginPostProcess( d3d.d3dDevice ); }
	d3d.d3dDevice->BeginScene();

	shape.RenderShape( d3d.d3dDevice, camera.CameraMatrix, camera.ProjectionMatrix );

	d3d.d3dDevice->EndScene();
	if( PostProcess::GetInstance()->m_bPostProcess )	{ PostProcess::GetInstance()->EndPostProcess( d3d.d3dDevice ); }
	
	d3d.d3dDevice->Present( 0, 0, 0, 0 );
}

void ShutDownD3DRender()
{
	shape.ShutDownShape();
	PostProcess::GetInstance()->ShutDown();
	d3d.ShutDownD3D();
}
void ResetD3DRender()
{
	d3d.ResetD3D();
}
void ToggleVSync( bool toggle )
{
	d3d.m_bVSync = toggle;
	ResetD3DRender();
}
