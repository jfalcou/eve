// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0f, -0.0f, -1.0f, 1.0f, 2.0f,
                  eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "<- wf                         = " << wf << "\n";

  std::cout << "-> sigmoid(wf)                = " << eve::sigmoid(wf) << "\n";
  std::cout << "-> sigmoid[ignore_last(2)](wf)= " << eve::sigmoid[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> sigmoid[wf != 2.0f](wf)    = " << eve::sigmoid[wf != 2.0f](wf) << "\n";
}
