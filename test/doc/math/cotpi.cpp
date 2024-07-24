// revision 1
#include <eve/module/math.hpp>
#include <iostream>


int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25, -0.5, -2.0};

  std::cout << "<- wf                       = " << wf << "\n";

  std::cout << "-> cotpi(wf)                = " << eve::cotpi(wf) << "\n";
  std::cout << "-> cotpi[ignore_last(2)](wf)= " << eve::cotpi[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> cotpi[wf > 0.0](wf)      = " << eve::cotpi[wf > 0.0](wf) << "\n";
  std::cout << "-> cotpi[quarter_circle](wf)= " << eve::cotpi[eve::quarter_circle](wf) << "\n";
  std::cout << "-> cotpi[half_circle](wf)   = " << eve::cotpi[eve::half_circle](wf) << "\n";
  std::cout << "-> cotpi[full_circle](wf)   = " << eve::cotpi[eve::full_circle](wf) << "\n";
}
