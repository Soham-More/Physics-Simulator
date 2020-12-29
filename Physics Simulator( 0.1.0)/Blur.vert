// This shader implements Gaussian Blur.

uniform float Sigma;
uniform float blur_radius;
uniform sampler2D texture;

float Get_Normal_Distribution(float x, float y)
{
    float e = 2.7182818284590452353602874713527f;
    float pi = 3.141592653589793238f;

    float Val = (1/(2 * pi * (Sigma * Sigma))) * pow(e, -((x*x) + y*y)/(2 * Sigma));

    return Val;
}

vec4 Get_Blurred_Pixel(float x, float y)
{
    float blur_radius = 0.0025f;

    vec2 offx = vec2(blur_radius, 0.0);
    vec2 offy = vec2(0.0, blur_radius);

    vec2 pos = gl_TexCoord[0].xy;

    return texture2D(texture, pos + (x * offx) + (y * offy)) * Get_Normal_Distribution(x, y);
}

void main()
{
    vec2 offx = vec2(blur_radius, 0.0);
    vec2 offy = vec2(0.0, blur_radius);

    vec2 pos = gl_TexCoord[0].xy;

    // DO NOT CHANGE THIS VALUE!!!!!
    // Changing this value will affect the program very badly.
    int Convolution_Matrix_Size = 5;

    vec4 Final_Color;

    for(int x = -1 * Convolution_Matrix_Size; x < Convolution_Matrix_Size; x++)
    {
        for(int y = -1 * Convolution_Matrix_Size; y < Convolution_Matrix_Size; y++)
        {
            Final_Color += Get_Blurred_Pixel(x, y);
        }
    }

    gl_FragColor = Final_Color;
}
