// particlemanager.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//      Define 2-d vectors and associated operations
//		particlemanager.cpp
//----------------------------------------------------------------------------------------
// ***** system includes *****
#include <fstream>
#include <glog/logging.h>
#include <boost/foreach.hpp>
#include <boost/smart_ptr/make_shared.hpp>

// ***** local includes *****
#include "particlemanager.h"
#include "hydrodynamics.h"
#include "interaction.h"
#include "initiation.h"
#include "boundary.h"



using namespace std;

//----------------------------------------------------------------------------------------
//									constructor
//----------------------------------------------------------------------------------------
ParticleManager::ParticleManager(const Initiation &ini)
{
  
  ///- copy properties from class Initiation
  supportlength = ini.supportlength;
  supportlengthsquare = supportlength*supportlength;
  box_size = ini.box_size;
  cll_sz = ini.cell_size;
  x_clls = ini.x_cells + 2; y_clls = ini.y_cells + 2;
  initial_condition = ini.initial_condition;
  hdelta = ini.hdelta; delta = ini.delta;

  assert(x_clls > 0);
  assert(y_clls > 0);
  cell_lists.resize(x_clls, y_clls);
  LOG(INFO) << "cell_lists is resized to (" << x_clls << ", " << y_clls << ")";
  LOG(INFO) << "ParticleManager object is created";
}

ParticleManager::ParticleManager(
				 const double supportlength, const Vec2d& box_size, 
				 const double cell_size, 
				 const int x_cells, const int y_cells,
				 const int initial_condition, const int hdelta,
				 const double delta
				 ):
  supportlength(supportlength), 
  supportlengthsquare(supportlength*supportlength),
  box_size(box_size),
  cll_sz(cell_size),
  initial_condition(initial_condition),
  delta(delta),
  hdelta(hdelta),
  x_clls(x_cells+2),
  y_clls(y_cells+2)
{
  cell_lists.resize(x_clls, y_clls);
}

//----------------------------------------------------------------------------------------
//				update the cell linked lists for real particles
//----------------------------------------------------------------------------------------
void ParticleManager::UpdateCellLinkedLists() 
{
	
  //  int i, j; //current cell postions
  //  int k, m; //possible new cell postions

  ///<ul><li>(double) loop (as indices i, j) on all cells
  for(int i = 0; i < x_clls; i++) {
    for(int j = 0; j < y_clls; j++) { 
      ///<ul><li>iterate this cell list
      std::list<spParticle >::iterator p = cell_lists(i,j).begin();
      ///<li>if the list is empty or the node position is at the end <b>!!!Question!!! is this comment right? would it not rather be...if list NOT empty and NOT at the end </b>
      while(p != cell_lists(i,j).end()) {
	///<ul><li>check the position of the real particle
	spParticle prtl = *p;
	if(prtl->bd == 0) {
	  //where is the particle
	  const int k = int ((prtl->R[0] + cll_sz)/ cll_sz);
	  const int m = int ((prtl->R[1] + cll_sz)/ cll_sz);
				
	  ///<ul><li>if the partilce runs out of the current cell
	  if(k != i || m !=j) {
	    ///<ul><li>delete the current node
	      p = cell_lists(i,j).erase(p);
	    ///<li>insert it to the new cell linked list</ul></ul></ul></ul>
	    if(prtl->R[0]>=0.0 &&prtl->R[0]<=cll_sz*x_clls)
	      cell_lists(k,m).insert(cell_lists(k,m).begin(), prtl);
	  } 
	} 
	p++;
      }
    }
  }
}
//----------------------------------------------------------------------------------------
//						do NNP search and build the NNP list
//----------------------------------------------------------------------------------------
std::list<spParticle> ParticleManager::BuildNNP(Vec2d &point)
{
  ///<ul><li>clear the list first
  std::list<spParticle> NNP_list;
  NNP_list.clear();
  
  LOG_EVERY_N(INFO,10000) << "NPP list should now be empty: Size: "<<NNP_list.size() ;
  //where is the point
  const int k = int ((point[0] + cll_sz)/ cll_sz);
  const int m = int ((point[1] + cll_sz)/ cll_sz);

  // if ( point[0]>=0.0 && point[0]<=2.0)//this if- condition has been added for the 1D shock case (as there are no boundary conditions and particles who left the domains should not be considered any more) 
  // {
    ///<li>loop on this and all surrounding cells
    for(int i = k - 1; i <= k + 1; i++) {
      for(int j = m - 1; j <= m + 1; j++) { 
	if(i < x_clls && j < y_clls && i >= 0 && j >= 0) {
	  ///<ul><li>iterate this cell list
	  for (std::list<spParticle >::const_iterator p = cell_lists(i,j).begin(); 
	       p != cell_lists(i,j).end(); 
	       p++) {

	    ///<ul><li>check the position of the particle
	    ///and (if particle is NNP) insert the nearest particle to the list
	    spParticle prtl = *p;
	    const double dstc = v_distance(point, prtl->R);
	    if(dstc < supportlength) {///<li>(line 137)
	      NNP_list.insert(NNP_list.begin(), prtl);
	    }
	  }
	}
      }
    }
    //  }
    // LOG(INFO) << "NPP_list for particle at pos x: "<<point[0];
    //BOOST_FOREACH(spParticle prtl_dest ,NNP_list) {
  // LOG(INFO) << "ParticleManager object is creating particle x:"<<prtl_dest->R[0];
    // }
  return NNP_list;
}

//----------------------------------------------------------------------------------------
//					build the interaction (particle pair) list
//----------------------------------------------------------------------------------------
void ParticleManager::BuildInteraction(std::list<spInteraction> &interactions, 
				       std::list<spParticle > &particle_list, 
				       spKernel weight_function, 
				       const Initiation& ini)
{
  //clear the list first
  interactions.clear();
  ///<ul><li>iterate particles on the particle list
  for (std::list<spParticle >::const_iterator p = particle_list.begin(); 
       p != particle_list.end();
       p++) {
      /// <ul><li> choose origin particle 
      spParticle prtl_org = *p;
      if(prtl_org->bd == 0)
	{
	  ///<li>find out where(in which cell) the particle is
	  const int i = int ((prtl_org->R[0] + cll_sz)/ cll_sz);
	  const int j = int ((prtl_org->R[1] + cll_sz)/ cll_sz);
	  ///<li>loop on this and all surrounding cells
	  for(int k = i - 1; k <= i + 1; k++) 
	    for(int m = j - 1; m <= j + 1; m++) { 
	      ///<ul><li>iterate this cell list
	      for (std::list<spParticle >::const_iterator p1 = cell_lists(k,m).begin(); 
		   p1 != cell_lists(k,m).end();
		   p1++) {
		// destination particle
		spParticle prtl_dest = *p1;
		
		///<ul><li>calculate distance between particle in question 
		///and destination particle (which is iterated)and if 
		///interaction takes place: add pair to inetraction list 
		/// (<b>question: why is dst compared to h^2 and not 
		///support length to determine if there is interaction or not??</b>
		const double dstc = v_sq(prtl_org->R - prtl_dest->R);
		assert(supportlengthsquare>0.0);
		if( (dstc < supportlengthsquare) && (prtl_org->ID > prtl_dest->ID)) {
		  spInteraction pair = 
		    boost::make_shared<Interaction>(prtl_org, prtl_dest, 
						    weight_function, sqrt(dstc),
						    ini);
		  interactions.push_back(pair);

		}
	      }
	    }
	}
  }

  //control output
  LOG(INFO)<<"build interaction (within build pair) done \n";
  ofstream txtFile("BuddiesDataN1");
  if (txtFile.is_open())
    {

      for (std::list<spInteraction>::const_iterator  p = interactions.begin(); 
	   p!=interactions.end();
	   p++)
	{
	  spInteraction inte= *p;

	  txtFile <<setprecision (9)<< ::setw( 7 )<<inte->getOrigin()->ID<<::setw( 7 )<<inte->getDest()->ID<<::setw( 17 )<<inte->get_rij()<<::setw(17 )<<inte->getWij()<<"  "<<inte->getGradWij()[0]<<endl;
	}

      txtFile.close();
    }

}
//----------------------------------------------------------------------------------------
//					build the initial particles and the linked lists
//                                      FOR INCOMPRESSIBLE SIMULATION
//----------------------------------------------------------------------------------------
void ParticleManager::BuildRealParticle(vecMaterial materials, 
					std::list<spParticle >& particle_list, 
					Initiation &ini)
{
	
  LOG(INFO) << "Start BuildRealParticle\n";

  double density, pressure, Temperature;
  int material_no;

  ///initial particles either from .tlc file or from .rst file 
 
      //initialize particles from the file .tlc
      if(initial_condition==0) {	
	//initialize the real particles inside the boundary
        LOG(INFO) << "Run simu_mode = 1, initial_condition = 0 version of BuildRealParticle";
	for(int i = 1; i < x_clls - 1; i++) {
	  for(int j = 1; j < y_clls - 1; j++) {
            LOG(INFO) << "cell (" << i << ", " << j << ")";
	    //create a new real particle
	    for(int k = 0; k < hdelta; k++) {
	      for(int m = 0; m < hdelta; m++) {
                const Vec2d position((i - 1)*cll_sz + (k + 0.5)*delta, 
                                     (j - 1)*cll_sz + (m + 0.5)*delta);
		material_no = 1;
		const Vec2d velocity = ini.U0;
		Temperature = ini.T0;
		density = materials[material_no]->rho0;
		pressure = materials[material_no]->get_p(density);
		const Vec2d c_cntr(4.0, 4.0);
		if(v_abs(position - c_cntr) <= 1.0) {
		  material_no = 2;
		  pressure += ini.p0;
		  density = materials[material_no]->get_rho(pressure);
		}
		//create a new real particle
                LOG_EVERY_N(INFO, 100) << "Create a particle with position: " << position;
		spParticle prtl = boost::make_shared<Particle>(position, velocity, 
							       density, pressure, 
							       Temperature, 
							       materials[material_no]);
		prtl->cell_i = i; prtl->cell_j = j; 
		//insert particle in the particle list
		particle_list.push_back(prtl);
                LOG_EVERY_N(INFO, 100) << "The particle is insertet into the particle list";
		//insert the position into corresponding cell list
		cell_lists(i,j).push_back(prtl);
                LOG_EVERY_N(INFO, 100) << "The particle is inserted into the cell list";
	      } // m loop
	    } // k loop
	  } // j loop
	} // i loop
        LOG(INFO) << "End of  simu_mode = 1, initial_condition = 0 version of BuildRealParticle";
      } /// initial_condition==0 condition
	
      //initialize real particles from the non-dimensional restart file .rst
      if(initial_condition==1) {	
	//the restart file name
	const std::string inputfile = ini.Project_name + ".rst";
	//check if the restart exist
	ifstream fin(inputfile.c_str(), ios::in);
	if (!fin.good()) {
	  LOG(INFO) <<"Initialtion: Cannot open "<< inputfile <<" \n";
	  exit(EXIT_FAILURE);
	}
        
	LOG(INFO) << "Initialtion: Read real particle data from "<< inputfile <<" \n"; 

	//reading the new starting time
	fin>>ini.Start_time;
	//change the starting and ending time
	ini.End_time += ini.Start_time;
	//read the real particle number
        int N;
	fin>>N;
	//read the particle data
	for(int n = 0; n < N; n++) { 
          Vec2d position;
          Vec2d velocity;
          std::string material_name;
	  fin>>material_name>>position[0]>>position[1]>>velocity[0]>>velocity[1]
	     >>density>>pressure>>Temperature;
          assert(density > 0.0);
	  //find the right material number
	  material_no = -1;
	  for(int k = 0;  k <= ini.number_of_materials; k++) 
	    if(material_name == materials[k]->material_name) material_no = k;
	  if(material_no != -1) {	
	    pressure = materials[material_no]->get_p(density);
	    spParticle prtl = boost::make_shared<Particle> ( position, velocity, density, pressure, Temperature, 
					   materials[material_no]);
	    //insert its poistion on the particle list
	    particle_list.insert(particle_list.begin(), prtl);
					
	    //where is the particle
	    const int  i = int (prtl->R[0] / cll_sz) + 1;
	    const int j = int (prtl->R[1] / cll_sz) + 1;
					
	    prtl->cell_i = i; prtl->cell_j = j; 
	    //insert the position into corresponding cell list
	    cell_lists(i,j).insert(cell_lists(i,j).begin(), prtl);

	  } else {
	    LOG(INFO)<<"The material in the restart file is not used by the program! \n";
	    exit(EXIT_FAILURE);
	  }
	}
	fin.close();
	LOG(INFO)<<"Initialtion of Read real particle data from "<< inputfile <<"done! \n"; 
      }
          
  LOG(INFO) << "ParticleManager::BuildRealParticle ends";
}


//----------------------------------------------------------------------------------------
//					build the initial particles and the linked lists
//                                      FOR COMPRESSIBLE SIMULATION
//----------------------------------------------------------------------------------------
void ParticleManager::BuildRealParticleGasDyn(vecMaterial materials, 
					std::list<spParticle >& particle_list, 
					Initiation &ini)
{
	
  LOG(INFO) << "Start BuildRealParticleGasDyn\n";

  double density, pressure, Temperature, mass;
  int material_no;

  ///initial particles either  from .rst file or from .ivs (Initial Values Shock tube)file
 
  const std::string inputfile =std::string(ini.Ivs_file_name);
       material_no = 1; //number for Air (second line in cfg file (->index 1)
      //check if the .ivs file exists
      ifstream fin(inputfile.c_str(), ios::in);
      if (!fin) {
      	LOG(INFO)<<"Initialtion: Cannot open "<< inputfile <<" \n";
      	LOG(INFO) << __FILE__ << ':' << __LINE__ << std::endl;
      	exit(EXIT_FAILURE);
      }
      else LOG(INFO)<<"Initialtion: Read real particle data from "<< inputfile <<" \n"; 
      //read the real particle number
      int N;
      fin>>N;

      // read the particle data
      for(int n = 0; n < N; n++)
	{ 
          Vec2d position;
          Vec2d velocity;
 	 
	  fin>>position[0]>>position[1]>>velocity[0]>>velocity[1]>>density>>pressure>>mass;
	  
	  Temperature=materials[material_no]->get_T(pressure,density);
	  spParticle prtl = boost::make_shared<Particle> ( position, velocity, density, pressure, mass, Temperature, materials[material_no]);
	  //insert its position on the particle list
	  particle_list.insert(particle_list.begin(), prtl);
					
	  //where is the particle
	  const int i = int (prtl->R[0] / cll_sz)+1;//so, a particle at position x=0 is insertet in cell nr. 1 (second cell), as cell nr 0 (first cell reserved forboundary particles)
	  const int j = int (prtl->R[1] / cll_sz)+1;
					
	  prtl->cell_i = i; prtl->cell_j = j; 
	  //insert the position into corresponding cell list
	  cell_lists(i,j).insert(cell_lists(i,j).begin(), prtl);
	  LOG_EVERY_N(INFO,100) << "Particle at position x: "<<prtl->R[0]<<" assigned to cell no (starts at 0 (for boundary particle, 1 is first real particle cell)): "<<prtl->cell_i;
	};
      
      fin.close();
      
   LOG(INFO) << "ParticleManager::BuildRealParticleGasDyn ends";
}



//----------------------------------------------------------------------------------------
//				build the initial wall particles and the linked lists (NOT USED in current code version (method with similar function in boundary class)
//----------------------------------------------------------------------------------------
///\todo{ParticleManager::BuildWallParticle NOT USED in current code version (method with similar function in boundary class, can therefore perhaps be removed!?!}
void ParticleManager::BuildWallParticle(Hydrodynamics &hydro, Boundary &boundary)
{
  ///left hand border (corresponds to the first column)
  if(boundary.xBl == 0) {

    ///<ul><li>iterate over the first colums of all cells that constitute this boundary
    for(int j = 1; j < y_clls - 1; j++) {
      ///<ul><li>create a new wall particle
      for(int k = 0; k < hdelta; k++)
	for(int m = 0; m < hdelta; m++) {
	  spParticle prtl = 
	    boost::make_shared<Particle> ( -1*cll_sz + (k + 0.5)*delta, 
					   (j - 1)*cll_sz + (m + 0.5)*delta, 
					   0.0, 0.0, 
					   hydro.materials[0]);

	  prtl->cell_i = 0; prtl->cell_j = j; 
	  ///<li>insert its position on the particle list
	  hydro.particle_list.insert(hydro.particle_list.begin(), prtl);

	  ///<li>insert the position into corresponding cell list</ul></ul>
	  cell_lists(0,j).insert(cell_lists(0,j).begin(), prtl);

	}
    }
  }
	
  /// right hand border(corresponds to the last column)
  if(boundary.xBr == 0) {

    ///<ul><li>iterate over the last colums of all cells that constitute this boundary
    for(int j = 1; j < y_clls - 1; j++) {
      ///<ul><li>create a new wall particle
      for(int k = 0; k < hdelta; k++)
	for(int m = 0; m < hdelta; m++) {
	  spParticle prtl = 
	    boost::make_shared<Particle> ( (x_clls - 2)*cll_sz + (k + 0.5)*delta, 
					   (j - 1)*cll_sz + (m + 0.5)*delta, 
					   0.0, 0.0, 
					   hydro.materials[0]);

	  prtl->cell_i = x_clls - 1; prtl->cell_j = j; 
	  ///<li>insert its poistion on the particle list
	  hydro.particle_list.insert(hydro.particle_list.begin(), prtl);
	  ///<li>insert the position into corresponding cell list</ul></ul>
	  cell_lists(x_clls - 1,j).insert(cell_lists(x_clls - 1,j).begin(), prtl);
	}
    }
  }

  ///lower border(corresponds to the lowest row)
  if(boundary.yBd == 0) {

    ///<ul><li>iterate over the lowest row of all cells that constitute this boundary
    for(int i = 1; i < x_clls - 1; i++) {
      ///<ul><li>creat a new wall particle
      for(int k = 0; k < hdelta; k++)
	for(int m = 0; m < hdelta; m++) {
	  spParticle prtl = 
	    boost::make_shared<Particle> ( (i - 1)*cll_sz + (k + 0.5)*delta, 
					   -1*cll_sz + (m + 0.5)*delta, 
					   0.0, 0.0, 
					   hydro.materials[0]);

	  prtl->cell_i = i; prtl->cell_j = 0; 
	  ///<li>insert its poistion on the particle list
	  hydro.particle_list.insert(hydro.particle_list.begin(), prtl);

	  ///<li>insert the position into corresponding cell list</ul></ul>
	  cell_lists(i,0).insert(cell_lists(i,0).begin(), prtl);

	}
    }
  }

  ///upper border (corresponds to the last row)
  if(boundary.yBu == 0) {

    ///<ul><li>iterate over the last rows of all cells that constitute this boundary
    for(int i = 1; i < x_clls - 1; i++) {
      ///<ul><li>create a new wall particle
      for(int k = 0; k < hdelta; k++)
	for(int m = 0; m < hdelta; m++) {
	  spParticle prtl = boost::make_shared<Particle>((i - 1)*cll_sz + 
							 (k + 0.5)*delta, 
							 (y_clls - 2)*cll_sz + 
							 (m + 0.5)*delta, 
							 0.0, 0.0,
							 hydro.materials[0]);
	  prtl->cell_i = i; prtl->cell_j = y_clls - 1; 
	  ///<li>insert its poistion on the particle list
	  hydro.particle_list.insert(hydro.particle_list.begin(), prtl);

	  ///<li>insert the position into corresponding cell list</ul></ul>
	  cell_lists(i,y_clls - 1).insert(cell_lists(i,y_clls - 1).begin(), prtl);

	}
    }
  }
}

