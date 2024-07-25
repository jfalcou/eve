// revision 1
#include <eve/module/elliptic.hpp>
#include <iostream>

eve::wide pf{1.0f, 0.0f, 1.5f, 3.0f};
eve::wide qf{1.0f, 4.0f, 0.2f, 0.5f};
eve::wide rf{2.0f, 1.0f, 0.1f, 0.4f};
eve::wide sf{0.19f, 0.5f, 0.87071f, 2.4f};
int main()
{
  std::cout << "<- pf = " << pf << "\n";
  std::cout << "<- qf = " << qf << "\n";
  std::cout << "<- rf = " << rf << "\n";
  std::cout << "<- sf = " << sf << "\n";

  std::cout << "-> ellint_rj(pf, qf, rf, sf)                = " << eve::ellint_rj(pf, qf, rf, sf) << "\n";
  std::cout << "-> ellint_rj[ignore_last(2)](pf, qf, rf, sf)= " << eve::ellint_rj[eve::ignore_last(2)](pf, qf, rf, sf) << "\n";
  std::cout << "-> ellint_rj[qf != 4.0f](pf, qf, rf, sf)    = " << eve::ellint_rj[qf != 4.0f](pf, qf, rf, sf) << "\n";
}
