#include "Header.hlsli"

/////////////////////////////////////////////////////////////////////////////
// Constant buffer
/////////////////////////////////////////////////////////////////////////////
cbuffer ObjectVars : register( cb0 )
{
    row_major matrix worldMatrix;
}

cbuffer CameraVars : register( cb1 )
{
    row_major matrix viewMatrix;
}

cbuffer ScreenVars : register( cb2 )
{
    row_major matrix projectionMatrix;
}

/////////////////////////////////////////////////////////////////////////////
// Vertex Shader
/////////////////////////////////////////////////////////////////////////////
PsInput main( VsInput input )
{
    PsInput output = { input.position, input.tex, input.normal };

    // Calculate the position of the vertex against the matrices
    output.position = mul(output.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    // Calculate the normal vector against the world matrix and normalize
    output.normal = mul(output.normal, (float3x3)worldMatrix);
    output.normal = normalize(output.normal);

    return output;
}
