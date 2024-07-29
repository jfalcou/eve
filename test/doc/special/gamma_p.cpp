// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{

  eve::wide wk = {1.0e-3, 0.3, 0.75, 5.5};
  eve::wide wp = {10.0, 0.5, 20.7, 1.0};

  std::cout << "<- wk                             = " << wk << "\n";
  std::cout << "<- wp                             = " << wp << "\n";

  std::cout << "-> gamma_p(wk, wp)                = " << eve::gamma_p(wk, wp) << "\n";
  std::cout << "-> gamma_p[ignore_last(2)](wk, wp)= " << eve::gamma_p[eve::ignore_last(2)](wk, wp) << "\n";
  std::cout << "-> gamma_p[wk > 0.5](wk, wp)      = " << eve::gamma_p[wk > 0.5](wk, wp) << "\n";
}
