// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  auto sml = eve::smallestposval(eve::as(1.0));
  eve::wide wf0{sml, -sml, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wf1{0.0, 34.0, 0.0, 72.0, 4.0, 3.0, 2.0, 96.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                      = " << wf0 << "\n";
  std::cout << "<- wf1                      = " << wf1 << "\n";
  std::cout << "<- wi0                      = " << wi0 << "\n";
  std::cout << "<- wu0                      = " << wu0 << "\n";

  std::cout << "-> inc(wf0)                 = " << eve::inc(wf0) << "\n";
  std::cout << "-> inc[ignore_last(2)](wf0) = " << eve::inc[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> inc[wf0 != 0](wf0)       = " << eve::inc[wf0 != 0](wf0) << "\n";
  std::cout << "-> inc(wu0)                 = " << eve::inc(wu0) << "\n";
  std::cout << "-> inc[ignore_last(2)](wu0) = " << eve::inc[eve::ignore_last(2)](wu0) << "\n";
  std::cout << "-> inc[wu0 != 0](wu0)       = " << eve::inc[wu0 != 0](wu0) << "\n";
  std::cout << "-> inc[saturated](wu0)      = " << eve::inc[eve::saturated](wu0) << "\n";
  std::cout << "-> inc(wi0)                 = " << eve::inc(wi0) << "\n";
  std::cout << "-> inc[ignore_last(2)](wi0) = " << eve::inc[eve::ignore_last(2)](wi0) << "\n";
  std::cout << "-> inc[wi0 != 0](wi0)       = " << eve::inc[wi0 != 0](wi0) << "\n";
  std::cout << "-> inc[saturated](wi0)      = " << eve::inc[eve::saturated](wi0) << "\n";
  std::cout << std::setprecision(20) << "-> inc[lower](wf0)         = " << eve::inc[eve::lower](wf0) << "\n";
  std::cout << std::setprecision(20) << "-> inc[upper](wf0)         = " << eve::inc[eve::upper](wf0) << "\n";
  std::cout << std::setprecision(20) << "-> inc[lower][strict](wf0)   = " << eve::inc[eve::lower][eve::strict](wf0) << "\n";
  std::cout << std::setprecision(20) << "-> inc[upper][strict](wf0)   = " << eve::inc[eve::upper][eve::strict](wf0) << "\n";
  std::cout << std::setprecision(20) << "-> inc[mod = 97](wf1)        = " << eve::inc[eve::mod = 97](wf1) << "\n";
}
