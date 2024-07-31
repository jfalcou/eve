// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25, -0.5, -2.0};

  std::cout << "<- wf                       = " << wf << "\n";

  std::cout << "-> cospi(wf)                = " << eve::cospi(wf) << "\n";
  std::cout << "-> cospi[ignore_last(2)](wf)= " << eve::cospi[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> cospi[wf > 0.0](wf)      = " << eve::cospi[wf > 0.0](wf) << "\n";
  std::cout << "-> cospi[quarter_circle](wf)= " << eve::cospi[eve::quarter_circle](wf) << "\n";
  std::cout << "-> cospi[half_circle](wf)   = " << eve::cospi[eve::half_circle](wf) << "\n";
  std::cout << "-> cospi[full_circle](wf)   = " << eve::cospi[eve::full_circle](wf) << "\n";
}
