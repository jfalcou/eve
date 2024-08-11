// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wf1{0.0, -4.0, 1.0, -1.0, 2.0, -2.0, 3.0, -3.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wi1{0, -4, 1, -1, 2, -2, 3, -3};

  std::cout << "<- wf0                               = " << wf0 << "\n";
  std::cout << "<- wf1                               = " << wf1 << "\n";
  std::cout << "<- wi0                               = " << wi0 << "\n";
  std::cout << "<- wi1                               = " << wi1 << "\n";

  std::cout << "-> average(wf0, wf1)                 = " << eve::average(wf0, wf1) << "\n";
  std::cout << "-> average(wi0, wi1)                 = " << eve::average(wi0, wi1) << "\n";
  std::cout << "-> average[ignore_last(2)](wi0, wi1) = " << eve::average[eve::ignore_last(2)](wi0, wi1) << "\n";
  std::cout << "-> average[wi0 != 0](wi0, wi1)       = " << eve::average[wi0 != 0](wi0, wi1) << "\n";
  std::cout << "-> average[raw2](wi0, wi1)            = " << eve::average[eve::raw2](wi0, wi1) << "\n";
  std::cout << "-> average[upward](wi0, wi1)         = " << eve::average[eve::upward](wi0, wi1) << "\n";
  std::cout << "-> average[downward](wi0, wi1)       = " << eve::average[eve::downward](wi0, wi1) << "\n";
}
