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
  wide_t pf = {-2, 3, -esp1,  -vm};
  wide_t qf = {3, -2, esm1,  2 };
  wide_t of = {4, -1, 1.0f, -vm};

  std::cout << "---- simd" << '\n'
            << " <- of                                = " << of << '\n'
            << " <- pf                                = " << pf << '\n'
            << " <- qf                                = " << qf << '\n'
            << " -> of*pf+qf                          = " << of*pf+qf << '\n'
            << " -> fanm[pedantic2](of, pf, qf)         = " << eve::fanm[eve::pedantic2](of, pf, qf) << '\n'
            << " -> fanm(of, pf, qf)                   = " << eve::fanm(of, pf, qf) << '\n'
            << "\n if the previous fanm result ends by '0, inf}', it is because\n"
            << " the system has no simd fanm fanmily intrinsics\n"
            << " or is not configured to use them.\n\n"
            << " -> fanm[pf < qf](of, pf, qf)  = " << eve::fanm[pf < qf](of, pf, qf) << '\n';

  std::cout << "---- scalar" << std::setprecision(10) << '\n'
            << " <- vm                                = " << vm << '\n'
            << " -> fanm[pedantic2](vm, 2.0f, -vm)      = " << eve::fanm[eve::pedantic2](vm, 2.0f, -vm) << '\n'
            << " -> fanm(vm, 2.0f, -vm)                = " << eve::fanm(vm, 2.0f, -vm) << '\n'
            << " <- esm1                              = " << esm1 << '\n'
            << " <- esp1                              = " << esp1 << '\n'
            << " -> fanm[pedantic2](esp1, esm1, 1.0f)   = " << eve::fanm[eve::pedantic2](esp1, esm1, 1.0f) << '\n'
            << " -> fanm(esp1, esm1, -1.0f)            = " << eve::fanm(esp1, esm1, 1.0f) << '\n';
  return 0;
}
