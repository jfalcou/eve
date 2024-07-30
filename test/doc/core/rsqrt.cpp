// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};

  std::cout << "<- wf0                        = " << wf0 << "\n";
                                              
  std::cout << "-> rsqrt(wf0)                 = " << eve::rsqrt(wf0) << "\n";
  std::cout << "-> rsqrt[ignore_last(2)](wf0) = " << eve::rsqrt[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> rsqrt[wf0 != 0](wf0)       = " << eve::rsqrt[wf0 != 0](wf0) << "\n";
  std::cout << "-> rsqrt[raw](wf0)            = " << eve::rsqrt[eve::raw](wf0) << "\n";
}
