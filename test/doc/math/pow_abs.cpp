// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide pf = {2.0f, 3.0f, -4.0f, 2.0f, 2.0f,
                  eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  eve::wide qf = {4.0f, 1.0f, -1.0f,  0.5f,  0.0f, 2.0f, -3.0f,  2.5f};

   std::cout << "<- pf                             = " << pf << "\n";
   std::cout << "<- qf                             = " << qf << "\n";

   std::cout << "-> pow_abs(pf, qf)                = " << eve::pow_abs(pf, qf) << "\n";
   std::cout << "-> pow_abs[ignore_last(2)](pf, qf)= " << eve::pow_abs[eve::ignore_last(2)](pf, qf) << "\n";
   std::cout << "-> pow_abs[qf > 0.0f](pf, qf)     = " << eve::pow_abs[qf > 0.0f](pf, qf) << "\n";
   std::cout << "-> pow_abs[raw2](pf, qf)           = " << eve::pow_abs[eve::raw2](pf, qf) << "\n";
}
