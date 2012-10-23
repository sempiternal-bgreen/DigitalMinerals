#include "D3D.h"	

HRESULT D3D::InitializeD3D( HWND hWnd )
{	
	m_bVSync = false;
	SetScreenWidth( 0.0f );
	SetScreenHeight( 0.0f );
	if( NULL == ( d3dObject = Direct3DCreate9( D3D_SDK_VERSION ) ) ) { return E_FAIL; }
	ZeroMemory( &d3dPresentParameters, sizeof( D3DPRESENT_PARAMETERS ) );

	d3dPresentParameters.Windowed				= true;
	d3dPresentParameters.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dPresentParameters.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	d3dPresentParameters.AutoDepthStencilFormat	= D3DFMT_D16;
	d3dPresentParameters.BackBufferFormat		= D3DFMT_UNKNOWN;
	d3dPresentParameters.EnableAutoDepthStencil	= true;

	if( m_bVSync )	{ d3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; }
	else			{ d3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; } 

	if( FAILED( d3dObject->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPresentParameters, &d3dDevice ) ) )	{ return E_FAIL; }

	d3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	d3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	return S_OK;
}
void D3D::ShutDownD3D()
{
	if( d3dDevice != NULL )	
	{ 
		d3dDevice->Release(); 
		d3dDevice = NULL;
	}
	if( d3dObject != NULL )		
	{ 
		d3dObject->Release(); 
		d3dObject = NULL;
	}
}
void D3D::ResetD3D()
{
	if( m_bVSync )	{ d3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; }
	else			{ d3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; }
	d3dDevice->Reset( &d3dPresentParameters );
}
