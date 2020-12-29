#include "Shader.h"

#include <fstream>
#include <string>
#include <sstream>

struct ShaderProgSrc
{
    std::string VertexSource;
    std::string FragmentSource;
};

static int CompileShader(const std::string& source,unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    Call(glShaderSource(id, 1, &src, nullptr));
    Call(glCompileShader(id));

    int result;
    Call(glGetShaderiv(id, GL_COMPILE_STATUS,&result));
    if(result == GL_FALSE)
    {
        int len;
        Call(glGetShaderiv(id, GL_INFO_LOG_LENGTH,&len));
        char* msg = new char[len];
        Call(glGetShaderInfoLog(id, len,&len,msg));
        std::cout << "ERROR in Compiling:" << (type == GL_VERTEX_SHADER ? "Vertex"  : "Fragment")
        << "Shader Due To :-\n"<< msg << std::endl;
        Call(glDeleteShader(id));
    }

    return id;
}

static ShaderProgSrc ParseShader(const std::string& filename)
{
    std::fstream s(filename.c_str(), std::ios::in);

    int type = -1;

    std::string line;
    std::stringstream ss[2];
    while(getline(s,line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            {
                type = 0;
            }
            else if(line.find("fragment") != std::string::npos)
            {
                type = 1;
            }

        }
        else
        {
            ss[type] << line << "\n";
        }
    }

    return {ss[0].str(),ss[1].str()};
}

static int CreateShader(std::string& vertexshader, std::string& fragmentshader)
{
    unsigned int prog = glCreateProgram();
    unsigned int vs = CompileShader(vertexshader,GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragmentshader,GL_FRAGMENT_SHADER);

    Call(glAttachShader(prog,vs));
    Call(glAttachShader(prog,fs));
    Call(glLinkProgram(prog));
    int result;
    glGetProgramiv(prog, GL_LINK_STATUS, &result);
    if(result == GL_FALSE)
    {
        int len;
        Call(glGetProgramiv(prog, GL_INFO_LOG_LENGTH,&len));
        char* msg = new char[len];
        Call(glGetProgramInfoLog(prog, len,&len,msg));
        std::cout << "ERROR in Linking Shader Due To :-\n"<< msg << std::endl;
        Call(glDeleteProgram(prog));

        raise(SIGBREAK);
    }
    Call(glValidateProgram(prog));

    Call(glDeleteShader(vs));
    Call(glDeleteShader(fs));

    return prog;
}
//Global Functions

OGL::Shader::Shader(const std::string& file) : fp(file), rid(0)
{
    ShaderProgSrc src = ParseShader(file);
    rid = CreateShader(src.VertexSource, src.FragmentSource);
}

OGL::Shader::~Shader()
{
    //dtor
}

void OGL::Shader::Bind()
{
    Call(glUseProgram(rid));
}

void OGL::Shader::Unbind()
{
    Call(glUseProgram(0));
}

void OGL::Shader::SetUniform(const std::string& name, float r, float g, float b, float al)
{
    glUniform4f(GetUniformLocation(name), r, g, b, al);
}

unsigned int OGL::Shader::GetUniformLocation(const std::string& name)
{
    int loc = 0;
   // if(UniformMap.find(name) == UniformMap.end())
    {
        loc = glGetUniformLocation(rid, name.c_str());
     //   UniformMap.insert(std::pair<std::string, int>(name, loc));
    }
 //   else
     //   loc = UniformMap[name];
    return loc;
}

void OGL::Shader::SetUniform1i(const std::string& name, float f1)
{
    glUniform1i(GetUniformLocation(name), f1);
}

void OGL::Shader::SetUniformMat4f(const std::string& name, const glm::mat4& mat)
{
   // GLfloat a[] = mat[0][0];
    glUniformMatrix4fv( GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}
