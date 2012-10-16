#include "PostProcess.h"
#include "D3D.h"
#include "Timer.h"

PostProcess::PostProcess(void){}
PostProcess::~PostProcess(void)
{
	ShutDown();
}
PostProcess* PostProcess::GetInstance(void)
{
	static PostProcess instance;
	return &instance;
}

void PostProcess::Initialize( IDirect3DDevice9 *device )
{

	// GRAB THE ACTUAL DISPLAY WIDTH
	IDirect3DSurface9* bBuffer = 0;
	device->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &bBuffer );
	bBuffer->GetDesc( &backbuffer );
	bBuffer->Release();  // DROP REF COUNT

	// LOAD IN AN EFFECT
	D3DXCreateEffectFromFile( device, L"../../Resources/PostProcess Shaders/Post.fx", 0, 0, 0, 0, &postEffect, 0 );

	// MAKE THE RENDER TARGET TEXTURE
	D3DXCreateTexture( device, 640, 480, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R8G8B8, D3DPOOL_DEFAULT, &renderTarget ); 

	// CREATE SCREEN SPACE QUAD WITH HALF-TEXEL OFFSET
	void *mem = 0;
	struct QUAD
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR2 uv;
	};
	QUAD quadverts[] =
	{
		{ D3DXVECTOR3( -1.0f, -1.0f, 0.0f ), D3DXVECTOR2( 0 , 1) },
		{ D3DXVECTOR3( -1.0f,  1.0f, 0.0f ), D3DXVECTOR2( 0 , 0) },
		{ D3DXVECTOR3(  1.0f,  1.0f, 0.0f ), D3DXVECTOR2( 1 , 0) },
		{ D3DXVECTOR3(  1.0f, -1.0f, 0.0f ), D3DXVECTOR2( 1 , 1) }
	};
	// INDICIES FOR QUAD
	short quadindicies[] =
	{
		0,1,2, 0,2,3
	};

	// CREATE VERTEX BUFFER FOR QUAD
	device->CreateVertexBuffer( unsigned int( sizeof( QUAD ) * 4 ), 0, 0, D3DPOOL_MANAGED, &quadbuff, 0 );
	mem = 0;
	quadbuff->Lock( 0, 0, &mem, 0 );
	memcpy( mem, quadverts, 4 * sizeof( QUAD ) );
	quadbuff->Unlock();

	// CREATE INDEX BUFFER FOR QUAD
	device->CreateIndexBuffer( sizeof( short ) * 6, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &quadindex, 0 );
	mem = 0;
	quadindex->Lock( 0, 0, &mem, 0 );
	memcpy( mem, quadindicies, 6 * sizeof( short ) );
	quadindex->Unlock();

	// VERTEX DECLARATIONS
	D3DVERTEXELEMENT9 decl[] = 
	{ 
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};
	device->CreateVertexDeclaration(decl, &cubedecl);

	// SHADER TYPE
	techs[0] = ( "PassThrough" );
	techs[1] = ( "InversePositions" );
	techs[2] = ( "Invert" );
	techs[3] = ( "Monochrome" );
	techs[4] = ( "Sepia" );
	techs[5] = ( "Warped" );
	techs[6] = ( "BlackAndWhite" );
	techs[7] = ( "Embossed" );
	techs[8] = ( "ColorLoop" );
	techs[9] = ( "TronEnergy" );
	techs[10] = ( "Dissolve" );
	index = 0;

	// COLOR
	colChange = 1;
	fRed = 0;
	fGreen = 0;
	fBlue = 0;

	current = 0;
	output = 0;
}
void PostProcess::Update()
{
	UpdateColor();;
}
void PostProcess::BeginPostProcess( IDirect3DDevice9 *device )
{
	// STORE BACKBUFFER
	current = 0;

	device->GetRenderTarget( 0, &current );

	// GET TEXTURE SURFACE AND SET RENDER TARGET
	output = 0;
	renderTarget->GetSurfaceLevel(0,&output);
	device->SetRenderTarget(0,output);
	// CLEAR RENDERTARGET
	device->Clear( 0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 ); // MODIFY FOR ZBUFFER

}
void PostProcess::EndPostProcess( IDirect3DDevice9 *device )
{
	// RESTORE BACKBUFFER
	device->SetRenderTarget( 0, current );

	// DROP REF COUNTS
	current->Release();
	output->Release();
	// CLEAR BACKBUFFER
	device->Clear( 0, 0, D3DCLEAR_TARGET , D3DCOLOR_XRGB(0,255,0), 1.0f, 0);	// MODIFY FOR ZBUFFER

	// SET THE TECHNIQUE TO THE PROPER EFFECT
	postEffect->SetTechnique( techs[index] );

	// RENDER QUAD WITH POST SHADER
	unsigned passes(0);
	postEffect->Begin(&passes, 0);
	for(unsigned i(0); i<passes; ++i)
	{
		postEffect->BeginPass(i);
		postEffect->SetTexture( "gDiffuseTexture", renderTarget );
		postEffect->SetFloat( "gTime" , Timer::GetInstance()->GetTime() );
		postEffect->SetFloat( "gRed" , fRed );
		postEffect->SetFloat( "gGreen" , fGreen );
		postEffect->SetFloat( "gBlue" , fBlue );

		postEffect->CommitChanges();
		device->SetVertexDeclaration( cubedecl );
		device->SetStreamSource( 0, quadbuff, 0, 20 );
		device->SetIndices( quadindex );
		device->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2 );
		postEffect->EndPass();
	}
	postEffect->End();
}
void PostProcess::ShutDown( void )
{
	if( renderTarget != NULL )
	{
		renderTarget->Release();
		renderTarget = NULL;
	}
	if( quadbuff != NULL )
	{
		quadbuff->Release();
		quadbuff = NULL;
	}
	if( quadindex != NULL )
	{
		quadindex->Release();
		quadindex = NULL;
	}
	if( cubedecl != NULL )
	{
		cubedecl->Release();
		cubedecl = NULL;
	}
	if( postEffect != NULL )
	{
		postEffect->Release();
		postEffect = NULL;
	}
}

void PostProcess::UpdateColor()
{
	switch( colChange )
	{
	case 1 :
		{
			fRed   += Timer::GetInstance()->GetDeltaTime() * 1.0f;
			fGreen -= Timer::GetInstance()->GetDeltaTime() * 1.0f;
			fBlue  -= Timer::GetInstance()->GetDeltaTime() * 1.0f;

			if( fBlue <= 0.0f )
			{
				fBlue = 0;
			}
			if( fGreen <= 0.0f )
			{
				fGreen = 0;
			}
			if( fRed >= 1.0f )
			{
				colChange = 2;
			}
		}
		break;	

	case 2 :
		{
			fRed   -= Timer::GetInstance()->GetDeltaTime() * 1.0f;
			fGreen += Timer::GetInstance()->GetDeltaTime() * 1.0f;
			fBlue  -= Timer::GetInstance()->GetDeltaTime() * 1.0f;
			if( fRed <= 0.0f )
			{
				fRed = 0;
			}
			if( fBlue <= 0.0f )
			{
				fBlue = 0;
			}
			if( fGreen >= 1.0f )
			{
				colChange = 3;
			}
		}
		break;

	case 3 :
		{
			fRed   -= Timer::GetInstance()->GetDeltaTime() * 1.0f;
			fGreen -= Timer::GetInstance()->GetDeltaTime() * 1.0f;
			fBlue  += Timer::GetInstance()->GetDeltaTime() * 1.0f;
			if( fRed <= 0.0f )
			{
				fRed = 0;
			}
			if( fGreen <= 0.0f )
			{
				fGreen = 0;
			}
			if( fBlue >= 1.0f )
			{
				colChange = 1;
			}
		}
		break;
	}
}
void PostProcess::ReleaseTexture(void)
{
	if(renderTarget) { renderTarget->Release(); }
}
void PostProcess::ReCreateTexture( IDirect3DDevice9 *device )
{
	D3DXCreateTexture( device, backbuffer.Width, backbuffer.Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R8G8B8, D3DPOOL_DEFAULT, &renderTarget ); 
}
