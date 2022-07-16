#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <vector>
#include <iostream>


int main()
{
  using wf_t = eve::wide<float, eve::fixed<4>>;
  wf_t pf = {3, 2, 3, 3};
  wf_t qf = {4, 1, 1, eve::inf(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << " <- pf                = " << pf << '\n'
            << " <- qf                = " << qf << '\n'
            << " -> agm(pf, qf)       = " << eve::agm(pf, qf) << '\n';

  double xi = 3, yi = 4;

  std::cout << "---- scalar" << '\n'
            << " xi                 = " << xi << '\n'
            << " yi                 = " << yi << '\n'
            << " -> agm(xi, yi)     = " << eve::agm(xi, yi) << '\n';
  return 0;
}
