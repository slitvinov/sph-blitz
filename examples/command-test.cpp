#include <iostream>
#include "main.h"
#include "simplecommand.h"

class TestClass {
public:
  TestClass();
  double show();
};

TestClass::TestClass() {
}

double TestClass::show() {
  cout << "Return 0.0" << endl;
  return 5.6;
}

int main() {
  TestClass* p = new TestClass();
  Command* a = new SimpleCommand<TestClass>(p, &TestClass::show);
  double s = a->Execute();
  cout << "a returns " << s << endl;
  return 0;
}
