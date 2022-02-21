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
  wide_t of = {-4, 1, -1.0f, vm};

  std::cout << "---- simd" << '\n'
            << " <- of                                = " << of << '\n'
            << " <- pf                                = " << pf << '\n'
            << " <- qf                                = " << qf << '\n'
            << " -> pedantic(fsm)(of, pf, qf)         = " << eve::pedantic(eve::fsm)(of, pf, qf) << '\n'
            << " -> numeric(fsm)(of, pf, qf)          = " << eve::numeric(eve::fsm)(of, pf, qf) << '\n'
            << " -> fsm(of, pf, qf)                   = " << eve::fsm(of, pf, qf) << '\n'
            << "\n if the last fsm result ends by '0, inf}', it is because\n"
            << " the system has no simd fsm fsmily intrinsics\n"
            << " or is not configured to use them.\n\n"
            << "-> diff_1st(fam)(of, pf, qf)          = " << eve::diff_1st(eve::fam)(of, pf, qf) << '\n'
            << "-> diff_2nd(fam)(of, pf, qf)          = " << eve::diff_2nd(eve::fam)(of, pf, qf) << '\n'
            << "-> diff_3rd(fam)(of, pf, qf)          = " << eve::diff_3rd(eve::fam)(of, pf, qf) << '\n';

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
