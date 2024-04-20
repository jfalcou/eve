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
  wide_t of = {2, -3, esp1,  vm};
  wide_t pf = {3, -2, esm1,  2 };
  wide_t qf = {-4, 1, -1.0f, vm};

  std::cout << "---- simd" << '\n'
            << " <- of                                = " << of << '\n'
            << " <- pf                                = " << pf << '\n'
            << " <- qf                                = " << qf << '\n'
            << " -> of*pf+qf                          = " << of*pf+qf << '\n'
            << " -> fms[pedantic](of, pf, qf)         = " <<eve::fms[eve::pedantic](of, pf, qf) << '\n'
            << " -> fms(of, pf, qf)                   = " << eve::fms(of, pf, qf) << '\n'
            << "\n if the previous fms result ends by '0, inf}', it is because\n"
            << " the system has no simd fms family intrinsics\n"
            << " or is not configured to use them.\n\n"
            << " -> fms[pf < qf](of, pf, qf)  = " << eve::fms[pf < qf](of, pf, qf) << '\n';

  std::cout << "---- scalar" << std::setprecision(10) << '\n'
            << " <- vm                                = " << vm << '\n'
            << " -> fms[pedantic](vm, 2.0f, vm)      = " <<eve::fms[eve::pedantic](vm, 2.0f, vm) << '\n'
            << " -> fms(vm, 2.0f, vm)                = " << eve::fms(vm, 2.0f, vm) << '\n'
            << " <- esm1                              = " << esm1 << '\n'
            << " <- esp1                              = " << esp1 << '\n'
            << " -> fms[pedantic](esp1, esm1, 1.0f)   = " <<eve::fms[eve::pedantic](esp1, esm1, 1.0f) << '\n'
            << " -> fms(esp1, esm1, -1.0f)            = " << eve::fms(esp1, esm1, 1.0f) << '\n';
  return 0;
}
