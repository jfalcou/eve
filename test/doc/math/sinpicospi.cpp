// revision 1
#include <eve/module/math.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});

int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25, -0.5, -2.0};

  std::cout << "<- wf = " << wf << "\n";

  std::cout << "-> sinpicospi(wf)                = " << eve::sinpicospi(wf) << "\n";
  std::cout << "-> sinpicospi[quarter_circle](wf)= " << eve::sinpicospi[eve::quarter_circle](wf) << "\n";
  std::cout << "-> sinpicospi[half_circle](wf)   = " << eve::sinpicospi[eve::half_circle](wf) << "\n";
  std::cout << "-> sinpicospi[full_circle](wf)   = " << eve::sinpicospi[eve::full_circle](wf) << "\n";
}
