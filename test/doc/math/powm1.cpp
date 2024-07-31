// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide pf = {2.0f, 3.0f, -4.0f, 2.0f, 2.0f,
                  2.0f, eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  eve::wide qf = {4.0f, 1.0f, -1.0f,  0.5f,  0.0f,
                  eve::eps(eve::as<float>()), -3.0f,  2.5f};

   std::cout << "<- pf                           = " << pf << "\n";
   std::cout << "<- qf                           = " << qf << "\n";

   std::cout << "-> powm1(pf, qf)                = " << eve::powm1(pf, qf) << "\n";
   std::cout << "-> powm1[ignore_last(2)](pf, qf)= " << eve::powm1[eve::ignore_last(2)](pf, qf) << "\n";
   std::cout << "-> powm1[qf > 0.0f](pf, qf)     = " << eve::powm1[qf > 0.0f](pf, qf) << "\n";
   std::cout << "-> powm1[raw](pf, qf)           = " << eve::powm1[eve::raw](pf, qf) << "\n";
}
