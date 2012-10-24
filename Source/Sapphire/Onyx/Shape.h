#ifndef SHAPE_H_
#define SHAPE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

#include <vector>

// defines for the ground plane
#define GROUND_WIDTH	9
#define GROUND_HEIGHT	9
#define CELL_WIDTH		1.0f
#define CELL_HEIGHT		1.0f

	// create cube vertex buffer
	struct VERTUV
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR2	uv;
	};


class Shape
{
public:
	IDirect3DVertexBuffer9		*cubebuff;
	IDirect3DIndexBuffer9		*cubeindex;
	IDirect3DVertexDeclaration9	*cubedecl;
	ID3DXEffect					*textureEffect;
	IDirect3DTexture9			*metalTexture;
	D3DXMATRIX					cube;

	IDirect3DVertexBuffer9		*groundbuff;
	IDirect3DIndexBuffer9		*groundindex;
	IDirect3DVertexDeclaration9	*grounddecl;
	D3DXMATRIX					 ground; 

	DWORD mNumGridVertices;
	DWORD mNumGridTriangles;

	ID3DXEffect					*groundEffect;
	IDirect3DTexture9			*groundTexture;

	void InitGround(IDirect3DDevice9* device);
	void RenderGround(IDirect3DDevice9* device, D3DXMATRIX camera, D3DXMATRIX projection );


	void InitializeShape( IDirect3DDevice9* d3d9 );
	void UpdateShape( float time );
	void RenderShape( IDirect3DDevice9* device, D3DXMATRIX camera, D3DXMATRIX projection );
	void ShutDownShape();

	void RenderCube( IDirect3DDevice9* device, D3DXMATRIX camera, D3DXMATRIX projection );
};

#endif
