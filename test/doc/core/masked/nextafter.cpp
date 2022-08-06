#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using w_t = eve::wide<float, eve::fixed<4>>;
  w_t pi = {0.0f, 1.0f, 1.0f-eve::eps(eve::as<float>())/2, 1.0f};
  w_t qi = {-1.0f, -2.0f, 3.0f, eve::inf(eve::as<float>())};

  std::cout << "---- simd" << std::setprecision(9) << '\n'
            << " <- pi                         = " << pi << '\n'
            << " <- qi                         = " << qi << '\n'
            << " -> nextafter[pi < qi](pi, qi) = " << eve::nextafter[pi < qi](pi, qi) << '\n';
  return 0;
}
