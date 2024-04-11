#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, eve::nan(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {1.0f, 1.0f, eve::nan(eve::as<float>()), -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                                 = " << pf << '\n'
            << "<- qf                                 = " << qf << '\n'
            << "-> is_equal(pf, qf)                   = " << eve::is_equal(pf, qf) << '\n'
            << "-> is_equal[eve::numeric](pf, qf)     = " << eve::is_equal[eve::numeric](pf, qf) << '\n'
            << "-> is_equal[almost2](pf, qf)          = " << eve::is_equal[eve::almost2](pf, qf) << '\n'
            << "-> is_equal[almost2 = 2](pf, qf)      = " << eve::is_equal[eve::almost2 = 2](pf, qf) << '\n'
            << "-> is_equal[almost2 = 2.0f](pf, qf)   = " << eve::is_equal[eve::almost2 = 2.0f](pf, qf) << '\n';
  return 0;
}
