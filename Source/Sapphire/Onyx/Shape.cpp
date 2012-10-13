#include"Shape.h"

void Shape::InitializeShape( IDirect3DDevice9* device )
{
	D3DXCreateEffectFromFile( device,  L"../../Resources/Shaders/smoothshade.fx", 0 ,0, 0, 0, &meshEffect, 0 );
	D3DXCreateSphere( device, 1, 175, 175, &sphereMesh, 0 );
	D3DXMatrixTranslation( &sphereMatrix, 0, 1.25f, -3.0f );
}
void Shape::UpdateShape( float time )
{
	D3DXMATRIX sphereRotation;
	D3DXMatrixIdentity( &sphereRotation );
	D3DXMatrixRotationY( &sphereRotation, D3DXToRadian( 125.0f * time ) );
	D3DXMatrixMultiply( &sphereMatrix, &sphereRotation, &sphereMatrix );
}
void Shape::RenderShape( D3DXMATRIX camera, D3DXMATRIX projection )
{
	RenderSphere( camera, projection );
}
void Shape::ShutDownShape()
{
	if( sphereMesh != NULL )	
	{ 
		sphereMesh->Release(); 
		sphereMesh = NULL;
	}
	if( meshEffect != NULL )		
	{ 
		meshEffect->Release(); 
		meshEffect = NULL;
	}
}

void Shape::RenderSphere( D3DXMATRIX camera, D3DXMATRIX projection )
{
	unsigned passes(0);
	meshEffect->Begin( &passes, 0 );
	for( unsigned i(0); i < passes; ++i )
	{
		meshEffect->BeginPass(i);
		meshEffect->SetMatrix( "gWorldViewProjection", &( sphereMatrix * camera * projection ) );
		meshEffect->CommitChanges();
		sphereMesh->DrawSubset(0);
		meshEffect->EndPass();
	}
	meshEffect->End();
}