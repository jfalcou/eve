// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = { 0.0f, 0.99f, -1.0f, -0.5f, -0.0f, 0.25f, 1.0f, -2.0f};

  std::cout << "<- wf                       = " << wf << "\n";

  std::cout << "-> asind(wf)                = " << eve::asind(wf) << "\n";
  std::cout << "-> asind[ignore_last(2)](wf)= " << eve::asind[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> asind[wf != -2.0f](wf)   = " << eve::asind[wf != -2.0f](wf) << "\n";
}
