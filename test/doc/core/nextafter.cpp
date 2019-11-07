#include <eve/function/nextafter.hpp>
#include <eve/literals.hpp>
#include <eve/wide.hpp>
#include <iomanip>

int main()
{
  using w_t = eve::wide<float, eve::fixed<4>>;
  w_t pf = {3, 2, 3, 3}, qf = {4, 1, 1, 10};

  std::cout << "---- simd" << std::setprecision(12) << '\n'
            << " <- pf =                      " << pf << '\n'
            << " <- qf =                      " << qf << '\n'
            << " -> eve::nextafter(pf, qf) =  " << eve::nextafter(pf, qf) << '\n';

  float  xf = 3.2f, yf = -1.5f;

  std::cout << "---- scalar" << '\n'
            << " xf =                         " << xf << '\n'
            << " yf =                         " << yf << '\n'
            << " -> eve::nextafter(xf, yf) =  " << eve::nextafter(xf, yf) << '\n';
  return 0;
}
