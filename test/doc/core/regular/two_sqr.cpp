#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using wf_t = eve::wide<float, eve::fixed<4>>;
  wf_t pf = {3, 2.5, -32.7, eve::eps(eve::as<float>())};
  auto [s, eps] = eve::two_sqr(pf);
  std::cout << "---- simd" << '\n'
            << " <- pf          = " << pf << '\n'
            << " -> {s, eps] = two_sqr(pf)\n"
            << " -> s           = " << s << '\n'
            << " -> eps         = " << eps << '\n';
  return 0;
}
