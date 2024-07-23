// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide pf = { 0.0f, 0.1f, 0.5f, 2.0f};
  eve::wide qf = { 1.0f, 1.0f, 3.0f, 5.0f};
  eve::wide rf = { 4.0f, 2.0f, 1.0f, 0.2f};

  std::cout << "<- pf                                      = " << pf << '\n';
  std::cout << "<- qf                                      = " << qf << '\n';
  std::cout << "<- rf                                      = " << rf << '\n';

  std::cout << "-> betainc_inv(pf, qf, rf)                 = " << eve::betainc_inv(pf, qf, rf) << '\n';
  std::cout << "-> betainc_inv[ignore_last(2)](pf, qf, rf) = " << eve::betainc_inv[eve::ignore_last(2)](pf, qf, rf) << '\n';
  std::cout << "-> betainc_inv[rf != 0.2f](pf, qf, rf)     = " << eve::betainc_inv[rf != 0.2](pf, qf, rf) << '\n';
}
