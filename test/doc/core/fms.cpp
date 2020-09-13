#include <eve/function/fms.hpp>
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
  wide_t qi = {4, -1, -1.0f, vm};

  std::cout << "---- simd" << '\n'
            << " <- oi                                =    " << oi << '\n'
            << " <- pi                                =    " << pi << '\n'
            << " <- qi                                =    " << qi << '\n'
            << " -> pedantic_(fms)(oi, pi, qi)        =    " << eve::pedantic_(eve::fms)(oi, pi, qi) << '\n'
            << " -> numeric_(fms)(oi, pi, qi)         =    " << eve::numeric_(eve::fms)(oi, pi, qi) << '\n'
            << " -> fms(oi, pi, qi)                   =    " << eve::fms(oi, pi, qi) << '\n'
            << "\n if the last fms result ends by '0, inf}', it is because\n"
            << " the system has no simd fms family intrinsics\n"
            << " or is not configured to use them.\n\n";

  std::cout << "---- scalar" << std::setprecision(10) << '\n'
            << " <- vm                                = " << vm << '\n'
            << " -> pedantic_(fms)(vm, 2.0f, vm)      = " << eve::pedantic_(eve::fms)(vm, 2.0f, -vm) << '\n'
            << " -> numeric_(fms)(vm, 2.0f, vm)       = " << eve::numeric_(eve::fms)(vm, 2.0f, -vm) << '\n'
            << " -> fms(vm, 2.0f, vm)                 = " << eve::fms(vm, 2.0f, -vm) << '\n'
            << " <- esm1                              = " << esm1 << '\n'
            << " <- esp1                              = " << esp1 << '\n'
            << " -> pedantic_(fms)(esp1, esm1, -1.0f) = " << eve::pedantic_(eve::fms)(esp1, esm1, -1.0f) << '\n'
            << " -> numeric_(fms)(esp1, esm1, -1.0f)  = " << eve::numeric_(eve::fms)(esp1, esm1, -1.0f) << '\n'
            << " -> fms(esp1, esm1, -1.0f)            = " << eve::fms(esp1, esm1, -1.0f) << '\n';
  return 0;
}
