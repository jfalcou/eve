#include <eve/function/abs.hpp>
#include <eve/function/saturated/abs.hpp>
#include <eve/wide.hpp>


using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {-1, 2, -3, -32768};

  std::cout << "---- simd" << '\n'
            << "<- pi =                         =  " << pi << '\n'
            << "-> eve::abs(pi) =               =  " << eve::abs(pi) << '\n'
            << "-> eve::saturated(eve::abs)(pi) =  " << eve::saturated(eve::abs)(pi) << '\n';

  return 0;
}
