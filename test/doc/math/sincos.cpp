// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25, -0.5, -2.0};
  wf *= eve::pi[eve::lower](eve::as(wf));

  std::cout << "<- wf = " << wf << "\n";

  std::cout << "-> sincos(wf)                = " << eve::sincos(wf) << "\n";
  std::cout << "-> sincos[quarter_circle](wf)= " << eve::sincos[eve::quarter_circle](wf) << "\n";
  std::cout << "-> sincos[half_circle](wf)   = " << eve::sincos[eve::half_circle](wf) << "\n";
  std::cout << "-> sincos[full_circle](wf)   = " << eve::sincos[eve::full_circle](wf) << "\n";
}
