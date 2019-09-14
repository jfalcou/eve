#include <eve/function/nearest.hpp>
#include <eve/wide.hpp>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.2f, 2.5f, 3.5f, 1.6f};

  std::cout << "---- simd" << '\n'
            << "<- pf =                            " << pf << '\n'
            << "-> eve::nearest(pf) =              " << eve::nearest(pf) << '\n';

  float        xf = -1.3f;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                            " << xf << '\n'
            << "-> eve::nearest(xf) =              " << eve::nearest(xf) << '\n'; 
  return 0;
}
