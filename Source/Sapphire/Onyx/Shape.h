#ifndef SHAPE_H_
#define SHAPE_H_

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

class Shape
{
public:
		IDirect3DVertexBuffer9		*cubebuff;
	IDirect3DIndexBuffer9		*cubeindex;
	IDirect3DVertexDeclaration9	*cubedecl;
	ID3DXEffect					*textureEffect;
	IDirect3DTexture9			*metalTexture;
	D3DXMATRIX					cube;

	void InitializeShape( IDirect3DDevice9* d3d9 );
	void UpdateShape( float time );
	void RenderShape( IDirect3DDevice9* device, D3DXMATRIX camera, D3DXMATRIX projection );
	void ShutDownShape();

	void RenderCube( IDirect3DDevice9* device, D3DXMATRIX camera, D3DXMATRIX projection );
};

#endif
