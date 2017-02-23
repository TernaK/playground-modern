#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 texCoord;
out vec4 fColor;
out vec2 fTexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model* vec4(position, 1.0);
  fColor = vec4(vColor, 1.0);
  fTexCoord = vec2(texCoord.s, 1.0 - texCoord.t);
}

//
//
//glm::mat4 view, projection, model;
//view = glm::lookAt(glm::vec3(0.0f,0.0f,3.0f), glm::vec3(0,0,0), glm::vec3(0,1,0));
//projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
//model = glm::rotate(model, GLfloat(glfwGetTime()*M_PI), glm::vec3(0.9f, 0.2f, 0.5f));
//glUniformMatrix4fv(glGetUniformLocation(shader.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
//glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
