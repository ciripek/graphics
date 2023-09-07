#include "Mesh.hpp"

Mesh::Mesh() = default;

Mesh::~Mesh() {
  if (inited) {
    glDeleteVertexArrays(1, &vertexArrayObject);
    
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);
  }
}

void Mesh::initBuffers() {
  glGenVertexArrays(1, &vertexArrayObject);
  glGenBuffers(1, &vertexBuffer);
  glGenBuffers(1, &indexBuffer);

  glBindVertexArray(vertexArrayObject);

  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferStorage(GL_ARRAY_BUFFER,
                  static_cast<GLsizeiptr>(sizeof(vertex) * vertices.size()),
                  static_cast<GLvoid*>(vertices.data()), 0);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),
                        reinterpret_cast<GLvoid*>(offsetof(vertex, position)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),
                        reinterpret_cast<GLvoid*>(offsetof(vertex, normal)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex),
                        reinterpret_cast<GLvoid*>(offsetof(vertex, texcoord)));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  glBufferStorage(GL_ELEMENT_ARRAY_BUFFER,
                  static_cast<GLsizeiptr>(sizeof(GLuint) * indices.size()),
                  static_cast<GLvoid*>(indices.data()), 0);

  glBindVertexArray(0);

  inited = true;
}

void Mesh::draw() {
  glBindVertexArray(vertexArrayObject);

  glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()),
                 GL_UNSIGNED_INT, nullptr);

  glBindVertexArray(0);
}