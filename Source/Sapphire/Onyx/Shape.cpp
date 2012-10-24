#include"Shape.h"
#include "Timer.h"

	
		void GenTriGrid(int numVertRows, int numVertCols,
		float dx, float dz, 
		const D3DXVECTOR3& center, 
		std::vector<D3DXVECTOR3>& verts,
		std::vector<DWORD>& indices);

void Shape::InitializeShape( IDirect3DDevice9* device )
{
	D3DXCreateEffectFromFile(device,L"../../Resources/Shaders/textured.fx",0,0,0,0,&textureEffect,0);
	D3DXCreateTextureFromFile( device, L"../../Resources/Textures/metallock3.dds", &metalTexture);
	void *mem = 0;

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








	D3DXCreateEffectFromFile( device, L"../../Resources/Shaders/Textured.fx",0,0,0,0,&groundEffect,0);
	D3DXCreateTextureFromFile( device, L"../../Resources/Textures/Weedy Lawn.jpg", &groundTexture );


	InitGround( device );
	D3DVERTEXELEMENT9 decl[] =
	{
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};

	device->CreateVertexDeclaration( decl, &grounddecl );
	D3DXMatrixIdentity( &ground );


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
	RenderGround( device, camera, projection );
}
void Shape::ShutDownShape()
{

}

void Shape::RenderCube( IDirect3DDevice9* device, D3DXMATRIX camera, D3DXMATRIX projection )
{
	D3DXMATRIX camInv;
	D3DXMatrixInverse( &camInv, 0, &camera );
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


void Shape::InitGround( IDirect3DDevice9* device )
{

	std::vector<D3DXVECTOR3> verts;
	std::vector<DWORD> indices;
	GenTriGrid(GROUND_WIDTH, GROUND_HEIGHT, CELL_WIDTH, CELL_HEIGHT, D3DXVECTOR3(0.0f, 0.0f, 0.0f), verts, indices);
	// Save vertex count and triangle count for DrawIndexedPrimitive arguments.
	mNumGridVertices  = GROUND_WIDTH * GROUND_HEIGHT;
	mNumGridTriangles = (GROUND_WIDTH - 1) * (GROUND_HEIGHT - 1) * 2;
	// Obtain a pointer to a new vertex buffer.
	device->CreateVertexBuffer(mNumGridVertices * sizeof(VERTUV), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &groundbuff, 0);
	// Now lock it to obtain a pointer to its internal data, and write the
	// grid's vertex data.
	VERTUV* v = 0;
	groundbuff->Lock(0, 0, (void**)&v, 0);
	float texScale = 0.5f;
	for(int i = 0; i < GROUND_WIDTH; ++i)
	{
		for(int j = 0; j < GROUND_HEIGHT; ++j)
		{
			DWORD index = i * ((GROUND_WIDTH + GROUND_HEIGHT)/2) + j;
			v[index].pos.x    = verts[index].x;
			v[index].pos.y    = rand()%25 * 0.025f;
			v[index].pos.z    = verts[index].z;
			v[index].uv = D3DXVECTOR2((float)j, (float)i ) * texScale;
		}
	}
	groundbuff->Unlock();
	// Obtain a pointer to a new index buffer.
	device->CreateIndexBuffer( mNumGridTriangles * 3 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &groundindex, 0);
	// Now lock it to obtain a pointer to its internal data, and write the
	// grid's index data.
	WORD* k = 0;
	groundindex->Lock(0, 0, (void**)&k, 0);
	for(DWORD i = 0; i < mNumGridTriangles*3; ++i)
		k[i] = (WORD)indices[i];
	groundindex->Unlock();
}

void Shape::RenderGround(IDirect3DDevice9* device, D3DXMATRIX camera, D3DXMATRIX projection )
{
	// TODO: render ground with textured shader
	unsigned passes(0);
	groundEffect->Begin( &passes, 0 );
	for( unsigned i(0); i < passes; ++i )
	{
		groundEffect->BeginPass(i);
		groundEffect->SetMatrix( "gWorld", &(ground) );
		groundEffect->SetMatrix( "gViewProjection", &(camera * projection));
		groundEffect->SetTexture( "gDiffuseTexture", groundTexture );
		groundEffect->CommitChanges();

		device->SetVertexDeclaration( grounddecl );
		device->SetStreamSource( 0, groundbuff, 0, sizeof( VERTUV ) );
		device->SetIndices( groundindex );
		device->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, mNumGridVertices, 0, mNumGridTriangles );

		groundEffect->EndPass();
	}
	groundEffect->End();
}

void GenTriGrid( int numVertRows, int numVertCols,float dx, float dz, const D3DXVECTOR3& center, std::vector<D3DXVECTOR3>& verts, std::vector<DWORD>& indices )
{
	int numVertices = numVertRows*numVertCols;
	int numCellRows = numVertRows-1;
	int numCellCols = numVertCols-1;

	int numTris = numCellRows*numCellCols*2;

	float width = (float)numCellCols * dx;
	float depth = (float)numCellRows * dz;

	// Build verts
	verts.resize( numVertices );

	// Offsets to translate grid from quadrant 4 to center of 
	// coordinate system.
	float xOffset = -width * 0.5f; 
	float zOffset =  depth * 0.5f;

	int k = 0;
	for(float i = 0; i < numVertRows; ++i)
	{
		for(float j = 0; j < numVertCols; ++j)
		{
			// Negate the depth coordinate to put in quadrant four.  
			// Then offset to center about coordinate system.
			verts[k].x =  j * dx + xOffset;
			verts[k].z = -i * dz + zOffset;
			verts[k].y =  0.0f;

			// Translate so that the center of the grid is at the
			// specified 'center' parameter.
			D3DXMATRIX T;
			D3DXMatrixTranslation(&T, center.x, center.y, center.z);
			D3DXVec3TransformCoord(&verts[k], &verts[k], &T);

			++k; // Next vertex
		}
	}

	//===========================================
	// Build indices.

	indices.resize(numTris * 3);

	// Generate indices for each quad.
	k = 0;
	for(DWORD i = 0; i < (DWORD)numCellRows; ++i)
	{
		for(DWORD j = 0; j < (DWORD)numCellCols; ++j)
		{
			indices[k]     =   i   * numVertCols + j;
			indices[k + 1] =   i   * numVertCols + j + 1;
			indices[k + 2] = (i+1) * numVertCols + j;

			indices[k + 3] = (i+1) * numVertCols + j;
			indices[k + 4] =   i   * numVertCols + j + 1;
			indices[k + 5] = (i+1) * numVertCols + j + 1;

			// next quad
			k += 6;
		}
	}
}