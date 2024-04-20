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
  wide_t qf = {4, -1, 1.0f, -vm};

  std::cout << "---- simd" << '\n'
            << " <- of                                 = " << of << '\n'
            << " <- pf                                 = " << pf << '\n'
            << " <- qf                                 = " << qf << '\n'
            << " -> -of*pf+qf                          = " << -of*pf+qf << '\n'
            << " -> fnms[pedantic](of, pf, qf)         = " <<eve::fnms[eve::pedantic](of, pf, qf) << '\n'
            << " -> fnms(of, pf, qf)                   = " << eve::fnms(of, pf, qf) << '\n'
            << "\n if the previous fnms result ends by '-0, -inf}', it is because\n"
            << " the system has no simd fnms family intrinsics\n"
            << " or is not configured to use them.\n\n"
            << " -> fnms[pf < qf](of, pf, qf)          = " << eve::fnms[pf < qf](of, pf, qf) << '\n';

  std::cout << "---- scalar" << std::setprecision(10) << '\n'
            << " <- vm                                = " << vm << '\n'
            << " -> fnms[pedantic](vm, 2.0f, -vm)      = " <<eve::fnms[eve::pedantic](vm, 2.0f, -vm) << '\n'
            << " -> fnms(vm, 2.0f, -vm)                = " << eve::fnms(vm, 2.0f, -vm) << '\n'
            << " <- esm1                               = " << esm1 << '\n'
            << " <- esp1                               = " << esp1 << '\n'
            << " -> fnms[pedantic](esp1, esm1, 1.0f)   = " <<eve::fnms[eve::pedantic](esp1, esm1, 1.0f) << '\n'
            << " -> fnms(esp1, esm1, -1.0f)            = " << eve::fnms(esp1, esm1, 1.0f) << '\n';
  return 0;
}
