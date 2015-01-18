/// \file hook.h
/// \brief A hook class for particles' preparation

#ifndef SRC_HOOK_HOOK
#define SRC_HOOK_HOOK
#include "src/glbtype.h"
#include <list>

class Initiation;
class Hydrodynamics;

/// Use a hook to change particle velocity and position (for example
/// to setupt Taylor-Green flow)
class Hook {
public: 
  Hook(Initiation& ini, Hydrodynamics& hydro);
  void Filter(std::list<spParticle> particle_list);
  bool UseHook(const double time);
private:
  /// local reference to the Initiation object
  Initiation& ini;

  /// local reference to the Hydrodynamics object
  Hydrodynamics& hydro;
  
  /// if this hook was used
  bool wasUsed; 
};
#endif // SRC_HOOK_HOOK

