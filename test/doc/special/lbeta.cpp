// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide pf = { 0.0f, 1.0f, 4.0f, 2.0f };
  eve::wide qf = { 1.0f, 1.0f, 3.0f, 5.0f};

  std::cout << "<- pf                           = " << qf << "\n";
  std::cout << "<- qf                           = " << qf << "\n";

  std::cout << "-> lbeta(pf, qf)                = " << eve::lbeta(pf, qf) << "\n";
  std::cout << "-> lbeta[ignore_last(2)](pf, qf)= " << eve::lbeta[eve::ignore_last(2)](pf, qf) << "\n";
  std::cout << "-> lbeta[qf != 3.0f](pf, qf)    = " << eve::lbeta[qf != 3.0f](pf, qf) << "\n";
}
