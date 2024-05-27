#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader {
public:
    unsigned int progID;

    Shader(const char* vertPath, const char* fragPath);

    // Activate the Shaders
    void Use();
    // Utility functions for applying uniforms
    void SetBool(const std::string &name, bool value);
    void SetInt(const std::string &name, int value);
    void SetFloat(const std::string &name, int value);
    void SetVec3(const std::string &name, float x, float y, float z);
    void SetVec3(const std::string &name, const glm::vec3 &value);
    void SetMat3(const std::string &name, const glm::mat3 &mat);
    void SetMat4(const std::string &name, const glm::mat4 &mat);

private:
    void CheckCompileErrors(unsigned int shader, std::string type);
};

#endif // SHADERS_H