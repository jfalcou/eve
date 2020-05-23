#include <eve/function/iround.hpp>
#include <eve/wide.hpp>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, -1.3f, -1.5f, -1.7f, 2.0f, 2.3f, 2.5f, 2.7f};

  std::cout << "---- simd" << '\n'
            << "<- pf                       = " << pf << '\n'
            << "-> iround(pf)               = " << eve::iround(pf) << '\n'
            << "-> upward_(iround)(pf)      = " << eve::upward_(eve::iround)(pf) << '\n'
            << "-> downward_(iround)(pf)    = " << eve::downward_(eve::iround)(pf) << '\n'
            << "-> to_nearest_(iround)(pf)  = " << eve::to_nearest_(eve::iround)(pf) << '\n'
            << "-> toward_zero_(iround)(pf) = " << eve::toward_zero_(eve::iround)(pf) << '\n';

  float xf = -32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                       = " << xf << '\n'
            << "-> iround(xf)               = " << eve::iround(xf) << '\n'
            << "-> upward_(iround)(xf)      = " << eve::upward_(eve::iround)(xf) << '\n'
            << "-> downward_(iround)(xf)    = " << eve::downward_(eve::iround)(xf) << '\n'
            << "-> to_nearest_(iround)(xf)  = " << eve::to_nearest_(eve::iround)(xf) << '\n'
            << "-> toward_zero_(iround)(xf) = " << eve::toward_zero_(eve::iround)(xf) << '\n';
  return 0;
}
