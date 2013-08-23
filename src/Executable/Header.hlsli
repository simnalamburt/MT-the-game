/////////////////////////////////////////////////////////////////////////////
// TYPEDEFS
/////////////////////////////////////////////////////////////////////////////

struct VsInput
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct PsInput
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};