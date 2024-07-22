// revision 1
#include <eve/module/elliptic.hpp>
#include <iostream>

eve::wide pf{1.0f, 0.0f, 1.5f, 3.0f};
eve::wide qf{1.0f, 4.0f, 0.2f, 0.5f};
eve::wide rf{2.0f, 1.0f, 0.1f, 0.4f};

int main()
{
  std::cout << "<- pf = " << pf << "\n";
  std::cout << "<- qf = " << qf << "\n";
  std::cout << "<- rf = " << rf << "\n";

  std::cout << "-> ellint_rg(pf, qf, rf)                = " << eve::ellint_rg(pf, qf, rf) << "\n";
  std::cout << "-> ellint_rg[ignore_last(2)](pf, qf, rf)= " << eve::ellint_rg[eve::ignore_last(2)](pf, qf, rf) << "\n";
  std::cout << "-> ellint_rg[qf != 4.0f](pf, qf, rf)    = " << eve::ellint_rg[qf != 4.0f](pf, qf, rf) << "\n";
}
