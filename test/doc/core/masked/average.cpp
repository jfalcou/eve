#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <vector>
#include <iostream>


int main()
{
  using w_t = eve::wide<std::uint32_t, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 3}, qi = {4, 1, 1, ~0};

  std::cout << "---- simd" << '\n'
            << " <- pi              = " << pi << '\n'
            << " <- qi              = " << qi << '\n'
            << " -> average[pi > qi](pi, qi) = " << eve::average[pi > qi](pi, qi) << '\n';
  return 0;
}
