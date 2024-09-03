// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -0.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                          = " << wf0 << "\n";

  std::cout << "-> is_nepz(wf0)                 = " << eve::is_nepz(wf0) << "\n";
  std::cout << "-> is_nepz[ignore_last(2)](wf0) = " << eve::is_nepz[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> is_nepz[wf0 != 0](wf0)       = " << eve::is_nepz[wf0 != 0](wf0) << "\n";
}
