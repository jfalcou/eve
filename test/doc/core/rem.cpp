// revision 1
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  auto nz =  [](auto z){ return eve::if_else(eve::is_eqz(z), eve::one(eve::as(z)), z); };

  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wf1{0.0, -4.0, 1.0, -1.0, 2.0, -2.0, 3.0, -3.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wi1{0, -4, 1, -1, 2, -2, 3, -3};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};
  eve::wide wu1{7u, 6u, 5u, 4u, 3u, 2u, 1u, 0u};

  std::cout << "<- wf0                           = " << wf0 << "\n";
  std::cout << "<- wf1                           = " << wf1 << "\n";
  std::cout << "<- wi0                           = " << wi0 << "\n";
  std::cout << "<- wi1                           = " << wi1 << "\n";
  std::cout << "<- wu0                           = " << wu0 << "\n";
  std::cout << "<- wu1                           = " << wu1 << "\n";

  std::cout << "-> rem(wf0, wf1)                 = " << eve::rem(wf0, wf1) << "\n";
  std::cout << "-> rem[ignore_last(2)](wf0, wf1) = " << eve::rem[eve::ignore_last(2)](wf0, wf1) << "\n";
  std::cout << "-> rem[wf0 != 0](wf0, wf1)       = " << eve::rem[wf0 != 0](wf0, wf1) << "\n";
  std::cout << "-> rem[downward](wf0, wf1)       = " << eve::rem[eve::downward](wf0, wf1) << "\n";
  std::cout << "-> rem[upward](wf0, wf1)         = " << eve::rem[eve::upward](wf0, wf1) << "\n";
  std::cout << "-> rem[to_nearest](wf0, wf1)     = " << eve::rem[eve::to_nearest](wf0, wf1) << "\n";
  std::cout << "-> rem[toward_zero](wf0, wf1)    = " << eve::rem[eve::toward_zero](wf0, wf1) << "\n";
  std::cout << "-> rem(wu0, wu1)                 = " << eve::rem(wu0, 2*nz(wu0)) << "\n";
  std::cout << "-> rem[ignore_last(2)](wu0, wu1) = " << eve::rem[eve::ignore_last(2)](wu0, wu1) << "\n";
  std::cout << "-> rem[wu0 != 0](wu0, wu1        = " << eve::rem[wu0 != 0](wu0, wu1) << "\n";
  std::cout << "-> rem(wi0, 2*nz(wi0)            = " << eve::rem(wi0, 2*nz(wi0)) << "\n";
  std::cout << "-> rem[ignore_last(2)](wi0, wi1) = " << eve::rem[eve::ignore_last(2)](wi0, wi1) << "\n";
  std::cout << "-> rem[wi0 != 0](wi0, 2*nz(wi0)  = " << eve::rem[wi0 != 0](wi0, 2*nz(wi0)) << "\n";
}
