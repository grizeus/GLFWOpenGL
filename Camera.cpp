#include "Camera.h"

camera::camera(GLuint shader, const int width, const int height, const glm::vec3& eye_pos, const glm::vec3& center_pos)
{
    m_matrix_id = glGetUniformLocation(shader, "MVP");

    // Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
    float ASPECT_RATIO = static_cast<float>(width) / static_cast<float>(height);
    constexpr float FOV = glm::radians(45.0f);
    constexpr float NEAR = 0.1f;
    constexpr float FAR = 1000.0f;
    glm::mat4 Projection = glm::perspective(FOV, ASPECT_RATIO, NEAR, FAR);

    // Camera matrix
    glm::mat4 View = glm::lookAt(
        eye_pos,
        center_pos,
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    m_mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around
}

camera::~camera()
{ }

void camera::on_render()
{
    glUniformMatrix4fv(m_matrix_id, 1, GL_FALSE, &m_mvp[0][0]);
}
