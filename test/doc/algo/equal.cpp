#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <iostream>
#include <vector>
#include <tts/tts.hpp>

int main()
{
  std::vector<int>  v = {2,5,-9,3,-8,2,-5,7,-2,3};
  std::vector<int>  w = {-9,3,-8,2,2,5,-5,7,-2,3};

  std::cout << " -> v                       = "
            << tts::as_string(v)
            << "\n";

  std::cout << " -> w                       = "
            << tts::as_string(w)
            << "\n";

  std::cout << " -> eve::algo::equal(v, v)  = " << std::boolalpha << eve::algo::equal(v, v) << "\n";
  std::cout << " -> eve::algo::equal(v, w)  = " << std::boolalpha << eve::algo::equal(v, w) << "\n";

  return 0;
}
