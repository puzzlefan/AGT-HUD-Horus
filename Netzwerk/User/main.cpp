#include <iostream>
#include "User.h"
#include <string>
using namespace std;

//
//  only exists for test purposes
//

int main(int argc, char const *argv[]) {
  user* abc = new user();
  abc->setMessage("ghj");
  std::cout << abc->getMessage() << '\n';
  string bcd = "xyz";
  abc->setMessage(bcd);
  std::cout << bcd << '\n';
  return 0;
}
