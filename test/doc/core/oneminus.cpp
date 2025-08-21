// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  auto sml = eve::smallestposval(eve::as(1.0));
  eve::wide wf0{sml, -sml, 1.0, -1.0, 2.0, -2.0, 3.0, -3.0};
  eve::wide wf1{0.0, 34.0, 0.0, 72.0, 4.0, 3.0, 2.0, 96.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                           = " << wf0 << "\n";
  std::cout << "<- wf1                      = " << wf1 << "\n";
  std::cout << "<- wi0                           = " << wi0 << "\n";
  std::cout << "<- wu0                           = " << wu0 << "\n";

  std::cout << "-> oneminus(wf0)                 = " << eve::oneminus(wf0) << "\n";
  std::cout << "-> oneminus[ignore_last(2)](wf0) = " << eve::oneminus[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> oneminus[wf0 != 0](wf0)       = " << eve::oneminus[wf0 != 0](wf0) << "\n";
  std::cout << "-> oneminus[saturated ](wf0)     = " << eve::oneminus[eve::saturated ](wf0) << "\n";
  std::cout << "-> oneminus(wu0)                 = " << eve::oneminus(wu0) << "\n";
  std::cout << "-> oneminus(wi0)                 = " << eve::oneminus(wi0) << "\n";
  std::cout << std::setprecision(20) << "-> oneminus[lower](wf0)         = " << eve::oneminus[eve::lower](wf0) << "\n";
  std::cout << std::setprecision(20) << "-> oneminus[upper](wf0)         = " << eve::oneminus[eve::upper](wf0) << "\n";
  std::cout << std::setprecision(20) << "-> oneminus[lower][strict](wf0)   = " << eve::oneminus[eve::lower][eve::strict](wf0) << "\n";
  std::cout << std::setprecision(20) << "-> oneminus[upper][strict](wf0)   = " << eve::oneminus[eve::upper][eve::strict](wf0) << "\n";
  std::cout << std::setprecision(20) << "-> oneminus[mod = 97](wf1)        = " << eve::oneminus[eve::mod = 97](wf1) << "\n";

}
