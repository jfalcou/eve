// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide pf = {0.0, 2.0, 3.0, 30.0};
  eve::wide qf = {0.0, 1.0, 1.0, 29.56};
  eve::wide rf = {0.0, 0.5, 10.0,25.35};
  kumi::tuple wt{pf, qf};

  std::cout << "<- pf                                  = " << pf << "\n";
  std::cout << "<- qf                                  = " << qf << "\n";
  std::cout << "<- rf                                  = " << rf << "\n";
  std::cout << "<- wt                                  = " << wt << "\n";

  std::cout << "-> logspace_add(pf, qf)                = " << eve::logspace_add(pf, qf) << "\n";
  std::cout << "-> logspace_add(wt)                    = " << eve::logspace_add(wt) << "\n";
  std::cout << "-> logspace_add[ignore_last(2)](pf, qf)= " << eve::logspace_add[eve::ignore_last(2)](pf, qf) << "\n";
  std::cout << "-> logspace_add[pf != 3.0](pf, qf)     = " << eve::logspace_add[pf != 3.0](pf, qf) << "\n";
  std::cout << "-> logspace_add(pf, qf, rf)            = " << eve::logspace_add(pf, qf, rf) << "\n";
}
