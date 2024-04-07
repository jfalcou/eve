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
  wide_t pf = {2, -3, esp1,  vm};
  wide_t qf = {3, -2, esm1,  2 };
  wide_t of = {-4, 1, -1.0f, vm};

  std::cout << "---- simd" << '\n'
            << " <- of                                = " << of << '\n'
            << " <- pf                                = " << pf << '\n'
            << " <- qf                                = " << qf << '\n'
            << " -> of*pf+qf                          = " << of*pf+qf << '\n'
            << " -> pedantic(fsm)(of, pf, qf)         = " << eve::pedantic(eve::fsm)(of, pf, qf) << '\n'
            << " -> numeric(fsm)(of, pf, qf)          = " << eve::numeric(eve::fsm)(of, pf, qf) << '\n'
            << " -> fsm(of, pf, qf)                   = " << eve::fsm(of, pf, qf) << '\n'
            << "\n if the previous fsm result ends by '0, inf}', it is because\n"
            << " the system has no simd fsm fsmily intrinsics\n"
            << " or is not configured to use them.\n\n"
            << " -> fsm[pf < qf](of, pf, qf)  = " << eve::fsm[pf < qf](of, pf, qf) << '\n';

  std::cout << "---- scalar" << std::setprecision(10) << '\n'
            << " <- vm                                = " << vm << '\n'
            << " -> pedantic(fsm)(vm, 2.0f, -vm)      = " << eve::pedantic(eve::fsm)(vm, 2.0f, -vm) << '\n'
            << " -> numeric(fsm)(vm, 2.0f, -vm)       = " << eve::numeric(eve::fsm)(vm, 2.0f, -vm) << '\n'
            << " -> fsm(vm, 2.0f, -vm)                = " << eve::fsm(vm, 2.0f, -vm) << '\n'
            << " <- esm1                              = " << esm1 << '\n'
            << " <- esp1                              = " << esp1 << '\n'
            << " -> pedantic(fsm)(esp1, esm1, 1.0f)   = " << eve::pedantic(eve::fsm)(esp1, esm1, 1.0f) << '\n'
            << " -> numeric(fsm)(esp1, esm1, 1.0f)    = " << eve::numeric(eve::fsm)(esp1, esm1, 1.0f) << '\n'
            << " -> fsm(esp1, esm1, -1.0f)            = " << eve::fsm(esp1, esm1, 1.0f) << '\n';
  return 0;
}
