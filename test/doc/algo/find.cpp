#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>

int main()
{
  std::vector<float> r1{12, 0, 21, 2, 0, -4};

  auto pos   = eve::algo::find_if(r1, eve::is_eqz);
  auto posn  = eve::algo::find_if_not(r1, [](auto x){return x <  20.0; });
  auto pos21 = eve::algo::find(r1, 21.0f);

  std::cout << " <- std::vector<float> r1{12, 0, 21, 2, 0, -4};\n";
  std::cout << " <- *eve::algo::find_if(r1, eve::is_eqz)   = " << *pos     << "\n";
  std::cout << " <- next element                           = " << *(pos+1) << "\n";
  std::cout << " <- previous  element                      = " << *(pos-1) << "\n";

  std::cout << " <- *eve::algo::find_ifnot(r1, [](auto x){return x <  20.0; })   = " << *posn    << "\n";
  std::cout << " <- next element                           = " << *(posn+1) << "\n";
  std::cout << " <- previous  element                      = " << *(posn-1) << "\n";

  std::cout << " <- *eve::algo::find(r1, 21.0f })          = " << *pos21    << "\n";
  std::cout << " <- next element                           = " << *(pos21+1) << "\n";
  std::cout << " <- previous  element                      = " << *(pos21-1) << "\n";
  return 0;
}
