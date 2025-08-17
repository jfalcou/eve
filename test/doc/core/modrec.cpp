// revision 0
#include <eve/module/core.hpp>
#include <eve/module/combinatorial.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{1.0f, 10.0f, 25.0f, 33.0f, 27.0f, 13.0f, 18.0f, 4.0f};
  unsigned int p = 36;
  std::cout << "p                                "<< p << std::endl;
  std::cout << "wf0                              "<< wf0<< std::endl;
  auto rec = eve::modrec(wf0, p);
  std::cout << "modrec(wf0, p)                   "<< rec << std::endl;
  std::cout << "modmul(wf0, modrec(wf0, p))      "<< eve::modmul(wf0, rec, p) << std::endl;
  std::cout << "gcd(wf0, 36.0f)                  "<< eve::gcd(wf0, 36.0f) << std::endl;
//   std::cout << eve::modrec(eve::wide(23.0f), 37)<<  std::endl;;
//   std::cout << eve::modrec(23.0, 37) <<  std::endl;

}
