// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using f_t = eve::float16_t;
  constexpr f_t e(eve::eps(eve::as<f_t>()));
  std::cout << "e " <<  float(e) << std::endl;
  constexpr auto ee = 1/e;

  std::cout << "ee " <<  float(ee) << std::endl;
//   constexpr auto ee = eve::rec(eve::eps(eve::as<f_t>()));
//   std::cout << "rec(e) " <<  float(ee) << std::endl;
}
