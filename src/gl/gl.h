#ifndef GL_GL_H_
#define GL_GL_H_

namespace gl
{

class Gl
{
public:
    virtual ~Gl() {};

    const GLuint getId() const {
        return this->m_id;
    }

    GLuint& getId() {
        return this->m_id;
    }
private:
    GLuint m_id;
};

}

#endif /* GL_GL_H_ */
