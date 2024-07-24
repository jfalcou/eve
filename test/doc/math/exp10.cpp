// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0f, -0.0f, -1.0f, 1.0f, 2.0f,
                  eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "<- wf                       = " << wf << "\n";

  std::cout << "-> exp10(wf)                = " << eve::exp10(wf) << "\n";
  std::cout << "-> exp10[ignore_last(2)](wf)= " << eve::exp10[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> exp10[wf != 2.0f](wf)    = " << eve::exp10[wf != 2.0f](wf) << "\n";
}
