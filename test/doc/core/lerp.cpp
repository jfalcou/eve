// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wf1{0.0, -4.0, 1.0, -1.0, 2.0, -2.0, 3.0, -3.0};
  eve::wide wf2{0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};

  std::cout << "<- wf0                                 = " << wf0 << "\n";
  std::cout << "<- wf1                                 = " << wf1 << "\n";
  std::cout << "<- wf2                                 = " << wf2 << "\n";
                                                       
  std::cout << "-> lerp(wf0, wf1, wf2)                 = " << eve::lerp(wf0, wf1, wf2) << "\n";
  std::cout << "-> lerp[ignore_last(2)](wf0, wf1, wf2) = " << eve::lerp[eve::ignore_last(2)](wf0, wf1, wf2) << "\n";
  std::cout << "-> lerp[wf0 != 0](wf0, wf1, wf2)       = " << eve::lerp[wf0 != 0](wf0, wf1, wf2) << "\n";
}
