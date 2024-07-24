// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf{0.0, 200.0, 40.0, -17.0};

  std::cout << "<- wf = " << wf << "\n";

  std::cout << "-> div_180(wf)                = " << eve::div_180(wf) << "\n";
  std::cout << "-> div_180[ignore_last(2)](wf)= " << eve::div_180[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> div_180[wf > 0.0](wf)      = " << eve::div_180[wf > 0.0](wf) << "\n";
}
