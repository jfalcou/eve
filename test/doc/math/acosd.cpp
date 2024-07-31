// revision 1
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide wf = { 0.0f, 0.99f, -1.0f, -0.5f, -0.0f, 0.25f, 1.0f, -2.0f};

  std::cout << "<- wf                       = " << wf << "\n";

  std::cout << std::setprecision(10);
  std::cout << "-> acosd(wf)                = " << eve::acosd(wf) << "\n";
  std::cout << "-> acosd[raw](wf)           = " << eve::acosd[eve::raw](wf) << "\n";
  std::cout << "-> acosd[ignore_last(2)](wf)= " << eve::acosd[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> acosd[wf != -2.0f](wf)   = " << eve::acosd[wf != -2.0f](wf) << "\n";
}
