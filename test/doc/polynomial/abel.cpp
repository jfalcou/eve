// revision 1
#include <eve/module/polynomial.hpp>
#include <iostream>

int main()
{
  eve::wide wx = {-1.0f, 0.0f, 1.0f, 2.0f};
  eve::wide wa = {0.0f, 1.0f, 2.0f, 3.0f};
  eve::wide wn = {0, 1, 2, 3};

  std::cout << "<- wx                               = " << wx << "\n";
  std::cout << "<- wa                               = " << wa<< "\n";
  std::cout << "<- wn                               = " << wn << "\n";

  std::cout << "-> abel(wn, wx, wa)                 = " << eve::abel(wn, wx, wa) << "\n";
  std::cout << "-> abel(wa, wx, wa)                 = " << eve::abel(wa, wx, wa) << "\n";
  std::cout << "-> abel[ignore_last(2)](wa, wx, wa) = " << eve::abel[eve::ignore_last(2)](wa, wx, wa) << "\n";
  std::cout << "-> abel[wx != 2.0f](wa, wx, wa)     = " << eve::abel[wx != 2.0f](wa, wx, wa) << "\n";
}
