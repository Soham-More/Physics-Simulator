#shader vertex
#version 330 core

//These Shaders are used to draw Cubes/Spheres on Screen.

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 nor;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec4 col;
uniform vec4 cameraPos;
uniform vec4 Origin;

out vec4 Color1;
out vec4 Normal;
out vec4 Curr_Point;
out vec4 CameraPos;
out mat4 inMod;
out vec4 isOnOrigin;

void main()
{
    Color1 = col;

    mat4 MVP = Projection * View * Model;
    vec4 Pos = MVP * pos;

    CameraPos = cameraPos;
    Normal = nor;//mat4(transpose(inverse(Model))) * nor;
    isOnOrigin = Origin;
    inMod = mat4(transpose(inverse(Model)));

    Curr_Point = Model * pos;
    gl_Position = Pos;
}

#shader fragment
#version 330 core

in vec4 Color1;
in vec4 Curr_Point;
in vec4 Normal;
in vec4 CameraPos;
in mat4 inMod;
in vec4 isOnOrigin;

out vec4 GL_Color;

uniform sampler2D x;
uniform sampler2D nx;
uniform sampler2D y;
uniform sampler2D ny;
uniform sampler2D z;
uniform sampler2D nz;

void main()
{
    if(CameraPos.w == 1.0f)
    {
        vec4 normal;

        if(Normal.z == 1.0f)
        {
            normal = texture(x, Normal.xy);
        }
        else if(Normal.z == -1.0f)
        {
            normal = texture(nx, Normal.xy);
        }
        else if(Normal.z == 2.0f)
        {
            normal = texture(y, Normal.xy);
        }
        else if(Normal.z == -2.0f)
        {
            normal = texture(ny, Normal.xy);
        }
        else if(Normal.z == 3.0f)
        {
            normal = texture(z, Normal.xy);
        }
        else if(Normal.z == -3.0f)
        {
            normal = texture(nz, Normal.xy);
        }

        int alpha = int(normal.a * 255.0f);

        if((alpha % 3) != 0)
        {
            normal.x *= -1.0f;
        }
        if((alpha % 5) != 0)
        {
            normal.y *= -1.0f;
        }
        if((alpha % 17) != 0)
        {
            normal.z *= -1.0f;
        }

        vec3 NormalVec = vec4(normal.r, normal.g, normal.b, 0.0f).xyz;

        vec3 RGB_Color = vec3(255.0f, 255.0f, 255.0f);
        vec3 lightColor = RGB_Color * (1/255.0f);
        vec3 lightPos = vec3(0.0f, 0.0f, 0.0f);

        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;

        vec3 norm = normalize(NormalVec.xyz);
        vec3 LightDir = normalize(lightPos - Curr_Point.xyz);

        float diff = abs(dot(norm, LightDir));
        vec3 diffuse = diff * lightColor;

        float specularStrength = 0.5f;

        vec3 viewDir = normalize(CameraPos.xyz - Curr_Point.xyz);
        vec3 reflectDir = reflect(-LightDir, norm);

        float spec = pow(abs(dot(viewDir, reflectDir)), 8);
        vec3 specular = specularStrength * spec * lightColor;

        float k = 0.0075f;

        float r = 1/(k * distance(lightPos, Curr_Point.xyz));

        vec3 final = ((diffuse + ambient + specular) * Color1.xyz) * r;

        vec3 Max = vec3(1.25f, 1.25f, 1.25f);

        if(final.r > Max.r)
        {
            final.r = Max.r;
        }
        if(final.g > Max.g)
        {
            final.g = Max.g;
        }
        if(final.b > Max.b)
        {
            final.b = Max.b;
        }

        GL_Color = vec4(final, 1.0f);
    }
    else if(isOnOrigin.x != 1.0f)
    {
        vec3 RGB_Color = vec3(255.0f, 255.0f, 255.0f);
        vec3 lightColor = RGB_Color * (1/255.0f);
        vec3 lightPos = vec3(0.0f, 0.0f, 0.0f);

        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;

        vec3 norm = normalize(Normal.xyz);
        vec3 LightDir = normalize(lightPos - Curr_Point.xyz);

        float diffuse_strength = 1.00f;

        float diff = max(dot(norm, LightDir), 0.0f);
        vec3 diffuse = diff * lightColor * diffuse_strength;

        float specularStrength = 0.5f;

        vec3 viewDir = normalize(CameraPos.xyz - Curr_Point.xyz);
        vec3 reflectDir = reflect(-LightDir, norm);

        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
        vec3 specular = specularStrength * spec * lightColor;

        float k = 0.075f;

        float r = 1/(k * distance(lightPos, Curr_Point.xyz));

        vec3 final = ((diffuse + ambient + specular) * Color1.xyz) * r;

        GL_Color = vec4(final, 1.0f);
    }
    else
    {
        vec3 RGB_Color = vec3(255.0f, 255.0f, 255.0f);
        vec3 lightColor = RGB_Color * (1/255.0f);

        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;

        vec3 lightPos = vec3(0.0f, 0.0f, 0.0f);

        vec3 norm = normalize(Normal.xyz);
        vec3 LightDir = normalize(lightPos - Curr_Point.xyz);

        float diff = abs(dot(norm, LightDir));
        vec3 diffuse = diff * lightColor;

        float specularStrength = 0.5f;

        vec3 viewDir = normalize(CameraPos.xyz - Curr_Point.xyz);
        vec3 reflectDir = reflect(-LightDir, norm);

        float spec = pow(abs(dot(viewDir, reflectDir)), 16);
        vec3 specular = specularStrength * spec * lightColor;

        float k = 0.075f;//0.1875f;

        float r = 1/(k * distance(lightPos, Curr_Point.xyz));

        vec3 final = (diffuse + ambient + specular) * (Color1.xyz * r);

        GL_Color = vec4(final, 1.0f);
    }
}
