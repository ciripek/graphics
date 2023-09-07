#pragma once

#include <GL/glew.h>

#include <array>
#include <tuple>
#include <utility>

#include "enums.hpp"

template <std::pair<BufferType, BufferStorageUsage>... TypeUsage>
class DSABufferStaticArray {
 public:
  DSABufferStaticArray() { glCreateBuffers(size, ids.data()); }

  ~DSABufferStaticArray() { glDeleteBuffers(size, ids.data()); }

  template <size_t N>
  consteval static decltype(auto) get_pair() noexcept {
    return std::get<N>(std::forward_as_tuple(TypeUsage...));
  }

  template <size_t N>
  consteval static decltype(auto) get_type() noexcept {
    return get_pair<N>().first;
  }

  template <size_t N>
  consteval static decltype(auto) get_usage() noexcept {
    return get_pair<N>().second;
  }

  template <size_t index>
  void storage(GLsizeiptr size, const void* data) const {
    glNamedBufferStorage(ids[index], size, data,
                         static_cast<GLbitfield>(get_usage<index>()));
  }

  template <class T, size_t N, size_t index>
  void storage(const std::array<T, N>& data) const {
    storage<index>(ContainerSizeInBytes(data), PointerToStart(data));
  }

  template <class T, size_t index>
  void storage(const std::vector<T>& data) const {
    storage<index>(ContainerSizeInBytes(data), PointerToStart(data));
  }

 private:
  static constexpr std::size_t size = sizeof...(TypeUsage);
  std::array<GLuint, size> ids;
};
