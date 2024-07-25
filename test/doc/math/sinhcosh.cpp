// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25,
                  eve::minf(eve::as<double>()), eve::nan(eve::as<double>())};

  std::cout << "<- wf           = " << wf << "\n";

  std::cout << "-> sinhcosh(wf) = " << eve::sinhcosh(wf) << "\n";
}
