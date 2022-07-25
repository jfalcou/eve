#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include <tts/tts.hpp>

int main()
{
  std::vector<int>  v = {2,5,-9,  9,  3,-8,2,-5,7,-2,3};
  std::vector<int>  w = {2,5,-9, -9, -9,-8,2,-5,7,-2,3};

  std::cout << " -> v                             = "
            << tts::as_string(v)
            << "\n";

  std::cout << " -> w                             = "
            << tts::as_string(w)
            << "\n";

  auto [vv, ww] = eve::algo::mismatch(v, w);
  std::cout << " <- auto [vv, ww]                 = eve::algo::mismatch(v, ww);\n";
  std::cout << " -> mismatch at " << eve::read(vv) << " != " << eve::read(ww) << std::endl;

  // ignoring sign
  auto [no_sign_vv, no_sign_ww] = eve::algo::mismatch(v, w, [](auto x, auto y) {
    return x == y || x == -y;
  });

  std::cout << " <- auto [no_sign_vv, no_sign_ww] = eve::algo::mismatch(v, w, [](...){ });\n";
  std::cout << " -> mismatch at " << eve::read(no_sign_vv) << " != " << eve::read(no_sign_ww) << std::endl;
}
