#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using wf_t = eve::wide<float, eve::fixed<4>>;
  wf_t pf = {31, 2, 3, 32700}, qf = {4, 8, 16, 100};

  std::cout << "---- simd" << '\n'
            << " <- pf                    = " << pf << '\n'
            << " <- qf                    = " << qf << '\n'
            << " -> div[pf >  qf](pf, qf) = " << eve::div[pf >  qf](pf, qf) << '\n';
  return 0;
}
