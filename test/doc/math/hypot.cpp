// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide pf = {-1.0, 2.0, -3.0, eve::valmax(eve::as<double>())};
  eve::wide qf = {-4.0, 3.0, -2.0, eve::inf(eve::as<double>())};
  eve::wide rf = {-40.0, 0.03, -2.0, eve::nan(eve::as<double>())};
  kumi::tuple wt{pf, qf};

   std::cout << "<- pf = " << pf << "\n";
   std::cout << "<- qf = " << qf << "\n";
   std::cout << "<- rf = " << rf << "\n";
   std::cout << "<- wt = " << wt << "\n";

   std::cout << "-> hypot(pf,qf)                = " << eve::hypot(pf,qf) << "\n";
   std::cout << "-> hypot(wt)                   = " << eve::hypot(wt) << "\n";
   std::cout << "-> hypot[ignore_last(2)](pf,qf)= " << eve::hypot[eve::ignore_last(2)](pf,qf) << "\n";
   std::cout << "-> hypot[pf > 0.0](pf,qf)      = " << eve::hypot[pf > 0.0](pf,qf) << "\n";
   std::cout << "-> hypot[pedantic](pf,qf)      = " << eve::hypot[eve::pedantic](pf,qf) << "\n";
   std::cout << "-> hypot(pf,qf,rf)             = " << eve::hypot(pf,qf,rf) << "\n";
   std::cout << "-> hypot[pedantic](pf,qf,rf)   = " << eve::hypot[eve::pedantic](pf,qf,rf) << "\n";
}
