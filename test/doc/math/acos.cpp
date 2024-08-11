// revision 1
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide wf = { 0.0f, 0.99f, -1.0f, -0.5f, -0.0f, 0.25f, 1.0f, -2.0f};

  std::cout << "<- wf                      = " << wf << "\n";

  std::cout << std::setprecision(10);
  std::cout << "-> acos(wf)                = " << eve::acos(wf) << "\n";
  std::cout << "-> acos[raw2](wf)           = " << eve::acos[eve::raw2](wf) << "\n";
  std::cout << "-> acos[ignore_last(2)](wf)= " << eve::acos[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> acos[wf != -2.0f](wf)   = " << eve::acos[wf != -2.0f](wf) << "\n";
}
