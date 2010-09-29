#include <boost/test/minimal.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "cpptcl/cpptcl.h"
void hello() {
  std::cout << "Hello C++/Tcl!" << std::endl;
}

int test_main( int, char *[] )     {  
  Tcl::interpreter interp; 
  interp.def("hello", hello);

  std::ifstream tclfilename;
  tclfilename.open ("cpptcl_test.tcl");

  interp.eval(tclfilename);
  tclfilename.close();

 const std::string script = "for {set i 0} {$i != $s} {incr i} { hello }";  
 const std::string s = interp.getval("s");
 BOOST_REQUIRE( s == "30");

 double val = interp.getval("val");
 BOOST_REQUIRE( abs(val-42.0)<1e-8);

 val = interp.getat("aux", 1);
 BOOST_REQUIRE( abs(val-1.0)<1e-8);

 val = interp.getat("aux", 2);
 BOOST_REQUIRE( abs(val-2.0)<1e-8);

 try {
   val = interp.getat("aux", 3);
   BOOST_FAIL("there is no index 3 in the arrya");
 } catch (std::runtime_error e) {
   // do nothing 
   std::cerr << "Exeption captured: correct behavior\n";
 }

 bool ios = interp.exist("not_a_val");
 BOOST_REQUIRE( !ios) ;

 ios = interp.exist("aux");
 BOOST_REQUIRE( ios) ;

 ios = interp.exist("s");
 BOOST_REQUIRE( ios) ;

 ios = interp.isproc("NotgetmatNo");
 BOOST_REQUIRE( !ios);

 ios = interp.isproc("aux");
 BOOST_REQUIRE( !ios);

 ios = interp.isproc("getmatNo");
 BOOST_REQUIRE( ios);

 ios = interp.exist("qq");
 BOOST_REQUIRE( !ios) ;
 interp.setdouble("qq", 42.0);
 val = interp.getval("qq");
 BOOST_REQUIRE( abs(val-42.0)<1e-8);


 interp.evalproc("getmatNo");
 const int no=interp.getval("no");
 BOOST_REQUIRE( no == 2) ;

 return EXIT_SUCCESS;
};
