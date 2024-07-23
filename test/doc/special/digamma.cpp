// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};

  std::cout << "<- wf                         = " << wf << "\n";

  std::cout << "-> digamma(wf)                = " << eve::digamma(wf) << "\n";
  std::cout << "-> digamma[ignore_last(2)](wf)= " << eve::digamma[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> digamma[wf > 0.0f](wf)     = " << eve::digamma[wf >  0.0](wf) << "\n";
}
