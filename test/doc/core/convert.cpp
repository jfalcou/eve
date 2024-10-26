// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.4, -1.0, -2.0, -3.0, -4.1};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 700u};

  std::cout << "<- wf0                      = " << wf0 << "\n";
  std::cout << "<- wu0                      = " << wu0 << "\n";

  std::cout << "-> convert(wf0, as<int>())              = " << eve::convert(wf0, eve::as<int>()) << "\n";
  std::cout << "-> convert(wu0, as<char>())             = " << eve::convert(wu0, eve::as<char>()) << "\n";
  std::cout << "-> convert[saturated](wu0, as<char>())  = " << eve::convert[eve::saturated](wu0, eve::as<char>()) << "\n";
}
