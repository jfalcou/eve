// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25, -0.5, -2.0};
  wf *= 180;

  std::cout << "<- wf = " << wf << "\n";

  std::cout << "-> sind(wf)                = " << eve::sind(wf) << "\n";
  std::cout << "-> sind[ignore_last(2)](wf)= " << eve::sind[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> sind[wf != -2.0f](wf)   = " << eve::sind[wf != -2.0f](wf) << "\n";
  std::cout << "-> sind[quarter_circle](wf)= " << eve::sind[eve::quarter_circle](wf) << "\n";
  std::cout << "-> sind[half_circle](wf)   = " << eve::sind[eve::half_circle](wf) << "\n";
  std::cout << "-> sind[full_circle](wf)   = " << eve::sind[eve::full_circle](wf) << "\n";
}
