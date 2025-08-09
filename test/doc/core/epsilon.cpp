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

  std::cout << "-> epsilon(wf0)                 = " << eve::epsilon(wf0) << "\n";
  std::cout << "-> epsilon[kahan](wf0)          = " << eve::epsilon[eve::kahan](wf0) << "\n";
  std::cout << "-> epsilon[harrisson](wf0)      = " << eve::epsilon[eve::harrisson](wf0) << "\n";
  std::cout << "-> epsilon[ignore_last(2)](wf0) = " << eve::epsilon[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> epsilon[wf0 != 0](wf0)       = " << eve::epsilon[wf0 != 0](wf0) << "\n";
  std::cout << "-> epsilon(wu0)                 = " << eve::epsilon(wu0) << "\n";
  std::cout << "-> epsilon[ignore_last(2)](wu0) = " << eve::epsilon[eve::ignore_last(2)](wu0) << "\n";
  std::cout << "-> epsilon[wu0 != 0](wu0)       = " << eve::epsilon[wu0 != 0](wu0) << "\n";
  std::cout << "-> epsilon(wi0)                 = " << eve::epsilon(wi0) << "\n";
  std::cout << "-> epsilon[ignore_last(2)](wi0) = " << eve::epsilon[eve::ignore_last(2)](wi0) << "\n";
  std::cout << "-> epsilon[wi0 != 0](wi0)       = " << eve::epsilon[wi0 != 0](wi0) << "\n";
    std::cout << eve::epsilon[eve::kahan](wf0)/eve::epsilon(wf0) << std::endl;

}
