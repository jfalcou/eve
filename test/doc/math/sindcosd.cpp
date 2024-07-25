// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25, -0.5, -2.0};
  wf *= 180;

  std::cout << "<- wf = " << wf << "\n";

  std::cout << "-> sindcosd(wf)                = " << eve::sindcosd(wf) << "\n";
  std::cout << "-> sindcosd[quarter_circle](wf)= " << eve::sindcosd[eve::quarter_circle](wf) << "\n";
}
