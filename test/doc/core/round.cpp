#include <eve/function/round.hpp>
#include <eve/wide.hpp>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, -1.3f, -1.5f, -1.7f, 2.0f, 2.3f, 2.5f, 2.7f};

  std::cout << "---- simd" << '\n'
            << "<- pf                      = " << pf << '\n'
            << "-> round(pf)               = " << eve::round(pf) << '\n'
            << "-> upward_(round)(pf)      = " << eve::upward_(eve::round)(pf) << '\n'
            << "-> downward_(round)(pf)    = " << eve::downward_(eve::round)(pf) << '\n'
            << "-> to_nearest_(round)(pf)  = " << eve::to_nearest_(eve::round)(pf) << '\n'
            << "-> toward_zero_(round)(pf) = " << eve::toward_zero_(eve::round)(pf) << '\n';

  float xf = -32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                      = " << xf << '\n'
            << "-> round(xf)               = " << eve::round(xf) << '\n'
            << "-> upward_(round)(xf)      = " << eve::upward_(eve::round)(xf) << '\n'
            << "-> downward_(round)(xf)    = " << eve::downward_(eve::round)(xf) << '\n'
            << "-> to_nearest_(round)(xf)  = " << eve::to_nearest_(eve::round)(xf) << '\n'
            << "-> toward_zero_(round)(xf) = " << eve::toward_zero_(eve::round)(xf) << '\n';
  return 0;
}
