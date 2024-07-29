// revision 1
#include <eve/module/special.hpp>
#include <iostream>


int main()
{
  eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i+float(c)/3);});
  std::cout << "<- wf = " << wf << "\n";

  std::cout << "-> stirling(wf)                = " << eve::stirling(wf) << "\n";
  std::cout << "-> stirling[ignore_last(2)](wf)= " << eve::stirling[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> stirling[wf != 6.0f](wf)    = " << eve::stirling[wf != 6.0f](wf) << "\n";
}
