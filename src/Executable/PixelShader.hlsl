#include "Header.hlsli"

/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////
Texture2D Texture : register( t0 );

SamplerState TextureSampler : register( s0 );

/////////////////////////////////////////////////////////////////////////////
// Constant buffer
/////////////////////////////////////////////////////////////////////////////
cbuffer LightVars : register( cb0 )
{
    float4 lightColor;
    float3 lightDirection;
    float padding;
}


/////////////////////////////////////////////////////////////////////////////
// Pixel Shader
/////////////////////////////////////////////////////////////////////////////
float4 main( PsInput input ) : SV_TARGET
{
    // Sample the pixel color from the texture using the sampler
    //     at this texture coordinate location
    float4 diffuseColor = Texture.Sample(TextureSampler, input.tex);
    
    // Calculate the amount of light on this pixel
    float lightIntensity = saturate(dot(input.normal, -lightDirection));
    
    // Determine the final amount of diffuse color
    return diffuseColor * saturate(lightColor * lightIntensity);
}