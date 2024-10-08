#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

class ShaderProgram
{
public:
    unsigned int ProgramId;
    
    ShaderProgram(const char* vertexPath, const char* fragmentPath);
    
    void Use() const;
    
    void SetBool(const std::string& name, bool value) const;
    
    void SetInt(const std::string& name, int value) const;
    
    void SetFloat(const std::string& name, float value) const;

    void SetMat4(const std::string& name, const glm::mat4& mat) const;

private:
    std::string GetShaderCode(const char* codePath);

    unsigned int CreateAndCompileShader(const char* shaderCode, std::string shaderType);

    void CheckCompileErrors(unsigned int shader, std::string type);
};