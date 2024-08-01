// revision 1
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wf1{0.0, -4.0, 1.0, -1.0, 2.0, -2.0, 3.0, -3.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wi1{0, -4, 1, -1, 2, -2, 3, -3};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};
  eve::wide wu1{4u, 5u, 6u, 7u, 8u, 1u, 2u, 3u};

  auto nz =  [](auto z){ return eve::if_else(eve::is_eqz(z), eve::one(eve::as(z)), z); };

  std::cout << "<- wf0                           = " << wf0 << "\n";
  std::cout << "<- wf1                           = " << wf1 << "\n";
  std::cout << "<- wi0                           = " << wi0 << "\n";
  std::cout << "<- wi1                           = " << wi1 << "\n";
  std::cout << "<- wu0                           = " << wu0 << "\n";

  std::cout << "-> div(wf0, wf1)                 = " << eve::div(wf0, wf1) << "\n";
  std::cout << "-> div[ignore_last(2)](wf0, wf1) = " << eve::div[eve::ignore_last(2)](wf0, wf1) << "\n";
  std::cout << "-> div[wf0 != 0](wf0, wf1)       = " << eve::div[wf0 != 0](wf0, wf1) << "\n";
  std::cout << "-> div[upward](wf0, wf1)         = " << eve::div[eve::upward](wf0, wf1) << "\n";
  std::cout << "-> div[downward](wf0, wf1)       = " << eve::div[eve::downward](wf0, wf1) << "\n";
  std::cout << "-> div[toward_zero](wf0, wf1)    = " << eve::div[eve::toward_zero](wf0, wf1) << "\n";
  std::cout << "-> div[to_nearest](wf0, wf1)     = " << eve::div[eve::to_nearest](wf0, wf1) << "\n";
  std::cout << "-> div(wi0, nz(wi1))             = " << eve::div(wi0, nz(wi1)) << "\n";
  std::cout << "-> div(wu0, wu1)                 = " << eve::div(wu0, wu1) << "\n";
  std::cout << "-> div[saturated](wi0, wi1)      = " << eve::div[eve::saturated](wi0, wi1) << "\n";
}
