#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <iostream>
#include <vector>
#include <tts/tts.hpp>

int main()
{
  std::vector<int>  v = {2,5,-9,3,-8,2,-5,7,-2,3};

  std::cout << " -> v                                   = "
            << tts::as_string(v)
            << "\n";

  std::cout << " -> eve::algo::none_of(v, i == 0)       = "
            << std::boolalpha << eve::algo::none_of(v, [](auto i){ return i == 0; })<< "\n";

  std::cout << " -> eve::algo::none_of(v, eve::is_ltz)  = "
            << std::boolalpha << eve::algo::none_of(v, eve::is_ltz)<< "\n";

  return 0;
}
