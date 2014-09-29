#include "main.h"
class TestPolymerParticle : public Particle {
public:
  PolymerParticle(Vec2d position, 
		  Vec2d velocity, 
		  double density, double pressure, 
		  double temperature, 
		  Material &material):Particle(position, 
					       velocity,
					       density, 
					       pressure,
					       temperature,
					       material){}	
  void ShowV () const;  
};

void TestPolymerParticle::ShowV() const {
  cout << p << endl;
}

int main() {
  /// Creating a material
  Material Ma;
  /// Position vector
  Vec2d u(1, 1);
  /// Velocity vector
  Vec2d v(1, 1); 
  /// Creating a particle
  Particle Pa(u, v, 
	     1.4, 1.0, 1.0, 
	      Ma);

  /// Creating a polymer particle
  TestPolymerParticle PoPa(u, v,
  		       4.0, 5.0, 8.0,
 		       Ma);

  cout << Pa.R() << endl;
  cout << PoPa.R() << endl;
  return 0;  
}
