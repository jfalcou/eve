// revision 1
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide wf = { 5.0f, 2.0f, -1.0f, -2.0f, -5.0f,  1.001f, -1.0f, 0.0f};

  std::cout << "<- wf                        = " << wf << "\n";

  std::cout << std::setprecision(10);
  std::cout << "-> asecpi(wf)                = " << eve::asecpi(wf) << "\n";
  std::cout << "-> asecpi[raw](wf)           = " << eve::asecpi[eve::raw](wf) << "\n";
  std::cout << "-> asecpi[ignore_last(2)](wf)= " << eve::asecpi[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> asecpi[wf != -2.0f](wf)   = " << eve::asecpi[wf != -2.0f](wf) << "\n";
}
