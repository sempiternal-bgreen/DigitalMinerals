#ifndef SHAPE_H_
#define SHAPE_H_

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

class Shape
{
public:
	ID3DXMesh	*sphereMesh;
	D3DXMATRIX	sphereMatrix;
	ID3DXEffect	*meshEffect;

	void InitializeShape( IDirect3DDevice9* d3d9 );
	void UpdateShape( float time );
	void RenderShape( D3DXMATRIX camera, D3DXMATRIX projection );
	void ShutDownShape();

	void RenderSphere( D3DXMATRIX camera, D3DXMATRIX projection );
};

#endif
