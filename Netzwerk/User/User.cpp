#include <string>
#include <vector>
#include "User.h"

user::user()
{
  fill();
}
user::~user()
{

}

void user::fill()
{
  id = 5;
  for(int i = 0; i < integerCount;i++)
  {
    integers[i] = i;
  }
  for(int i = 0; i < boolCount;i++)
  {
    bools[i] = i%2;
  }
  message = "abc";
  for(int i = 0; i<= 19200 * 2;i++){
    BITBild.push_back(i %256);
  }
}
