// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, 10*eve::mindenormal(eve::as(-4.0))};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                          = " << wf0 << "\n";
  std::cout << "<- wi0                          = " << wi0 << "\n";
  std::cout << "<- wu0                          = " << wu0 << "\n";

  std::cout << "-> sulp(wf0)                 = " << eve::sulp(wf0) << "\n";
  std::cout << "-> sulp[kahan](wf0)          = " << eve::sulp[eve::kahan](wf0) << "\n";
  std::cout << "-> sulp[harrisson](wf0)      = " << eve::sulp[eve::harrisson](wf0) << "\n";
  std::cout << "-> sulp[ignore_last(2)](wf0) = " << eve::sulp[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> sulp[wf0 != 1.0f](wf0)    = " << eve::sulp[wf0 != 1](wf0) << "\n";
  std::cout << "-> sulp(wu0)                 = " << eve::sulp(wu0) << "\n";
  std::cout << "-> sulp[ignore_last(2)](wu0) = " << eve::sulp[eve::ignore_last(2)](wu0) << "\n";
  std::cout << "-> sulp[wu0 != 2](wu0)       = " << eve::sulp[wu0 != 2](wu0) << "\n";
  std::cout << "-> sulp(wi0)                 = " << eve::sulp(wi0) << "\n";
  std::cout << "-> sulp[ignore_last(2)](wi0) = " << eve::sulp[eve::ignore_last(2)](wi0) << "\n";
  std::cout << "-> sulp[wi0 != 3](wi0)       = " << eve::sulp[wi0 != 3](wi0) << "\n";
    std::cout << eve::sulp[eve::kahan](wf0)/eve::sulp(wf0) << std::endl;

}
