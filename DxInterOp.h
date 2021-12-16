//--------------------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once

#include <DirectXMath.h>

#ifndef SAFE_DELETE
    #define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif    

#ifndef SAFE_DELETE_ARRAY
    #define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif    

#ifndef SAFE_RELEASE
    #define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif

#ifndef SAFE_RELEASE_DELETE
    #define SAFE_RELEASE_DELETE(p)	{ if(p) { (p)->Release(); delete (p); (p)=NULL; } }
#endif
#ifndef RETURN_IF_FAIL
    #define RETURN_IF_FAIL(x)    { HRESULT thr = (x); if (FAILED(thr)) { return E_FAIL; } }
#endif

struct Vertex2D
{
    DirectX::XMFLOAT2 Pos;
};
