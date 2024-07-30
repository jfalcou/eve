// revision 1
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};

  std::cout << "<- wf0                          = " << wf0 << "\n";
                                                
  std::cout << "-> modf(wf0)                    = " << eve::modf(wf0) << "\n";
/    std::cout << "-> modf[ignore_last(2)](wf0) = " << eve::modf[eve::ignore_last(2)](wf0) << "\n";
/    std::cout << "-> modf[wf0 != 0](wf0)       = " << eve::modf[wf0 != 0](wf0) << "\n";
  std::cout << "-> modf[raw](wf0)               = " << eve::modf[eve::raw](wf0) << "\n";
  std::cout << "-> modf[pedantic](wf0)          = " << eve::modf[eve::pedantic](wf0) << "\n";
  std::cout << "-> modf[almost](wf0)            = " << eve::modf[eve::almost](wf0) << "\n";
}
