//--------------------------------------------------------------------------------------
// File: ComputeEngine.h
//
// This is an AMPC++ implementation of a compute shader. It transforms a shape with a
// rotation of an angle THETA. 
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once

#include <windows.h>
#include <memory>
#include <amp.h>
#include <amp_math.h>
#include <amp_graphics.h>
#include "DXInterOp.h"

using namespace concurrency;
using namespace concurrency::fast_math;
using namespace concurrency::direct3d;

// Rotation angle
#define THETA 3.1415f/1024  

class AMP_compute_engine
{
public:
    AMP_compute_engine(ID3D11Device* d3ddevice) : m_accl_view(create_accelerator_view(d3ddevice))     {}

    void initialize_data(int num_elements, const Vertex2D* data)     {
        m_data = std::unique_ptr<array<Vertex2D,1>>(new array<Vertex2D, 1>(num_elements, data, m_accl_view));
    }

    HRESULT get_data_d3dbuffer(void** d3dbuffer) const    {
        return get_buffer(*m_data)->QueryInterface(__uuidof(ID3D11Buffer), (LPVOID*)d3dbuffer);
    }

    void run()    {
        array<Vertex2D, 1>& data_ref = *m_data;

        // Transform the vertex data on the accelerator which is associated with the array data_ref. 
        //
        // If in some cases, you need to use array_view instead of array, you need to explicitily 
        // specify the accelerator_view in the parallel_for_each to avoid implicit copy of the array_view
        // data from the acclerator_view m_accl_view to the default accelerator_view of the 
        // parallel_for_each
        parallel_for_each(m_data->extent, [=, &data_ref] (index<1> idx) restrict(amp)
        {
            // Rotate the vertex by angle THETA
            DirectX::XMFLOAT2 pos = data_ref[idx].Pos;
            data_ref[idx].Pos.y = pos.y * cos(THETA) - pos.x * sin(THETA);
            data_ref[idx].Pos.x = pos.y * sin(THETA) + pos.x * cos(THETA);
        });
    }

private:
    accelerator_view					m_accl_view;
    std::unique_ptr<array<Vertex2D, 1>>	m_data;
};

