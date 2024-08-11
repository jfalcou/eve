// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};

  std::cout << "<- wf0                = " << wf0 << "\n";
                                      
  std::cout << "-> exponent(wf0)      = " << eve::exponent(wf0) << "\n";
  std::cout << "-> exponent[raw](wf0) = " << eve::exponent[eve::raw](wf0) << "\n";
}
