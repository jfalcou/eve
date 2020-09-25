#include <eve/function/hypot.hpp>
#include <eve/wide.hpp>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};
  wide_ft qf = {-4, 3, -2, -12};

  std::cout << "---- simd" << std::setprecision(10) << '\n'
            << "<- pf                       = " << pf << '\n'
            << "<- qf                       = " << qf << '\n'
            << "-> hypot(pf, qf)            = " << eve::hypot(pf, qf) << '\n'
            << "-> pedantic(hypot)(pf, qf) = " << eve::pedantic(eve::hypot)(pf, qf) << '\n';

  double        xf = -32768.0;
  double        yf = 12.0;

  std::cout << "---- scalar" << '\n'
            << "<- xf                       = " << xf << '\n'
            << "<- yf                       = " << yf << '\n'
            << "-> hypot(xf, yf)            = " << eve::hypot(xf, yf) << '\n'
            << "-> pedantic(hypot)(xf, yf) = " << eve::pedantic(eve::hypot)(xf, yf) << '\n';
  return 0;
}
