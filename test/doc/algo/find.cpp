#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "print.hpp"

int main()
{
  std::vector<int> v{12,0,5,-9,3,-8,2,-5,7,21,2,0,-4};

  std::cout << " -> v                      = ";
  doc_utils::print(v);

  auto pos   = eve::algo::find_if(v, eve::is_eqz);
  std::cout << " <- eve::algo::find_if(v, eve::is_eqz)  = " << *pos   << "\n";

  auto posn  = eve::algo::find_if_not(v, [](auto x){return x < 0; });
  std::cout << " <- eve::algo::find_if_not(v, x <0 )    = " << *posn  << "\n";

  auto pos21 = eve::algo::find(v, 21);
  std::cout << " <- eve::algo::find(v, 21 })            = " << *pos21 << "\n";

  return 0;
}
