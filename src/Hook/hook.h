#ifndef SRC_HOOK_HOOK
#define SRC_HOOK_HOOK
#include "src/glbtype.h"
#include <list>

class Initiation;
class Hook {
public: 
  explicit Hook(const Initiation& ini);
  void Filter(std::list<spParticle> particle_list);
  bool UseHook(const double time);
private:
  /// local reference to the Initiation object
  const Initiation& ini;
  
  /// if this hook was used
  bool wasUsed; 
};
#endif // SRC_HOOK_HOOK

