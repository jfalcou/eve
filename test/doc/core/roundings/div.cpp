#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using wf_t = eve::wide<float, eve::fixed<4>>;
  wf_t pf = {3034, 200, 333, 32700}, qf = {4, 7, 13, 100};

  std::cout << "---- simd" << '\n'
            << " <- pf                       = " << pf << '\n'
            << " <- qf                       = " << qf << '\n'
            << " -> toward_zero(div)(pf, qf) =  " << eve::toward_zero(eve::div)(pf, qf) << '\n'
            << " -> downward(div)(pf, qf)    = " << eve::downward(eve::div)(pf, qf) << '\n'
            << " -> upward(div)(pf, qf)      = " << eve::upward(eve::div)(pf, qf) << '\n'
            << " -> to_nearest(div)(pf, qf)  = " << eve::to_nearest(eve::div)(pf, qf) << '\n';
  return 0;
}
