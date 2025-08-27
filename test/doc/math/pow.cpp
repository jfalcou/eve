// revision 1
#include <eve/module/math.hpp>
#include <iostream>
#include <cmath>

int main()
{
  eve::wide qf = {0.0f, 3.0f, -4.0f, 2.0f, 2.0f,
                  eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  eve::wide pf = {4.0f, 1.0f, -1.0f,  0.5f,  0.0f, 0.0f, -0.0f,  2.5f};
  eve::wide pd = {4.0, 1.0, 12.0, 24.0,  13.0, 0.0, 96.0,  2.0};


  std::cout << "<- pf                         = " << pf << "\n";
  std::cout << "<- qf                         = " << qf << "\n";

  std::cout << "-> pow(pf, qf)                = " << eve::pow(pf, qf) << "\n";
  std::cout << "-> pow[ignore_last(2)](pf, qf)= " << eve::pow[eve::ignore_last(2)](pf, qf) << "\n";
  std::cout << "-> pow[qf > 0.0f](pf, qf)     = " << eve::pow[qf > 0.0f](pf, qf) << "\n";
  std::cout << "-> pow[raw](pf, qf)           = " << eve::pow[eve::raw](pf, qf) << "\n";
  std::cout << "<- pd                         = " << pd << "\n";
  std::cout << "<- pow([mod = 97](pd, 96.0)   = " << eve::pow[eve::mod = 97](pd, 96.0)<< "  //little Fermat\n";
}
