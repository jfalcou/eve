// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25, -0.5, -2.0};
  wf *= 180;

  std::cout << "<- wf = " << wf << "\n";

  std::cout << "-> tand(wf)                = " << eve::tand(wf) << "\n";
  std::cout << "-> tand[ignore_last(2)](wf)= " << eve::tand[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> tand[wf != -2.0f](wf)   = " << eve::tand[wf != -2.0f](wf) << "\n";
  std::cout << "-> tand[quarter_circle](wf)= " << eve::tand[eve::quarter_circle](wf) << "\n";
}
