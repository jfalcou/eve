#include <eve/function/div.hpp>
#include <eve/wide.hpp>

int main()
{
  using w_t = eve::wide<std::int16_t, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 32700}, qi = {4, 1, 1, 100};

  std::cout << "---- simd" << '\n'
            << " <- pi =          " << pi << '\n'
            << " <- qi =          " << qi << '\n'
            << " -> div(pi, qi) = " << eve::div(pi, qi) << '\n'
            << " -> pi / qi     = " << pi / qi << '\n';

  std::int16_t xi = -32768, yi = -1;

  std::cout << "---- scalar" << '\n'
            << " xi                        = " << xi << '\n'
            << " yi                        = " << yi << '\n'
            << " -> div(xi, yi)            = " << eve::div(xi, yi) << '\n'
            << " -> xi / yi                = " << xi / yi << '\n' // C++ promotion to int
            << " -> std::int16_t( xi / yi) = "<< std::int16_t( xi / yi) << '\n';
  return 0;
}
