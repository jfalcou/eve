// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  auto sml = eve::smallestposval(eve::as(1.0));
  eve::wide wf0{sml, -sml, 1.0, -1.0, 2.0, -2.0, 3.0, -3.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                      = " << wf0 << "\n";
  std::cout << "<- wi0                      = " << wi0 << "\n";
  std::cout << "<- wu0                      = " << wu0 << "\n";

  std::cout << "-> dec(wf0)                 = " << eve::dec(wf0) << "\n";
  std::cout << "-> dec[ignore_last(2)](wf0) = " << eve::dec[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> dec[wf0 != 0](wf0)       = " << eve::dec[wf0 != 0](wf0) << "\n";
  std::cout << "-> dec(wu0)                 = " << eve::dec(wu0) << "\n";
  std::cout << "-> dec[ignore_last(2)](wu0) = " << eve::dec[eve::ignore_last(2)](wu0) << "\n";
  std::cout << "-> dec[wu0 != 0](wu0)       = " << eve::dec[wu0 != 0](wu0) << "\n";
  std::cout << "-> dec[saturated](wu0)      = " << eve::dec[eve::saturated](wu0) << "\n";
  std::cout << "-> dec(wi0)                 = " << eve::dec(wi0) << "\n";
  std::cout << "-> dec[ignore_last(2)](wi0) = " << eve::dec[eve::ignore_last(2)](wi0) << "\n";
  std::cout << "-> dec[wi0 != 0](wi0)       = " << eve::dec[wi0 != 0](wi0) << "\n";
  std::cout << "-> dec[saturated](wi0)      = " << eve::dec[eve::saturated](wi0) << "\n";
  std::cout << std::setprecision(20) << "-> dec[lower](wf0)         = " << eve::dec[eve::lower](wf0) << "\n";
  std::cout << std::setprecision(20) << "-> dec[upper](wf0)         = " << eve::dec[eve::upper](wf0) << "\n";
  std::cout << std::setprecision(20) << "-> dec[lower][strict](wf0)   = " << eve::dec[eve::lower][eve::strict](wf0) << "\n";
  std::cout << std::setprecision(20) << "-> dec[upper][strict](wf0)   = " << eve::dec[eve::upper][eve::strict](wf0) << "\n";
}
