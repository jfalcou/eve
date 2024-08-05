// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};

  std::cout << "<- wf0                              = " << wf0 << "\n";
  std::cout << "<- wi0                              = " << wi0 << "\n";
                                                    
  std::cout << "-> is_denormal(wf0)                 = " << eve::is_denormal(wf0) << "\n";
  std::cout << "-> is_denormal[ignore_last(2)](wf0) = " << eve::is_denormal[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> is_denormal[wf0 != 0](wf0)       = " << eve::is_denormal[wf0 != 0](wf0) << "\n";
  std::cout << "-> is_denormal(wi0)                 = " << eve::is_denormal(wi0) << "\n";
}
