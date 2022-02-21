#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

int main()
{
  wide_ft wxf;
  wide_it wxi;

  std::cout << "---- simd" << '\n'
            << "-> bitincrement(as<wide_ft>())  = " << eve::bitincrement(eve::as<wide_ft>()) << '\n'
            << "-> bitincrement(as<wide_it>())  = " << eve::bitincrement(eve::as<wide_it>()) << '\n'
            << "-> bitincrement(as(wxf))        = " << eve::bitincrement(eve::as(wxf))     << '\n'
            << "-> bitincrement(as(wxi))        = " << eve::bitincrement(eve::as(wxi))     << '\n';

  double        xf;
  std::int16_t xi;

  std::cout << "---- scalar" << '\n'
            << "-> bitincrement(as<float>())         = " << eve::bitincrement(eve::as(float())) << '\n'
            << "-> bitincrement(as<std::int16_t>())  = " << eve::bitincrement(eve::as(std::int16_t())) << '\n'
            << "-> bitincrement(as<xf))              = " << eve::bitincrement(eve::as(xf)) << '\n'
            << "-> bitincrement(as<xi))              = " << eve::bitincrement(eve::as(xi)) << '\n';

  return 0;
}
