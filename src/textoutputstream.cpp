#include <iostream>
#include <fstream>
#include "textoutputstream.h"
#include "particle.h"
#include "simplecommand.h"
#include "simpleparticlecommand.h"
#include "initiation.h"

extern ostream& operator<< (ostream& ostr, const Particle& prtl);
extern ostream& operator<< (ostream& ostr, const PolymerParticle& prtl);

using namespace std;
TextOutputStream::TextOutputStream():  
  itime_(0),
  iparticle_(0)
{
  ///open output files  
  ///attache time
  Command* co = 
    new SimpleCommand<TextOutputStream>(this,
					   &TextOutputStream::GetTime);

  ///attache a command to the datastream
  AddTimeStepAttribute("t", co);

  
  ///attache particle temperature to the output
//   co = new SimpleParticleCommand('T');
//   AddParticleAttribute("T", co);

  Initiation* ini = Initiation::Instance();
  attrfilename_ = ini->output_dir + "/attr.txt";
  particlefilename_ = ini->output_dir + "/par.txt";

  if (ini->initial_condition == 0) {
    foutTime_.open(attrfilename_.c_str());
    foutPart_.open(particlefilename_.c_str());
  }
}

TextOutputStream::~TextOutputStream() {
}


void TextOutputStream::VisitParticle(Particle* pa) {
  foutPart_ << *pa;    
  WriteAllParticleAttributes(pa);
  foutPart_ << '\n';
}

void TextOutputStream::VisitPolymerParticle(PolymerParticle* polyp) {
  foutPart_ << *polyp;
  WriteAllParticleAttributes(polyp);
  foutPart_ << '\n';
}

void TextOutputStream::VisitInteraction(Interaction* inter) {
}

void TextOutputStream::VisitPolymerInteraction(PolymerInteraction* polyinter) {
}

void TextOutputStream::NewTimeStep() {
#ifdef DEBUG
  cout << "Write new timestep" << endl;
#endif
  ///if the first time step output header to the files
  WriteAllTimeStepAttributes();

  itime_++;  
  iparticle_++;
  foutPart_ << "\n";
  foutTime_ << '\n';

  foutPart_.close();
  foutTime_.close();
  foutTime_.open(attrfilename_.c_str(), 
		 ios::app);
  foutPart_.open(particlefilename_.c_str(), ios::app);
}

void TextOutputStream::WriteTimeStepAttribute(string AttrName, 
					      double AttrValue) {
#ifdef DEBUG
  cout << "Output an attribute" << endl;
#endif  
  foutTime_ << AttrValue << ' ';
}

void TextOutputStream::WriteParticleAttribute(string AttrName, 
						double AttrValue) {
  foutPart_ << ' ' << AttrValue << ' ';
}


void TextOutputStream::Update(Subject* s) {
#ifdef DEBUG
  cout << "Update of TextOutputStream was called" << endl;
#endif  
  ///dont foget to call Update function of OutputStream class
  OutputStream::Update(s);
  NewTimeStep();
}

void TextOutputStream::Initialize() {
  ///header for time attributes file
  Initiation* ini = Initiation::Instance();
  if (ini->initial_condition == 0) {    
#ifdef DEBUG  
    cout << "initialize called" << '\n';
#endif
    foutTime_ << "# ";
    map<const string, Command*>::iterator theIterator;
    for( theIterator = registry_.begin(); 
	 theIterator != registry_.end(); 
       theIterator++ ) {
      string s = theIterator->first;
      foutTime_ << s << ' ';	
    }    
    foutTime_ << '\n';    
    
    ///header for particle attributes file
    foutPart_ << "# ";
    vector<string>::iterator vectorIterator;
    vector<string> hVector = Particle::getHeader();
    for( vectorIterator = hVector.begin(); 
	 vectorIterator != hVector.end(); 
	 vectorIterator++ ) {
      string s = *vectorIterator;
      foutPart_ << s << ' ';
    }    
  
  
    for( theIterator = pAttrRegistry_.begin(); 
	 theIterator != pAttrRegistry_.end(); 
	 theIterator++ ) {
      string s = theIterator->first;
      foutPart_ << s << ' ';	
    }  
    foutPart_ << '\n';
  }
}
