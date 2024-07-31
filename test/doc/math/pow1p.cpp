// revision 1
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>


int main()
{
  eve::wide pf = {2.0f, 3.0f, -4.0f, 2.0f, 2.0f,
                  eve::eps(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  eve::wide qf = {4.0f, 1.0f, -1.0f,  0.5f,  0.0f, 2.0f, -3.0f,  2.5f};

  std::cout << std::setprecision(10);
   std::cout << "<- pf                           = " << pf << "\n";
   std::cout << "<- qf                           = " << qf << "\n";

   std::cout << "-> pow1p(pf, qf)                = " << eve::pow1p(pf, qf) << "\n";
   std::cout << "-> pow1p[ignore_last(2)](pf, qf)= " << eve::pow1p[eve::ignore_last(2)](pf, qf) << "\n";
   std::cout << "-> pow1p[qf > 0.0f](pf, qf)     = " << eve::pow1p[qf > 0.0f](pf, qf) << "\n";
   std::cout << "-> pow1p[raw](pf, qf)           = " << eve::pow1p[eve::raw](pf, qf) << "\n";
}
