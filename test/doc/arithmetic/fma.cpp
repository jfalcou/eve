//#include <eve/function/fma.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/function/pedantic/fma.hpp>
#include <eve/function/numeric/fma.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_t = eve::wide<float, eve::fixed<4>>;

int main()
{
  float es  = eve::eps(eve::as<float>());
  float esm1 = es-1.0f;
  float esp1 = es+1.0f;
  float vm  = eve::valmax(eve::as<float>());
  wide_t oi = {2, -3, esp1,  vm};
  wide_t pi = {3, -2, esm1,  2 };
  wide_t qi = {4, -1, 1.0f, -vm};

  std::cout << "---- simd" << '\n'
            << " <- oi                                = " << oi << '\n'
            << " <- pi                                = " << pi << '\n'
            << " <- qi                                = " << qi << '\n'
            << " -> pedantic(fma)(oi, pi, qi)         = " << eve::pedantic(eve::fma)(oi, pi, qi) << '\n'
            << " -> numeric(fma)(oi, pi, qi)          = " << eve::numeric(eve::fma)(oi, pi, qi) << '\n'
             << " -> fma(oi, pi, qi)                   = " << eve::fma(oi, pi, qi) << '\n'
            << "\n if the last fma result ends by '0, inf}', it is because\n"
            << " the system has no simd fma family intrinsics\n"
            << " or is not configured to use them.\n\n";

  std::cout << "---- scalar" << std::setprecision(10) << '\n'
            << " <- vm                                = " << vm << '\n'
            << " -> pedantic(fma)(vm, 2.0f, -vm)      = " << eve::pedantic(eve::fma)(vm, 2.0f, -vm) << '\n'
            << " -> numeric(fma)(vm, 2.0f, -vm)       = " << eve::numeric(eve::fma)(vm, 2.0f, -vm) << '\n'
            << " -> fma(vm, 2.0f, -vm)                = " << eve::fma(vm, 2.0f, -vm) << '\n'
            << " <- esm1                              = " << esm1 << '\n'
            << " <- esp1                              = " << esp1 << '\n'
            << " -> pedantic(fma)(esp1, esm1, 1.0f)   = " << eve::pedantic(eve::fma)(esp1, esm1, 1.0f) << '\n'
            << " -> numeric(fma)(esp1, esm1, 1.0f)    = " << eve::numeric(eve::fma)(esp1, esm1, 1.0f) << '\n'
            << " -> fma(esp1, esm1, -1.0f)            = " << eve::fma(esp1, esm1, 1.0f) << '\n';
  return 0;
}
