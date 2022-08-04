#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <tts/tts.hpp>
#include <iostream>
#include <vector>

int main()
{
  std::vector<int> v{12, 0, 5, -9, 3, 0, 5};

  std::cout << " -> v                                                        = "
            << tts::as_string(v)
            << "\n";

  auto pos   = eve::algo::find_if(v, eve::is_eqz);
  std::cout << " <- eve::algo::find_if(v, eve::is_eqz) - v.begin()           = " << pos - v.begin()   << "\n";

  auto pos_b = eve::algo::find_last_if(v, eve::is_eqz);
  std::cout << " <- eve::algo::find_last_if(v, eve::is_eqz) - v.begin()  = " << pos_b - v.begin()   << "\n";

  auto pos_bn  = eve::algo::find_last_if_not(v, [](auto x){return x < 0; });
  std::cout << " <- eve::algo::find_last_if_not(v, x < 0) - v.begin()    = " << pos_bn - v.begin()  << "\n";

  auto pos_bv = eve::algo::find_last(v, 5);
  std::cout << " <- eve::algo::find_last(v, 5) - v.begin()               = " << pos_bv - v.begin() << "\n";

  return 0;
}
