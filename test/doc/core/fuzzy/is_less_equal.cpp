#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, 2.0f};
  wide_ft qf = {1.0f, -1.0f, 0.0f, 3.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf              = " << pf << '\n'
            << "<- qf              = " << qf << '\n'
            << "-> almost(is_less_equal)(pf, qf) = " << eve::almost(eve::is_less_equal)(pf, qf) << '\n';
  return 0;
}
