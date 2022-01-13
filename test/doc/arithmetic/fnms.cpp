//#include <eve/function/fnms.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/function/pedantic/fnms.hpp>
#include <eve/function/numeric/fnms.hpp>
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
            << " <- oi                                 = " << oi << '\n'
            << " <- pi                                 = " << pi << '\n'
            << " <- qi                                 = " << qi << '\n'
            << " -> pedantic(fnms)(oi, pi, qi)        = " << eve::pedantic(eve::fnms)(oi, pi, qi) << '\n'
            << " -> numeric(fnms)(oi, pi, qi)         = " << eve::numeric(eve::fnms)(oi, pi, qi) << '\n'
            << " -> fnms(oi, pi, qi)                   = " << eve::fnms(oi, pi, qi) << '\n'
            << "\n if the last fnms result ends by '0, -inf}', it means that\n"
            << " the system has no simd fnms family intrinsics\n"
            << " or is not configured to use them.\n\n";

  std::cout << "---- scalar" << std::setprecision(10) << '\n'
            << " <- vm                                = " << vm << '\n'
            << " -> pedantic(fnms)(vm, 2.0f, vm)     = " << eve::pedantic(eve::fnms)(vm, 2.0f, -vm) << '\n'
            << " -> numeric(fnms)(vm, 2.0f, vm)      = " << eve::numeric(eve::fnms)(vm, 2.0f, -vm) << '\n'
            << " -> fnms(vm, 2.0f, vm)                = " << eve::fnms(vm, 2.0f, -vm) << '\n'
            << " <- esm1                              = " << esm1 << '\n'
            << " <- esp1                              = " << esp1 << '\n'
            << " -> pedantic(fnms)(esp1, esm1, 1.0f) = " << eve::pedantic(eve::fnms)(esp1, esm1,1.0f) << '\n'
            << " -> numeric(fnms)(esp1, esm1, 1.0f)  = " << eve::numeric(eve::fnms)(esp1, esm1, 1.0f) << '\n'
            << " -> fnms(esp1, esm1, 1.0f)            = " << eve::fnms(esp1, esm1, 1.0f) << '\n';
  return 0;
}
