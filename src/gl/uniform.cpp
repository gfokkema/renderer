#include "uniform.h"

void Uniform::set(glm::mat4& uniform)
{
    glUniformMatrix4fv(this->location, 1, GL_FALSE, &uniform[0][0]);
}

void Uniform::set(Texture& tex)
{
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(this->location, 0);
}
