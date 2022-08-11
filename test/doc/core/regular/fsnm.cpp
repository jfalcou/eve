#include <eve/module/core.hpp>
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
  wide_t qf = {2, -3, esp1,  vm};
  wide_t pf = {3, -2, esm1,  2 };
  wide_t of = {4, -1, 1.0f, -vm};

  std::cout << "---- simd" << '\n'
            << " <- of                                = " << of << '\n'
            << " <- pf                                = " << pf << '\n'
            << " <- qf                                = " << qf << '\n'
            << " -> pedantic(fsnm)(of, pf, qf)         = " << eve::pedantic(eve::fsnm)(of, pf, qf) << '\n'
            << " -> numeric(fsnm)(of, pf, qf)          = " << eve::numeric(eve::fsnm)(of, pf, qf) << '\n'
            << " -> fsnm(of, pf, qf)                   = " << eve::fsnm(of, pf, qf) << '\n'
            << "\n if the last fsnm result ends by '0, inf}', it is because\n"
            << " the system has no simd fsnm fsnmily intrinsics\n"
            << " or is not configured to use them.\n\n";

  std::cout << "---- scalar" << std::setprecision(10) << '\n'
            << " <- vm                                = " << vm << '\n'
            << " -> pedantic(fsnm)(vm, 2.0f, -vm)      = " << eve::pedantic(eve::fsnm)(vm, 2.0f, -vm) << '\n'
            << " -> numeric(fsnm)(vm, 2.0f, -vm)       = " << eve::numeric(eve::fsnm)(vm, 2.0f, -vm) << '\n'
            << " -> fsnm(vm, 2.0f, -vm)                = " << eve::fsnm(vm, 2.0f, -vm) << '\n'
            << " <- esm1                              = " << esm1 << '\n'
            << " <- esp1                              = " << esp1 << '\n'
            << " -> pedantic(fsnm)(1.0f, esp1, esm1)   = " << eve::pedantic(eve::fsnm)(1.0f, esp1, esm1) << '\n'
            << " -> numeric(fsnm)(1.0f, esp1, esm1)    = " << eve::numeric(eve::fsnm)(1.0f, esp1, esm1)  << '\n'
            << " -> fsnm(-1.0f, esp1, esm1)            = " << eve::fsnm(-1.0f, esp1, esm1) << '\n';
  return 0;
}
