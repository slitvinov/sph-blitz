/// \file spParticle.cpp
//#include <cstdlib>
#include <iostream>
//#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
/// example class 
class A {
public: 
  A() {
    std::cerr << "constructor of A\n";
  }
  A(const int n) {
    std::cerr << "constructor of A with n=" << n << " called\n";
  }
  ~A() {
    std::cerr << "destructor of A\n";
  }
  void say() const {
    std::cerr << "(A.say) I am object of A class\n";
  }
};

int main() {
  // crate a shared pointer to an object of A class
  /// call constructor with no arguments
  boost::shared_ptr<A> spa1 = boost::make_shared<A>();
  spa1->say();
  /// call constructor with one arguments
  boost::shared_ptr<A> spa2 = boost::make_shared<A>(42);
  spa2->say();
  // overwrite a pointer 
  spa2 = boost::make_shared<A>();
  // at this point destructor is called 
  // because there are no references to 
  // the object
  spa2->say();
  return EXIT_SUCCESS;
}
