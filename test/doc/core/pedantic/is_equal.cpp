#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, eve::nan(as < float>()), eve::nan(as < float>())};
  wide_ft qf = {1.0f, 1.0f, eve::nan(as < float>()), -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                        = " << pf << '\n'
            << "<- qf                        = " << qf << '\n'
            << "-> numeric(is_equal)(pf, qf) = " << eve::numeric(eve::is_equal)(pf, qf) << '\n';

  return 0;
}
