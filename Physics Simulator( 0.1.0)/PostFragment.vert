#version 330 core

// This Shader is used to Draw Button Outline.

uniform sampler2D texture;
uniform vec2 Mouse;
uniform vec3 Max;

uniform float val;

void main()
{
    float dist = distance(Mouse.xy, gl_FragCoord.xy);

    vec4 color = vec4(1.0f, 1.0f, 1.0f, 1.0f) * val * (1/dist);

    if(color.r > Max.r)
    {
        color.r = Max.r;
    }
    if(color.g > Max.g)
    {
        color.g = Max.g;
    }
    if(color.b > Max.b)
    {
        color.b = Max.b;
    }

    gl_FragColor = vec4(mix(color.rgb, vec3(0.0f, 0.0f, 0.0f), 0.25f), color.a);
}
