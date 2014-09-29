#ifndef BOUNDARYSTRUCT_H
#define BOUNDARYSTRUCT_H
#include "glbfunc.h"
#include "vec2d.h"

///the structure to store the boundary conditions data
class BoundaryStruct {
public:
  ///constructor
  ///\param newdR displaysment vector (for periodic boundary conditions)
  explicit BoundaryStruct(const Vec2d& newdR);
  BoundaryStruct();
  ///get two points distance (using periodic boundary conditions)
  virtual Vec2d getDistance(const Vec2d&, const Vec2d&) const;

  ///destructor 
  virtual ~BoundaryStruct();
protected:
  ///vector
  Vec2d dR;  
};

///wall boundary structure
class WallBoundaryStruct : public BoundaryStruct {
};

///periodic boundary structure
class SymmBoundaryStruct : public BoundaryStruct {
};

///frees slip boundary structure
class FreeSlipBoundaryStruct : public BoundaryStruct {
};

///symmetry boundary structure
class PeriodicBoundaryStruct : public BoundaryStruct {
public:
  explicit PeriodicBoundaryStruct(const Vec2d& newdR);
  virtual Vec2d getDistance(const Vec2d&, const Vec2d&) const ;
};


///factory class to create boundary structures
class BoundaryStructFactory {
public:
  ///create boundary structure
  BoundaryStruct* Create(BPosition bp, int bcFlag);
};

#endif
