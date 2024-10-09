// revision 1
#include <eve/module/math.hpp>
#include <iostream>


int main()
{
  eve::wide<float> wf = [](auto i, auto c) { return 2.f*(i-c/2);};

  std::cout << "<- wf = " << wf << "\n";

  std::cout << "-> sinpicospi(wf)                = " << eve::sinpicospi(wf) << "\n";
  std::cout << "-> sinpicospi[quarter_circle](wf)= " << eve::sinpicospi[eve::quarter_circle](wf) << "\n";
}
