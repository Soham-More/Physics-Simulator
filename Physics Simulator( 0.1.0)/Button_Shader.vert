// This Shader is used to Draw Button Text.

uniform sampler2D texture;
uniform vec2 Mouse;
uniform vec3 Max;
uniform vec3 Color;

uniform float val;

void main()
{
    float dist = distance(Mouse.xy, gl_FragCoord.xy);

    float factor = (0.01f * dist * dist) - (0.05f * dist) + 250;

    vec4 color = vec4(Color, 1.0f) + (vec4(1.0f, 0.0f, 0.0f, 1.0f) * 1.75f * val * (1/factor));

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

    color.a = 0.0f;

    vec2 pos = gl_TexCoord[0].xy;

    vec4 Col = texture2D(texture,pos);

    gl_FragColor = vec4(vec3(1.0f, 1.0f, 1.0f) - Col.rgb, Col.a) + color;
}
