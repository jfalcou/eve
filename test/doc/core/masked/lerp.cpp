#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using wf_t = eve::wide<double, eve::fixed<4>>;
  wf_t pf = {3, 2.5, -32.7, 1327.43}, qf = {4.2, 1.5, -100.834, 10.02}, tf = {0, 0.1, -3, 1.0};

  std::cout << "---- simd" << '\n'
            << " <- pf                       = " << pf << '\n'
            << " <- qf                       = " << qf << '\n'
            << " <- tf                       = " << tf << '\n'
            << " -> lerp[pf > 0](pf, qf, tf) = " << eve::lerp[pf > 0](pf, qf, tf) << '\n';
  return 0;
}
