#include "particlemanager.h"
#include "hydrodynamics.h"
#include <boost/test/minimal.hpp>
#include <cstdlib>


int test_main( int, char *[] )     {  

  const int number_of_materials = 2;
  const double supportlength = 0.03;
  const Vec2d box_size(2.0, 0.05);
  const double cell_size = 0.05;
  const int x_cells = 40;
  const int y_cells = 1;
  const int initial_condition = 1;
  const int hdelta = 1;
  const double delta = 0.05;

  /// gas dynamics
  const int simu_mode = 2;
  const Vec2d U0_in(0.0, 0.0);

  ParticleManager prtl_mng = ParticleManager(
					     supportlength, box_size, 
					     cell_size, 
					     x_cells, y_cells,
					     initial_condition, hdelta,
					     delta
					     );
  
  

  
  return EXIT_SUCCESS;
}
