#include"Shape.h"
#include "Timer.h"

void Shape::InitializeShape( IDirect3DDevice9* device )
{
	D3DXCreateEffectFromFile(device,L"../../Resources/Shaders/textured.fx",0,0,0,0,&textureEffect,0);
	D3DXCreateTextureFromFile( device, L"../../Resources/Textures/metallock3.dds", &metalTexture);
	void *mem = 0;
	// create cube vertex buffer
	struct VERTUV
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR2	uv;
	};

	// build indexed cube
	VERTUV cubeverts[] = 
	{
		{ D3DXVECTOR3(-0.75f, 0.75f,-0.75f), D3DXVECTOR2(0,0) },
		{ D3DXVECTOR3( 0.75f, 0.75f,-0.75f), D3DXVECTOR2(1,0) },
		{ D3DXVECTOR3( 0.75f,-0.75f,-0.75f), D3DXVECTOR2(1,1) },
		{ D3DXVECTOR3(-0.75f,-0.75f,-0.75f), D3DXVECTOR2(0,1) },

		{ D3DXVECTOR3(-0.75f, 0.75f, 0.75f), D3DXVECTOR2(1,0) },
		{ D3DXVECTOR3( 0.75f, 0.75f, 0.75f), D3DXVECTOR2(0,0) },
		{ D3DXVECTOR3( 0.75f,-0.75f, 0.75f), D3DXVECTOR2(0,1) },
		{ D3DXVECTOR3(-0.75f,-0.75f, 0.75f), D3DXVECTOR2(1,1) }
	};
	short cubeindicies[] = 
	{
		0,1,3, 3,1,2,// front
		0,4,5, 0,5,1,// top
		1,5,2, 2,5,6,// right
		4,0,7, 7,0,3,// left
		7,3,2, 7,2,6,// bottom
		5,4,6, 6,4,7// back
	};

		// create vertex and index buffer
	device->CreateVertexBuffer(unsigned int(sizeof(VERTUV) * 8), 0,0, D3DPOOL_MANAGED, &cubebuff,0);
	mem = 0;
	cubebuff->Lock(0,0,&mem,0);
	memcpy(mem,cubeverts,8 * sizeof(VERTUV));
	cubebuff->Unlock();
	// index
	device->CreateIndexBuffer(sizeof(short)*36, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &cubeindex,0);
	mem = 0;
	cubeindex->Lock(0,0,&mem,0);
	memcpy(mem,cubeindicies,36 * sizeof(short));
	cubeindex->Unlock();

		// cube & quad
	
	D3DVERTEXELEMENT9 decl2[] = 
	{ 
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};
	device->CreateVertexDeclaration( decl2, &cubedecl );

	D3DXMatrixTranslation( &cube, 0, 1.5f, -2.75f );
}
void Shape::UpdateShape( float time )
{
	D3DXMATRIX r;
	D3DXMatrixRotationY( &r, D3DXToRadian(50) * time );
	cube = r * cube;
}
void Shape::RenderShape( IDirect3DDevice9* device, D3DXMATRIX camera, D3DXMATRIX projection )
{
	RenderCube( device, camera, projection );
}
void Shape::ShutDownShape()
{

}

void Shape::RenderCube( IDirect3DDevice9* device, D3DXMATRIX camera, D3DXMATRIX projection )
{
	unsigned int passes3(0);
	HRESULT hr = textureEffect->Begin(&passes3, 0);

	for(unsigned i(0); i<passes3; ++i)
	{
		textureEffect->BeginPass(i);

		textureEffect->SetMatrix("gWorld", &cube );
		textureEffect->SetMatrix("gViewProjection", &(camera * projection) );
		textureEffect->SetTexture("gDiffuseTexture", metalTexture );
		textureEffect->CommitChanges();
		// render data
		device->SetVertexDeclaration( cubedecl );
		device->SetStreamSource( 0, cubebuff, 0, 20 );
		device->SetIndices( cubeindex );
		device->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 12, 0, 12 );

		textureEffect->EndPass();
	}
	textureEffect->End();
}