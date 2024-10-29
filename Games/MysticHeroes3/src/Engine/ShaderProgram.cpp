#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode = GetShaderCode(vertexPath);
    std::string fragmentCode = GetShaderCode(fragmentPath);

    unsigned int vertexShader = CreateAndCompileShader(vertexCode.c_str(), "VERTEX");
    unsigned int fragmentShader = CreateAndCompileShader(fragmentCode.c_str(), "FRAGMENT");

    ProgramId = glCreateProgram();
    glAttachShader(ProgramId, vertexShader);
    glAttachShader(ProgramId, fragmentShader);
    glLinkProgram(ProgramId);
    CheckCompileErrors(ProgramId, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void ShaderProgram::Use() const
{
    glUseProgram(ProgramId);
}

void ShaderProgram::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), (int)value);
}

void ShaderProgram::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), value);
}

void ShaderProgram::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ProgramId, name.c_str()), value);
}

void ShaderProgram::SetMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::SetVec4(const std::string& name, const glm::vec4& vec) const
{
    glUniform4fv(glGetUniformLocation(ProgramId, name.c_str()), 1, &vec[0]);
}

std::string ShaderProgram::GetShaderCode(const char* codePath)
{
    std::string code;
    std::ifstream fileStream;

    fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        fileStream.open(codePath);

        std::stringstream stringStream;
        stringStream << fileStream.rdbuf();

        fileStream.close();

        code = stringStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    return std::move(code);
}

unsigned int ShaderProgram::CreateAndCompileShader(const char* shaderCode, std::string shaderType)
{
    const auto glShaderType = shaderType == "VERTEX"
        ? GL_VERTEX_SHADER
        : GL_FRAGMENT_SHADER;

    unsigned int shader = glCreateShader(glShaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    CheckCompileErrors(shader, shaderType);

    return shader;
}

void ShaderProgram::CheckCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}