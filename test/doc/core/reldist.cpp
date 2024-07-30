// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wf1{0.0, -4.0, 1.0, -1.0, 2.0, -2.0, 3.0, -3.0};

  std::cout << "<- wf0                               = " << wf0 << "\n";
  std::cout << "<- wf1                               = " << wf1 << "\n";
                                                     
  std::cout << "-> reldist(wf0, wf1)                 = " << eve::reldist(wf0, wf1) << "\n";
  std::cout << "-> reldist[ignore_last(2)](wf0, wf1) = " << eve::reldist[eve::ignore_last(2)](wf0, wf1) << "\n";
  std::cout << "-> reldist[wf0 != 0](wf0, wf1)       = " << eve::reldist[wf0 != 0](wf0, wf1) << "\n";
  std::cout << "-> reldist[pedantic](wf0, wf1)       = " << eve::reldist[eve::pedantic](wf0, wf1) << "\n";
}
