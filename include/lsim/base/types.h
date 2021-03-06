//
// Created by Ivars Rusbergs in 2021
//
// Collection of commonly used types for library and applications
#ifndef LSIM_TYPES_H_
#define LSIM_TYPES_H_

//#define GLM_FORCE_MESSAGES
//#include <glm/glm.hpp>

namespace lsim {
using F32 = float;
using F64 = double;
using UC = unsigned char;
// Store data that require width and height
template<typename T>
struct Size {
    explicit Size(T w = 0, T h = 0) : width(w), height(h) {};
    T width;
    T height;
};
// GLM linear math types aliasing
/*
using Vec2 = glm::tvec2<F32>;
using Vec3 = glm::tvec3<F32>;
using Vec4 = glm::tvec4<F32>;
using Vec2u16 = glm::tvec2<uint16_t>;
using Vec3u32 = glm::tvec3<uint32_t>;
using Vec2i16 = glm::tvec2<int16_t>;
using Vec2i32 = glm::tvec2<int32_t>;
using Vec3i32 = glm::tvec3<int32_t>;
using Mat3 = glm::tmat3x3<F32>;
using Mat4 = glm::tmat4x4<F32>;
*/
// Type compile-time checks
static_assert(sizeof(F32) == 4);
static_assert(sizeof(F64) == 8);
static_assert(sizeof(UC) == 1);
} // namespace lsim

#endif