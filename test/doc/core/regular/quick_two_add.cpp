#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using wf_t = eve::wide<float, eve::fixed<4>>;
  wf_t pf = {6, 2.5, -320.7, 1.0}, qf = {4.2, 1.5, -100.834, eve::eps(eve::as<float>())/2};
  auto [s, eps] = eve::quick_two_add(pf, qf);
  std::cout << "---- simd" << '\n'
            << " <- pf          = " << pf << '\n'
            << " <- qf          = " << qf << '\n'
            << " -> {s, eps] = quick_two_add(pf, qf)\n"
            << " -> s           = " << s << '\n'
            << " -> eps         = " << eps << '\n';
  return 0;
}
