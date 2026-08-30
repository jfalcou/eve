// revision 0
#include <eve/module/special.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide wf = {0.5, 1.0, 1.5, 2.0, 3.0, 10.0, 0.25, 100.0};

  std::cout << std::setprecision(15);
  std::cout << "<- wf              = " << wf << "\n";
  std::cout << "-> trigamma(wf)    = " << eve::trigamma(wf) << "\n";
  std::cout << "-> trigamma[wf > 1.0](wf) = " << eve::trigamma[wf > 1.0](wf) << "\n";
}
