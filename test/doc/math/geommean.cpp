// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide pf = {3.0, -1.0, -3.0, 10.0};
  eve::wide qf = {4.0, 1.0, 1.0, 15.0};
  eve::wide rf = {-1.0, 2.0, 3.0, 1.5};
  kumi::tuple wt{pf, qf, rf};

  std::cout << "<- pf                              = " << pf << "\n";
  std::cout << "<- qf                              = " << qf << "\n";
  std::cout << "<- rf                              = " << rf << "\n";
  std::cout << "<- wt                              = " << wt << "\n";

  std::cout << "-> geommean(pf, qf)                = " << eve::geommean(pf, qf) << "\n";
  std::cout << "-> geommean(wt)                    = " << eve::geommean(wt) << "\n";
  std::cout << "-> geommean[ignore_last(2)](pf, qf)= " << eve::geommean[eve::ignore_last(2)](pf, qf) << "\n";
  std::cout << "-> geommean[pf >  0.0](pf, qf)     = " << eve::geommean[pf > 0.0](pf, qf) << "\n";
  std::cout << "-> geommean[pf >  0.0](pf, qf, rf) = " << eve::geommean(pf, qf, rf) << "\n";
}
