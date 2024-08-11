// revision 1
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide wf = { 0.0f, 0.99f, -1.0f, -0.5f, -0.0f, 0.25f, 1.0f, -2.0f};

  std::cout << "<- wf = " << wf << "\n";

  std::cout << std::setprecision(10);
  std::cout << "-> acospi(wf)                = " << eve::acospi(wf) << "\n";
  std::cout << "-> acospi[raw2](wf)           = " << eve::acospi[eve::raw2](wf) << "\n";
  std::cout << "-> acospi[ignore_last(2)](wf)= " << eve::acospi[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> acospi[wf != -2.0f](wf)   = " << eve::acospi[wf != -2.0f](wf) << "\n";
}
