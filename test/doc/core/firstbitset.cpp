#include <eve/function/firstbitset.hpp>
#include <eve/wide.hpp>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, -1.3f, -1.5f, -1.7f, 2.0f, 2.3f, 2.5f, 2.7f};

  std::cout << "---- simd" << '\n'
            << "<- pf =                   " << pf << '\n'
            << "-> eve::firstbitset(pf) =        " << eve::firstbitset(pf) << '\n';

  float xf = -32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                   " << xf << '\n'
            << "-> eve::firstbitset(xf) =        " << eve::firstbitset(xf) << '\n';
  return 0;
}
