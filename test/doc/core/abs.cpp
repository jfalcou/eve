// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                      = " << wf0 << "\n";
  std::cout << "<- wi0                      = " << wi0 << "\n";
  std::cout << "<- wu0                      = " << wu0 << "\n";
                                            
  std::cout << "-> abs(wf0)                 = " << eve::abs(wf0) << "\n";
  std::cout << "-> abs[ignore_last(2)](wf0) = " << eve::abs[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> abs[wf0 != 0](wf0)       = " << eve::abs[wf0 != 0](wf0) << "\n";
  std::cout << "-> abs(wu0)                 = " << eve::abs(wu0) << "\n";
  std::cout << "-> abs[ignore_last(2)](wu0) = " << eve::abs[eve::ignore_last(2)](wu0) << "\n";
  std::cout << "-> abs[wu0 != 0](wu0)       = " << eve::abs[wu0 != 0](wu0) << "\n";
  std::cout << "-> abs[saturated](wu0)      = " << eve::abs[eve::saturated](wu0) << "\n";
  std::cout << "-> abs(wi0)                 = " << eve::abs(wi0) << "\n";
  std::cout << "-> abs[ignore_last(2)](wi0) = " << eve::abs[eve::ignore_last(2)](wi0) << "\n";
  std::cout << "-> abs[wi0 != 0](wi0)       = " << eve::abs[wi0 != 0](wi0) << "\n";
  std::cout << "-> abs[saturated](wi0)      = " << eve::abs[eve::saturated](wi0) << "\n";
}
