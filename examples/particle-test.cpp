#include "main.h"
int main() {
  /// Creating a material
  Material Ma;

  /// Position vector
  Vec2d u(1, 1);

  /// Velocity vector
  Vec2d v(1, 1);
  
  /// Creating a particle
  Particle Pa(u, v, 
	     1.0, 1.0, 1.0, 
	      Ma);
  return 0;
}
