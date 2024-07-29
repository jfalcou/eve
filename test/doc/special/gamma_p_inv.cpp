// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide wk = {1.0e-3f, 0.3f, 0.75f, 5.5f};
  eve::wide wp = {0.0f,  0.1f, 0.7f, 1.0f};

  std::cout << "<- wk                                 = " << wk << "\n";
  std::cout << "<- wp                                 = " << wp << "\n";

  std::cout << "-> gamma_p_inv(wp, wk)                = " << eve::gamma_p_inv(wp, wk) << "\n";
  std::cout << "-> gamma_p_inv[ignore_last(2)](wp, wk)= " << eve::gamma_p_inv[eve::ignore_last(2)](wp, wk) << "\n";
  std::cout << "-> gamma_p_inv[wp != 0.1f](wp, wk)    = " << eve::gamma_p_inv[wp != 0.1f](wp, wk) << "\n";
}
