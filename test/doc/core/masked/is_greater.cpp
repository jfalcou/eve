#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, 2.0f};
  wide_ft qf = {1.0f, -1.0f, -1.0f, 2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                         = " << pf << '\n'
            << "<- qf                         = " << qf << '\n'
            << "-> is_greater[pf > 0](pf, qf) = " << eve::is_greater[pf > 0](pf, qf) << '\n';
  return 0;
}
