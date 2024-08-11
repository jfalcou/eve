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

  std::cout << "-> rec(wf0)                 = " << eve::rec(wf0) << "\n";
  std::cout << "-> rec[ignore_last(2)](wf0) = " << eve::rec[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> rec[wf0 != 0](wf0)       = " << eve::rec[wf0 != 0](wf0) << "\n";
  std::cout << "-> rec[raw2](wf0)            = " << eve::rec[eve::raw2](wf0) << "\n";
  std::cout << "-> rec[pedantic](wf0)       = " << eve::rec[eve::pedantic](wf0) << "\n";
  std::cout << "-> rec(wu0)                 = " << eve::rec(wu0) << "\n";
  std::cout << "-> rec[ignore_last(2)](wu0) = " << eve::rec[eve::ignore_last(2)](wu0) << "\n";
  std::cout << "-> rec[wu0 != 0](wu0)       = " << eve::rec[wu0 != 0](wu0) << "\n";
  std::cout << "-> rec[raw2](wu0)            = " << eve::rec[eve::raw2](wu0) << "\n";
  std::cout << "-> rec[pedantic](wu0)       = " << eve::rec[eve::pedantic](wu0) << "\n";
  std::cout << "-> rec(wi0)                 = " << eve::rec(wi0) << "\n";
  std::cout << "-> rec[ignore_last(2)](wi0) = " << eve::rec[eve::ignore_last(2)](wi0) << "\n";
  std::cout << "-> rec[wi0 != 0](wi0)       = " << eve::rec[wi0 != 0](wi0) << "\n";
  std::cout << "-> rec[raw2](wi0)            = " << eve::rec[eve::raw2](wi0) << "\n";
  std::cout << "-> rec[pedantic](wi0)       = " << eve::rec[eve::pedantic](wi0) << "\n";
}
