#include <eve/function/trunc.hpp>
#include <eve/wide.hpp>


using wide_ft = eve::wide <float, eve::fixed<4>>;
using wide_it = eve::wide <std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};
  wide_it pi = {-1,    2,    -3,    -32768   };

  std::cout
    << "---- simd" << '\n'
    << "<- pf =                            " << pf << '\n'
    << "-> eve::trunc(pf) =                  " << eve::trunc(pf) << '\n'
    << "<- pi =                            " << pi << '\n'
    << "-> eve::trunc(pi) =                  " << eve::trunc(pi) << '\n'; 

  float xf = -32768.0f;
  std::int16_t xi =  -32768;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf =                            " << xf << '\n'
    << "-> eve::trunc(xf) =                  " << eve::trunc(xf) << '\n'
    << "<- xi =                            " << xi << '\n'
    << "-> eve::trunc(xi) =                  " << eve::trunc(xi) << '\n'; 
  return 0;
}
