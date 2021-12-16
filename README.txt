DX interop sample

-Overview:
This sample demonstrates the usage of AMP C++ interOp APIs with Direct3D 11. It displays the rotation animation of a triangle shape.

-Hardware requirement:
This sample requires a DirectX 11 capable card. If there is not a DirectX 11 capable card in the system, the sample will use DirectX 11 reference emulator with very low performance.

-Software requirement:
Install Visual Studio Dev11 Beta from http://msdn.microsoft.com
The latest version of HLSL compiler. Starting with Windows 8 Consumer Preview, the DirectX SDK is included as part of the Windows SDK. The HLSL compiler D3DCOMPILER_44.DLL is installed under %ProgramFiles(x86)%\Windows Kits\8.0\Redist\D3D\<arch>

-Running the sample:
This sample contains the DXInterOp project which builds a graphical sample which displays the animation of a triangle rotation in a DirectX rendering window.  

-Description:
This sample is first written using pure DirectX 11 features. Then it is ported to use AMP C++ feature. The porting takes the following 5 steps:

1) Refactored the compute shader in a HLSL file into the lamda function of an AMP C++ parallel_for_each closure, which is defined in the AMP_compute_engine class.
2) Passed the ID3D11Device, which is created calling DirectX 11 API D3D11CreateDeviceAndSwap() in the DX code, to the AMP_compute_engine to create an accelerator_view using the InterOp API direct3d::create_accelerator_view(ID3D11Device*)
3) Qeuried the ID3D11Buffer, which is associated with the result array in the AMP_compute_engine, by calling the InterOp API direct3d::get_buffer(array)->QueryInterface()
4) Created a readonly resource view for the Vertex shader as the input using the queried ID3D11Buffer. It is worth to note that the ID3D11Buffer implemented in AMP C++ runtime for arrays are type ByteAddressBuffer. The number of elements of the resource view might need to be adjusted if the vertex data type is not int, uint or float.
5) Adjusted the input buffer access in the Vertex shader to reflect that the buffer is type of ByteAddressBuffer


