// revision 1
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide wf = { 5.0f, 2.0f, -1.0f, -2.0f, -5.0f,  1.001f, -1.0f, 0.0f};

  std::cout << "<- wf                      = " << wf << "\n";

  std::cout << std::setprecision(10);
  std::cout << "-> asec(wf)                = " << eve::asec(wf) << "\n";
  std::cout << "-> asec[deg](wf)           = " << eve::asec[eve::deg](wf) << "\n";
  std::cout << "-> asec[radpi](wf)         = " << eve::asec[eve::radpi](wf) << "\n";
  std::cout << "-> asec[rad](wf)           = " << eve::asec[eve::rad](wf) << "\n";
  std::cout << "-> asec[raw](wf)           = " << eve::asec[eve::raw](wf) << "\n";
  std::cout << "-> asec[ignore_last(2)](wf)= " << eve::asec[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> asec[wf != 2.0f](wf)    = " << eve::asec[wf != 2.0f](wf) << "\n";
}
