// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{1.0f, 10.0f, 25.0f, 33.0f, 27.0f, 13.0f, 18.0f, 4.0f};
  unsigned int p = 37;
  std::cout << "p                                "<< p << std::endl;
  std::cout << "wf0                              "<< wf0<< std::endl;
  auto rec = eve::modrec(wf0, p);
  std::cout << "modrec(wf0, p)                   "<< rec << std::endl;
  std::cout << "modmul(wf0, modrec(wf0, p)       "<< eve::modmul(wf0, rec, p) << std::endl;
}
