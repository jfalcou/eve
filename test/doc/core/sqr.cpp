// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wf1{0.0, 34.0, 0.0, 72.0, 4.0, 3.0, 2.0, 96.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                      = " << wf0 << "\n";
  std::cout << "<- wf1                      = " << wf1 << "\n";
  std::cout << "<- wi0                      = " << wi0 << "\n";
  std::cout << "<- wu0                      = " << wu0 << "\n";

  std::cout << "-> sqr(wf0)                 = " << eve::sqr(wf0) << "\n";
  std::cout << "-> sqr[ignore_last(2)](wf0) = " << eve::sqr[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> sqr[wf0 != 0](wf0)       = " << eve::sqr[wf0 != 0](wf0) << "\n";
  std::cout << "-> sqr(wu0)                 = " << eve::sqr(wu0) << "\n";
  std::cout << "-> sqr[ignore_last(2)](wu0) = " << eve::sqr[eve::ignore_last(2)](wu0) << "\n";
  std::cout << "-> sqr[wu0 != 0](wu0)       = " << eve::sqr[wu0 != 0](wu0) << "\n";
  std::cout << "-> sqr[saturated](wu0)      = " << eve::sqr[eve::saturated](wu0) << "\n";
  std::cout << "-> sqr(wi0)                 = " << eve::sqr(wi0) << "\n";
  std::cout << "-> sqr[ignore_last(2)](wi0) = " << eve::sqr[eve::ignore_last(2)](wi0) << "\n";
  std::cout << "-> sqr[wi0 != 0](wi0)       = " << eve::sqr[wi0 != 0](wi0) << "\n";
  std::cout << "-> sqr[saturated](wi0)      = " << eve::sqr[eve::saturated](wi0) << "\n";
  std::cout << "-> sqr[mod = 97](wf1)       = " << eve::sqr[eve::mod = 97](wf1) << "\n";
}
