#include "reflection.h"

Reflection::Reflection(const Vec2d& a):
  a_(a)
{}

Vec2d Reflection::operator()(const Vec2d& x) const {
  return (x - 2*dot(x, a_) / dot(a_, a_) * a_);
}
