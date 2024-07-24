// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});

  std::cout << "<- wf = " << wf << "\n";

  std::cout << "-> erfc_inv(wf)                = " << eve::erfc_inv(wf) << "\n";
  std::cout << "-> erfc_inv[ignore_last(2)](wf)= " << eve::erfc_inv[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> erfc_inv[wf != -2.0f](wf)   = " << eve::erfc_inv[wf != -2.0f](wf) << "\n";
}
