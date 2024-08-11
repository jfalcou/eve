// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide wf0{eve::next(0.0), 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wf1{eve::next(0.0f), 1.0f, 2.0f, 3.0f, -1.0f, -2.0f, -3.0f, -4.0f};

  std::cout << "<- wf0                               = " << wf0 << "\n";
  std::cout << "<- wf1                               = " << wf1 << "\n";

//   std::cout << std::hexfloat << eve::exp2(-53.0)*(1+exp2(-52)) << std::endl;
//   std::cout << std::hexfloat << eve::exp2(-24.0f)*(1+exp2(-23.0f)) << std::endl;
  std::cout << std::setprecision(15);
  std::cout << "-> ulp(wf0)                 = " << eve::ulp(wf0) << "\n";
  std::cout << "-> ulp[upward](wf0)         = " << eve::ulp[eve::upward](wf0) << "\n";
  std::cout << "-> ulp[downward](wf0)       = " << eve::ulp[eve::downward](wf0) << "\n";
  std::cout << "-> epsilon(wf0)             = " << eve::epsilon(wf0) << "\n";

  std::cout << "-> ulp(wf1)                 = " << eve::ulp(wf1) << "\n";
  std::cout << "-> ulp[upward](wf1)         = " << eve::ulp[eve::upward](wf1) << "\n";
  std::cout << "-> ulp[downward](wf1)       = " << eve::ulp[eve::downward](wf1) << "\n";
  std::cout << "-> epsilon(wf1)             = " << eve::epsilon(wf1) << "\n";

  std::cout << "-> ulp[ignore_last(2)](wf0) = " << eve::ulp[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> ulp[wf0 != -2.0f](wf0)   = " << eve::ulp[wf0 != -2.0f](wf0) << "\n";
}
