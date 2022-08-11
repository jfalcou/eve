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
            << " <- of                        = " << of << '\n'
            << " <- pf                        = " << pf << '\n'
            << " <- qf                        = " << qf << '\n'
            << " -> fnma[pf < qf](of, pf, qf) = " << eve::fnma[pf < qf](of, pf, qf) << '\n';
  return 0;
}
