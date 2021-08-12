#include <eve/function/fma.hpp>
#include <eve/function/pedantic/fsm.hpp>
#include <eve/function/numeric/fsm.hpp>
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
  wide_t qi = {2, -3, esp1,  vm};
  wide_t pi = {3, -2, esm1,  2 };
  wide_t oi = {-4, 1, -1.0f, vm};

  std::cout << "---- simd" << '\n'
            << " <- oi                                = " << oi << '\n'
            << " <- pi                                = " << pi << '\n'
            << " <- qi                                = " << qi << '\n'
            << " -> pedantic(fsm)(oi, pi, qi)         = " << eve::pedantic(eve::fsm)(oi, pi, qi) << '\n'
            << " -> numeric(fsm)(oi, pi, qi)          = " << eve::numeric(eve::fsm)(oi, pi, qi) << '\n'
            << " -> fsm(oi, pi, qi)                   = " << eve::fsm(oi, pi, qi) << '\n'
            << "\n if the last fsm result ends by '0, inf}', it is because\n"
            << " the system has no simd fsm fsmily intrinsics\n"
            << " or is not configured to use them.\n\n";

  std::cout << "---- scalar" << std::setprecision(10) << '\n'
            << " <- vm                                = " << vm << '\n'
            << " -> pedantic(fsm)(vm, 2.0f, vm)      = " << eve::pedantic(eve::fsm)(vm, 2.0f, vm) << '\n'
            << " -> numeric(fsm)(vm, 2.0f, vm)       = " << eve::numeric(eve::fsm)(vm, 2.0f, vm) << '\n'
            << " -> fsm(vm, 2.0f, vm)                = " << eve::fsm(vm, 2.0f, vm) << '\n'
            << " <- esm1                              = " << esm1 << '\n'
            << " <- esp1                              = " << esp1 << '\n'
            << " -> pedantic(fsm)(-1.0f, esp1, esm1)   = " << eve::pedantic(eve::fsm)(-1.0f, esp1, esm1) << '\n'
            << " -> numeric(fsm)(-1.0f, esp1, esm1)    = " << eve::numeric(eve::fsm)(-1.0f, esp1, esm1)  << '\n'
            << " -> fsm(1.0f, esp1, esm1)            = " << eve::fsm(1.0f, esp1, esm1) << '\n';
  return 0;
}
