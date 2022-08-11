#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, 0.0f, 367.0f, -1005600.0f, eve::mindenormal(eve::as<double>()),
               eve::inf(eve::as<double>()), eve::minf(eve::as<double>()), eve::nan(eve::as<double>())};

  auto [mp, ep]  = eve::pedantic(eve::frexp)(pf);
  std::cout << "---- simd" << '\n'
            << "-> pedantic(frexp)(pf) = [" << '\n'
            << "                          " << mp << ", \n"
            << "                          " << ep << '\n'
            << "                          ]\n";
  return 0;
}
