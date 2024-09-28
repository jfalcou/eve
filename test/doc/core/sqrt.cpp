// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                       = " << wf0 << "\n";
  std::cout << "<- wi0                       = " << wi0 << "\n";
  std::cout << "<- wu0                       = " << wu0 << "\n";

  std::cout << "-> sqrt(wf0)                 = " << eve::sqrt(wf0) << "\n";
  std::cout << "-> sqrt[ignore_last(2)](wf0) = " << eve::sqrt[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> sqrt[wf0 != 0](wf0)       = " << eve::sqrt[wf0 != 0](wf0) << "\n";
  std::cout << "-> sqrt[raw](wf0)            = " << eve::sqrt[eve::raw](wf0) << "\n";
  std::cout << "-> sqrt(wu0)                 = " << eve::sqrt(wu0) << "\n";
  std::cout << "-> sqrt[ignore_last(2)](wu0) = " << eve::sqrt[eve::ignore_last(2)](wu0) << "\n";
  std::cout << "-> sqrt[wu0 != 0](wu0)       = " << eve::sqrt[wu0 != 0](wu0) << "\n";
  std::cout << "-> sqrt[raw](wu0)            = " << eve::sqrt[eve::raw](wu0) << "\n";
  std::cout << "-> sqrt(wi0)                 = " << eve::sqrt(wi0) << "\n";
  std::cout << "-> sqrt[ignore_last(2)](wi0) = " << eve::sqrt[eve::ignore_last(2)](wi0) << "\n";
  std::cout << "-> sqrt[wi0 != 0](wi0)       = " << eve::sqrt[wi0 != 0](wi0) << "\n";
  std::cout << "-> sqrt[raw](wi0)            = " << eve::sqrt[eve::raw](wi0) << "\n";
  std::cout << std::setprecision(20) << "-> sqrt(wf0)                = " << eve::sqrt(wf0) << "\n";
  std::cout << std::setprecision(20) << "-> sqrt[lower](wf0)         = " << eve::sqrt[eve::lower](wf0) << "\n";
  std::cout << std::setprecision(20) << "-> sqrt[upper](wf0)         = " << eve::sqrt[eve::upper](wf0) << "\n";
  std::cout << std::setprecision(20) << "-> sqrt[lower][strict](wf0)   = " << eve::sqrt[eve::lower][eve::strict](wf0) << "\n";
  std::cout << std::setprecision(20) << "-> sqrt[upper][strict](wf0)   = " << eve::sqrt[eve::upper][eve::strict](wf0) << "\n";
}
