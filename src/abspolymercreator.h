#ifndef ABSPOLYMERCREATOR_H
#define ABSPOLYMERCREATOR_H

//#include "dllist.h"
#include "vec2d.h"
class PolymerInteraction;
class ParticleManager;
class InteractionState;

///basic class for creating polymers
class AbsPolymerCreator {
  ///create polymer
public:
  AbsPolymerCreator();
  ///create polymerin the simulation domain
  virtual void CreatePolymer(const ParticleManager& particles ) = 0;
  ///returns additional polymer interaction force
  virtual Vec2d getForce(const Vec2d& eij, const double& rij) const = 0;

  ///returns the energy of monomers interaction
  virtual double getEnergy(const Vec2d& eij, const double& rij) const =0;
  virtual void showName() const = 0;
  virtual void push_back(PolymerInteraction* newinteraction) = 0;
  //  virtual void outputinteractions() const;
  virtual ~AbsPolymerCreator();
};
#endif
