#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class user{
private:
  int id;
  static const int integerCount = 10;
  static const int boolCount = 10;
  int integers[integerCount];
  bool bools[boolCount];
  std::string message;
  std::vector<char> BITBild;
public:
  user();
  ~user();

  void fill();
};

#endif
