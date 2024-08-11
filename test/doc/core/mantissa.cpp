// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};

  std::cout << "<- wf0                           = " << wf0 << "\n";
                                                 
  std::cout << "-> mantissa(wf0)                 = " << eve::mantissa(wf0) << "\n";
  std::cout << "-> mantissa[ignore_last(2)](wf0) = " << eve::mantissa[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> mantissa[wf0 != 0](wf0)       = " << eve::mantissa[wf0 != 0](wf0) << "\n";
  std::cout << "-> mantissa[raw](wf0)            = " << eve::mantissa[eve::raw](wf0) << "\n";
}
