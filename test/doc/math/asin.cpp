// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = { 0.0f, 0.99f, -1.0f, -0.5f, -0.0f, 0.25f, 1.0f, -2.0f};

  std::cout << "<- wf                      = " << wf << "\n";

  std::cout << "-> asin(wf)                = " << eve::asin(wf) << "\n";
  std::cout << "-> asin[deg](wf)           = " << eve::asin[eve::deg](wf) << "\n";
  std::cout << "-> asin[radpi](wf)         = " << eve::asin[eve::radpi](wf) << "\n";
  std::cout << "-> asin[rad](wf)           = " << eve::asin[eve::rad](wf) << "\n";
  std::cout << "-> asin[ignore_last(2)](wf)= " << eve::asin[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> asin[wf != -2.0f](wf)   = " << eve::asin[wf != -2.0f](wf) << "\n";
}
