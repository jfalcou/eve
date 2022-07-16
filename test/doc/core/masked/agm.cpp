#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <vector>
#include <iostream>


int main()
{
  using wf_t = eve::wide<float, eve::fixed<4>>;
  wf_t pf = {3, 2, 4, 3};
  wf_t qf = {4, 1, 3, eve::inf(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << " <- pf                   = " << pf << '\n'
            << " <- qf                   = " << qf << '\n'
            << " -> agm[pf < qf](pf, qf) = " << eve::agm[pf < qf](pf, qf) << '\n';

  return 0;
}
