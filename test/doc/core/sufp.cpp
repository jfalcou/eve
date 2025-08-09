// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 10.0, 100.0, -1.0e8, -2.0e5, -30.0, 10*eve::mindenormal(eve::as(-4.0))};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << std::hexfloat << "<- wf0                          = " << wf0 << "\n";
  std::cout << "<- wi0                          = " << wi0 << "\n";
  std::cout << "<- wu0                          = " << wu0 << "\n";

  std::cout << "-> sufp(wf0)                 = " << eve::sufp(wf0) << "\n";
  std::cout << "-> sufp[kahan](wf0)          = " << eve::sufp[eve::kahan](wf0) << "\n";
  std::cout << "-> sufp[harrisson](wf0)      = " << eve::sufp[eve::harrisson](wf0) << "\n";
  std::cout << "-> sufp[ignore_last(2)](wf0) = " << eve::sufp[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> sufp[wf0 != 1.0f](wf0)    = " << eve::sufp[wf0 != 1](wf0) << "\n";
  std::cout << "-> sufp(wu0)                 = " << eve::sufp(wu0) << "\n";
  std::cout << "-> sufp[ignore_last(2)](wu0) = " << eve::sufp[eve::ignore_last(2)](wu0) << "\n";
  std::cout << "-> sufp[wu0 != 2](wu0)       = " << eve::sufp[wu0 != 2](wu0) << "\n";
  std::cout << "-> sufp(wi0)                 = " << eve::sufp(wi0) << "\n";
  std::cout << "-> sufp[ignore_last(2)](wi0) = " << eve::sufp[eve::ignore_last(2)](wi0) << "\n";
  std::cout << "-> sufp[wi0 != 3](wi0)       = " << eve::sufp[wi0 != 3](wi0) << "\n";
}
