// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{1.0f, 10.0f, 25.0f, 33.0f, 27.0f, 13.0f, 18.0f, 4.0f};
  eve::wide wf1{0.0f, 25.0f, 33.0f, 12.0f, 20.0f, 18.0f, 6.0f,  10.0f};
  unsigned int p = 37;
  std::cout << "p                                "<< p << std::endl;
  std::cout << "wf0                              "<< wf0<< std::endl;
  std::cout << "wf1                              "<< wf1<< std::endl;
  std::cout << "moddiv(wf0, wf1, p)              "<< eve::moddiv(wf0, wf1, p) << std::endl;
}
