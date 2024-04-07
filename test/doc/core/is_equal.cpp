#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, eve::nan(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {1.0f, 1.0f, eve::nan(eve::as<float>()), -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                             = " << pf << '\n'
            << "<- qf                             = " << qf << '\n'
            << "-> is_equal(pf, qf)               = " << eve::is_equal(pf, qf) << '\n'
            << "-> numeric(is_equal)(pf, qf)      = " << eve::numeric(eve::is_equal)(pf, qf) << '\n'
            << "-> almost(is_equal)(pf, qf)       = " << eve::almost (eve::is_equal)(pf, qf) << '\n'
            << "-> almost(is_equal)(pf, qf, 2)    = " << eve::almost (eve::is_equal)(pf, qf, 2) << '\n'
            << "-> almost(is_equal)(pf, qf, 2.0f) = " << eve::almost (eve::is_equal)(pf, qf, 2.0f) << '\n';
  return 0;
}
