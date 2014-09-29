#ifndef REFLECTION_H
#define REFLECTION_H
#include "vec2d.h"

///reflaction functor
///The functor returns the result 
///of the reflaction in the hyperplane through the origin.
///The function should be initialize by the vector a ortoganal to 
///the hyperplane
class Reflection {
public:
  ///constructor
  ///\par the vector ortoganal to the hyperplane
  explicit Reflection(const Vec2d& a);
  ///operator returns the reflaction vector
  Vec2d operator()(const Vec2d& x) const;
private:
  Vec2d a_;
};
#endif

