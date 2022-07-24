#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <tts/tts.hpp>
#include <iostream>
#include <vector>

int main()
{
  std::vector<int> v{12,0,5,-9,3,-8,2,-5,7,21,2,0,-4};

  std::cout << " -> v                                               = "
            << tts::as_string(v)
            << "\n";

  auto pos   = eve::algo::find_if(v, eve::is_eqz);
  std::cout << " <- eve::algo::find_if(v, eve::is_eqz) - v.begin()  = " << pos - v.begin()   << "\n";

  auto posn  = eve::algo::find_if_not(v, [](auto x){return x < 0; });
  std::cout << " <- eve::algo::find_if_not(v, x < 0) - v.begin()    = " << posn - v.begin()  << "\n";

  auto pos21 = eve::algo::find(v, 5);
  std::cout << " <- eve::algo::find(v, 5) - v.begin()               = " << pos21 - v.begin() << "\n";

  return 0;
}
