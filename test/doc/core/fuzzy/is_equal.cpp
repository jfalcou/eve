#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 1.0f, -1.0f, -2.0f};
  wide_ft qf = {1.0f, -1.0f, -1.0f, -2.0f};
  pf += 3*eve::eps(eve::as<float>());

  std::cout << "---- simd" << '\n'
            << "<- pf                             = " << pf << '\n'
            << "<- qf                             = " << qf << '\n'
            << "-> is_equal)(pf, qf)              = " << eve::is_equal(pf, qf) << '\n'
            << "-> almost(is_equal)(pf, qf)       = " << eve::almost (eve::is_equal)(pf, qf) << '\n'
            << "-> almost(is_equal)(pf, qf, 2)    = " << eve::almost (eve::is_equal)(pf, qf, 2) << '\n'
            << "-> almost(is_equal)(pf, qf, 2.0f) = " << eve::almost (eve::is_equal)(pf, qf, 2.0f) << '\n';
  return 0;
}
