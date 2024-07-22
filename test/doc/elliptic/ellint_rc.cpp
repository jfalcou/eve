// revision 1
#include <eve/module/elliptic.hpp>
#include <iostream>

eve::wide pf{1.0f, 0.0f, 1.5f, 3.0f};
eve::wide qf{1.0f, 4.0f, 0.2f, 0.5f};

int main()
{
  std::cout << "<- pf = " << pf << "\n";
  std::cout << "<- qf = " << qf << "\n";

  std::cout << "-> ellint_rc(pf, qf)                = " << eve::ellint_rc(pf, qf) << "\n";
  std::cout << "-> ellint_rc[ignore_last(2)](pf, qf)= " << eve::ellint_rc[eve::ignore_last(2)](pf, qf) << "\n";
  std::cout << "-> ellint_rc[qf != 4.0f](pf, qf)    = " << eve::ellint_rc[qf != 4.0f](pf, qf) << "\n";
}
