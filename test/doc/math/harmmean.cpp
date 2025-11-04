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

  std::cout << "-> harmmean(pf, qf)                = " << eve::harmmean(pf, qf) << "\n";
  std::cout << "-> harmmean(wt)                    = " << eve::harmmean(wt) << "\n";
  std::cout << "-> harmmean[ignore_last(2)](pf, qf)= " << eve::harmmean[eve::ignore_last(2)](pf, qf) << "\n";
  std::cout << "-> harmmean[pf >  0.0](pf, qf)     = " << eve::harmmean[pf > 0.0](pf, qf) << "\n";
  std::cout << "-> harmmean[pf >  0.0](pf, qf, rf) = " << eve::harmmean(pf, qf, rf) << "\n";
  auto tup = kumi::tuple{pf, qf, rf};
  std::cout << "<- tup                             = " << tup  << "\n";
  std::cout << "-> harmmean[kahan](tup)            = " << eve::harmmean[eve::kahan](tup) << "\n";
}
