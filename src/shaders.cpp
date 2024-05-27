#include "shaders/shaders.h"

Shader::Shader(const char* vertPath, const char* fragPath){
    // 1. Use the filepath to retreive the vertex/fragment source code
    std::string vertCode;
    std::string fragCode;
    std::ifstream vertFile;
    std::ifstream fragFile;

    // Check for errors in reaching or opening the files
    vertFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try{
        // Opening the files and reading their buffer contents into streams
        vertFile.open(vertPath);
        fragFile.open(fragPath);
        std::stringstream vertStream, fragStream;
        vertStream << vertFile.rdbuf();
        fragStream << fragFile.rdbuf();

        // Closing the files
        vertFile.close();
        fragFile.close();

        // Converting the streams into strings
        vertCode = vertStream.str();
        fragCode = fragStream.str();
    }

    catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ:" << e.what() << std::endl;
    }

    const char* vertShaderCode = vertCode.c_str();
    const char* fragShaderCode = fragCode.c_str();

    // 2. Compile the shaders
    unsigned int vert, frag;

        // Vertex Shader
    vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertShaderCode, NULL);
    glCompileShader(vert);
    CheckCompileErrors(vert, "VERTEX");

        // Fragment Shader
    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragShaderCode, NULL);
    glCompileShader(frag);
    CheckCompileErrors(frag, "FRAGMENT");

        // Shader Program
    progID = glCreateProgram();
    glAttachShader(progID, vert);
    glAttachShader(progID, frag);
    glLinkProgram(progID);
    CheckCompileErrors(progID, "PROGRAM");

    // 3. Delete Shaders since they're linked to the program and not needed
    glDeleteShader(vert);
    glDeleteShader(frag);
}

// Activate the Shaders
void Shader::Use(){
    glUseProgram(progID);
}

// Utility functions for applying uniforms
void Shader::SetBool(const std::string &name, bool value){
    glUniform1i(glGetUniformLocation(progID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string &name, int value){
    glUniform1i(glGetUniformLocation(progID, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, int value){
    glUniform1i(glGetUniformLocation(progID, name.c_str()), value);
}

void Shader::SetVec3(const std::string &name, float x, float y, float z){
    glUniform3f(glGetUniformLocation(progID, name.c_str()), x, y, z);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value){
    glUniform3f(glGetUniformLocation(progID, name.c_str()), value.x, value.y, value.z);
}

void Shader::SetMat3(const std::string &name, const glm::mat3 &mat){
    glUniformMatrix3fv(glGetUniformLocation(progID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &mat){
    glUniformMatrix4fv(glGetUniformLocation(progID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// Check for errors in compiling the shaders
void Shader::CheckCompileErrors(unsigned int shader, std::string type){
    int success;
    char infoLog[1024];
    if(type != "PROGRAM"){
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else{
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}