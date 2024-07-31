// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = { 0.0f, 0.99f, -1.0f, -0.5f, -0.0f, 0.25f, 1.0f, -2.0f};

  std::cout << "<- wf                        = " << wf << "\n";

  std::cout << "-> asinpi(wf)                = " << eve::asinpi(wf) << "\n";
  std::cout << "-> asinpi[ignore_last(2)](wf)= " << eve::asinpi[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> asinpi[wf != -2.0f](wf)   = " << eve::asinpi[wf != -2.0f](wf) << "\n";
}
