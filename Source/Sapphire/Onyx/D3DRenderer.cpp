#include "D3DRenderer.h"

#include "D3D.h"
#include "Shape.h"
#include "Camera.h"
#include "Timer.h"
#include "PostProcess.h"

// DEBUG CONSOLE
#include "Tools\DebugConsole.h"

D3D		d3d;
Camera  camera;
Shape	shape;

bool	currentlyDrawing = true;

HRESULT InitializeD3DRender( HWND hWnd, float screenWidth, float screenHeight )
{
	// STARTUP DEBUG CONSOLE
	//SetupDebugConsole();

	// INITIALIZE D3D
	d3d.InitializeD3D( hWnd );
	d3d.SetScreenWidth( screenWidth );
	d3d.SetScreenHeight( screenHeight );

	// INITIALIZE POSTPROCESSING 
	PostProcess::GetInstance()->Initialize( d3d.d3dDevice );

	// INITIALIZE CAMERA
	camera.Initialize( screenWidth, screenHeight );

	// INITIALIZE BASIC SHAPE
	shape.InitializeShape( d3d.d3dDevice );

	return S_OK;
}
void UpdateD3DRender()
{
	// UPDATE TIMER
	Timer::GetInstance()->Update();

	// CHECK IF POSTPROCESSING IS ALLOWED; UPDATE IF TRUE
	if( PostProcess::GetInstance()->m_bPostProcess )	{ PostProcess::GetInstance()->Update(); }

	// UPDATE BASIC SHAPE
	shape.UpdateShape( Timer::GetInstance()->GetDeltaTime() );

	// UPDATE CAMERA
	camera.Update( Timer::GetInstance()->GetDeltaTime(),d3d.m_fScreenWidth, d3d.m_fScreenHeight );
}
void RenderD3DRender()
{
	if( NULL == d3d.d3dDevice ) { return; }

	d3d.d3dDevice->Clear( 0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 135, 206, 250 ), 1.0f, 0 );

	if( PostProcess::GetInstance()->m_bPostProcess )	{ PostProcess::GetInstance()->BeginPostProcess( d3d.d3dDevice ); }

	if( currentlyDrawing )
	{
		d3d.d3dDevice->BeginScene();

		shape.RenderShape( d3d.d3dDevice, camera.CameraViewMatrix, camera.ProjectionMatrix );

		d3d.d3dDevice->EndScene();
		if( PostProcess::GetInstance()->m_bPostProcess )	{ PostProcess::GetInstance()->EndPostProcess( d3d.d3dDevice ); }
		currentlyDrawing = false;
	}

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
void SetCameraToggle( bool toggle )
{
	camera.bCameraIsLocked = toggle;
}