// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide pf = { 0.0f, 1.0f, 4.0f, -2.0f, eve::inf(eve::as<float>()), 0.0f, eve::minf(eve::as<float>()), 1.0f};
  eve::wide qf = { 1.0f, -1.0f, 3.0f, -0.0f, 1.0f, 0.0f, 0.0f, -0.0f};

  std::cout << "<- pf                           = " << pf << "\n";
  std::cout << "<- qf                           = " << qf << "\n";

  std::cout << "-> atan2(pf, qf)                = " << eve::atan2(pf, qf) << "\n";
  std::cout << "-> atan2[pedantic](pf, qf)      = " << eve::atan2[eve::pedantic](pf, qf) << "\n";
  std::cout << "-> atan2[ignore_last(2)](pf, qf)= " << eve::atan2[eve::ignore_last(2)](pf, qf) << "\n";
  std::cout << "-> atan2[pf != -2.0f](pf, qf)   = " << eve::atan2[pf != -2.0f](pf, qf) << "\n";
}
