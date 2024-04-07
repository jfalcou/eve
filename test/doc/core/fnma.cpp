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
  wide_t of = {-2, 3, -esp1, -vm};
  wide_t pf = {3, -2, esm1,  2 };
  wide_t qf = {4, -1, 1.0f, -vm};

  std::cout << "---- simd" << '\n'
            << " <- of                                = " << of << '\n'
            << " <- pf                                = " << pf << '\n'
            << " <- qf                                = " << qf << '\n'
            << " -> of*pf+qf                          = " << of*pf+qf << '\n'
            << " -> pedantic(fnma)(of, pf, qf)         = " << eve::pedantic(eve::fnma)(of, pf, qf) << '\n'
            << " -> numeric(fnma)(of, pf, qf)          = " << eve::numeric(eve::fnma)(of, pf, qf) << '\n'
            << " -> fnma(of, pf, qf)                   = " << eve::fnma(of, pf, qf) << '\n'
            << "\n if the previous fnma result ends by '0, inf}', it is because\n"
            << " the system has no simd fnma fnmaily intrinsics\n"
            << " or is not configured to use them.\n\n"
            << " -> fnma[pf < qf](of, pf, qf)  = " << eve::fnma[pf < qf](of, pf, qf) << '\n';

  std::cout << "---- scalar" << std::setprecision(10) << '\n'
            << " <- vm                                = " << vm << '\n'
            << " -> pedantic(fnma)(vm, 2.0f, -vm)      = " << eve::pedantic(eve::fnma)(vm, 2.0f, -vm) << '\n'
            << " -> numeric(fnma)(vm, 2.0f, -vm)       = " << eve::numeric(eve::fnma)(vm, 2.0f, -vm) << '\n'
            << " -> fnma(vm, 2.0f, -vm)                = " << eve::fnma(vm, 2.0f, -vm) << '\n'
            << " <- esm1                              = " << esm1 << '\n'
            << " <- esp1                              = " << esp1 << '\n'
            << " -> pedantic(fnma)(esp1, esm1, 1.0f)   = " << eve::pedantic(eve::fnma)(esp1, esm1, 1.0f) << '\n'
            << " -> numeric(fnma)(esp1, esm1, 1.0f)    = " << eve::numeric(eve::fnma)(esp1, esm1, 1.0f) << '\n'
            << " -> fnma(esp1, esm1, -1.0f)            = " << eve::fnma(esp1, esm1, 1.0f) << '\n';
  return 0;
}
