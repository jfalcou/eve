// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide w = {0.0,  -1.0, 1.0, 2.0, 50.0,
                  eve::inf(eve::as<double>()), eve::minf(eve::as<double>()), eve::nan(eve::as<double>())};

  std::cout << "<- w                          = " << w << "\n";

  std::cout << "-> cos_int(w)                 = " << eve::cos_int(w) << "\n";
  std::cout << "-> cos_int[ignore_last(2)](w) = " << eve::cos_int[eve::ignore_last(2)](w) << "\n";
  std::cout << "-> cos_int[w <= 2.0](w)       = " << eve::cos_int[w <= 2.0](w) << "\n";
}
