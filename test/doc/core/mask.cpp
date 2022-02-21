#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int32_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {-1, 2, -3, 4};
  wide_ft pf = {-1.0f, -2.0f, -3.0f, -32.0f};

  std::cout << "<- pi =                            " << pi << '\n'
            << "<- pf =                            " << pf << '\n'
            << "-> eve::dec(pi) =                  " << eve::dec(pi) << '\n'
            << "-> (eve::dec[pi > 0])(pi) =        " << (eve::dec[pi > 0])(pi) << '\n'
            << "-> eve::dec(pf) =                  " << eve::dec(pf) << '\n'
            << "-> (eve::dec[pi < 2])(pf) =        " << (eve::dec[pi < 2])(pf) << '\n';
  return 0;
}
