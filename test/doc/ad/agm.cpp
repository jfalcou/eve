#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/ad.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include "../test/tts/tts.hpp"


int main()
{

  float x = 11;
  float y = 3;
  using eve::var;
  std::cout << "---- scalar" << '\n'
            << "<- x                                   = " << x << '\n'
            << "<- y                                   = " << y << '\n'
            << "-> average(x, var(y))    = " << eve::average(x, var(y)) << '\n'
            << "-> geommean(x, var(y))   = " << eve::geommean(x, var(y)) << '\n'
            << "-> agm(x, var(y)))       = " << eve::agm(x, var(y)) << '\n'
    ;
  return 0;
}
