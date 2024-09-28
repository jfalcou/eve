// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, 1.0};
  eve::wide wf1{0.0, -4.0, 1.0, -1.0, 2.0, -2.0, -eve::smallestposval(eve::as(1.0)), eve::smallestposval(eve::as(1.0))};
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
  std::cout << "-> average[raw](wi0, wi1)            = " << eve::average[eve::raw](wi0, wi1) << "\n";
  std::cout << "-> average[upper](wi0, wi1)          = " << eve::average[eve::upper](wi0, wi1) << "\n";
  std::cout << "-> average[lower](wi0, wi1)          = " << eve::average[eve::lower](wi0, wi1) << "\n";
  std::cout << std::setprecision(20) << "-> average[upper](wf0, wf1)          = " << eve::average[eve::upper](wf0, wf1) << "\n";
  std::cout << "-> average[lower](wf0, wf1)          = " << eve::average[eve::lower](wf0, wf1) << "\n";
  std::cout << std::setprecision(20) << "-> average[lower][strict](wf0, wf1)   = " << eve::average[eve::lower][eve::strict](wf0, wf1) << "\n";
  std::cout << std::setprecision(20) << "-> average[upper][strict](wf0, wf1)   = " << eve::average[eve::upper][eve::strict](wf0, wf1) << "\n";
}
