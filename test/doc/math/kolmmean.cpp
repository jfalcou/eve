// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide pf = {3.0, -1.0, -3.0, 10.0};
  eve::wide qf = {4.0, 1.0, 1.0, 15.0};
  eve::wide rf = {-1.0, 2.0, 3.0, 1.5};
  kumi::tuple wt{pf, qf, rf};
  auto f0 = eve::abs; //l1 mean
  auto rf0 = f0;
  auto f1 = eve::rec[eve::pedantic]; //harmonic
  auto rf1 = f1;
  auto f2 = [](auto x){ return eve::sqr(x); }; // quadratic
  auto rf2 =  [](auto x){ return eve::sqrt(x); };
  std::cout << "<- pf                              = " << pf << "\n";
  std::cout << "<- qf                              = " << qf << "\n";
  std::cout << "<- rf                              = " << rf << "\n";
  std::cout << "<- wt                              = " << wt << "\n";

  std::cout << "-> kolmmean(f0, rf0, pf, qf, rf)   = " << eve::kolmmean(f0, rf0, pf, qf, rf) << " //l1 mean\n";
  std::cout << "-> kolmmean(f0, rf0, wt)           = " << eve::kolmmean(f0, rf0, wt) << "\n";
  std::cout << "-> kolmmean(f1, rf1, pf, qf, rf)   = " << eve::kolmmean(f1, rf1, pf, qf, rf) << " //harmonic mean\n";
  std::cout << "-> kolmmean(f1, rf1, wt)           = " << eve::kolmmean(f1, rf1, wt) << "\n";
  std::cout << "-> kolmmean(f2, rf2, pf, qf, rf)   = " << eve::kolmmean(f2, rf2, pf, qf, rf) << " // quadratic mean\n";
  std::cout << "-> kolmmean(f2, rf2, wt)           = " << eve::kolmmean(f2, rf2, wt) << "\n\n";
}
