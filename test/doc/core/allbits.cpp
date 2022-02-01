#include <eve/module/core/constant/allbits.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

int main()
{
  wide_ft wxf;
  wide_it wxi;

  std::cout << "---- simd" << '\n'
            << "-> allbits(as<wide_ft>())  = " << eve::allbits(eve::as<wide_ft>()) << '\n'
            << "-> allbits(as<wide_it>())  = " << eve::allbits(eve::as<wide_it>()) << '\n'
            << "-> allbits(as(wxf))          = " << eve::allbits(eve::as(wxf))     << '\n'
            << "-> allbits(as(wxi))          = " << eve::allbits(eve::as(wxi))     << '\n';

  float        xf;
  std::int16_t xi;

  std::cout << "---- scalar" << '\n'
            << "-> allbits(as<float>())         = " << eve::allbits(eve::as(float>()) << '\n'
            << "-> allbits(as<std::int16_t>())  = " << eve::allbits(eve::as(std::int16_t>()) << '\n'
            << "-> allbits(as<xf))              = " << eve::allbits(eve::as(xf)) << '\n'
            << "-> allbits(as<xi))              = " << eve::allbits(eve::as(xi)) << '\n';

  return 0;
}
