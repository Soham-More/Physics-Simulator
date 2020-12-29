#ifndef SHADER_H
#define SHADER_H

#include <Call.h>

#include <fstream>
#include <string>
#include <sstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <unordered_map>

namespace OGL
{
    class Shader
    {
        private:
            unsigned int rid;
            unsigned int GetUniformLocation(const std::string& name);
            std::string fp;

            std::unordered_map<std::string, int> UniformMap;
        public:
            Shader(){}
            Shader(const std::string& file);
            ~Shader();

            void Bind();
            void Unbind();

            void SetUniform1i(const std::string& name, float f1);

            void SetUniform(const std::string& name, float r, float g, float b, float al);

            void SetUniformMat4f(const std::string& name, const glm::mat4& mat);

            bool isValidShader(){ return (rid != 0); }

    };
}

#endif // SHADER_H
