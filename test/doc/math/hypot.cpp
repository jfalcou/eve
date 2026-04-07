// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
//   eve::wide pf = {-1.0, 2.0, -3.0, eve::valmax(eve::as<double>())};
//   eve::wide qf = {-4.0, 3.0, -2.0, eve::inf(eve::as<double>())};
//   eve::wide rf = {-40.0, 0.03, -2.0, eve::nan(eve::as<double>())};
//   kumi::tuple wt{pf, qf};

//    std::cout << "<- pf = " << pf << "\n";
//    std::cout << "<- qf = " << qf << "\n";
//    std::cout << "<- rf = " << rf << "\n";
//    std::cout << "<- wt = " << wt << "\n";

//    std::cout << "-> hypot(pf,qf)                = " << eve::hypot(pf,qf) << "\n";
//    std::cout << "-> hypot(wt)                   = " << eve::hypot(wt) << "\n";
//    std::cout << "-> hypot[ignore_last(2)](pf,qf)= " << eve::hypot[eve::ignore_last(2)](pf,qf) << "\n";
//    std::cout << "-> hypot[pf > 0.0](pf,qf)      = " << eve::hypot[pf > 0.0](pf,qf) << "\n";
//    std::cout << "-> hypot[pedantic](pf,qf)      = " << eve::hypot[eve::pedantic](pf,qf) << "\n";
//    std::cout << "-> hypot(pf,qf,rf)             = " << eve::hypot(pf,qf,rf) << "\n";
//    std::cout << "-> hypot[pedantic](pf,qf,rf)   = " << eve::hypot[eve::pedantic](pf,qf,rf) << "\n";

  float o = 1.0f;
  float i = eve::inf(eve::as(o));
  float n = eve::nan(eve::as(o));
  float v = eve::valmax(eve::as(o));
  float m = (v/3)*2;
  std::cout << "<- o                               = " << o << "\n";
  std::cout << "-> i                               = " << i << "\n";
  std::cout << "-> n                               = " << n << "\n";
  std::cout << "-> m                               = " << m << "\n";
  std::cout << "-> hypot(i, o, -i)                 = " << eve::hypot(i, o, -i) << "\n";
  std::cout << "-> hypot(i, o, n)                  = " << eve::hypot(i, o,  n) << "\n";
  std::cout << "-> hypot[pedantic](i, o, -i)       = " << eve::hypot[eve::pedantic](i, o, -i) << "\n";
  std::cout << "-> hypot[pedantic](i, o, n)        = " << eve::hypot[eve::pedantic](i, o,  n) << "\n";
  std::cout << "-> hypot[pedantic](o, o, n)        = " << eve::hypot[eve::pedantic](o, o, n) << "\n";
  std::cout << "-> hypot[pedantic](o, n, o)        = " << eve::hypot[eve::pedantic](o, n, o) << "\n";
  std::cout << "-> hypot[pedantic](n, o, o)        = " << eve::hypot[eve::pedantic](n, o, o) << "\n";
  std::cout << "-> hypot          (o, o, n)        = " << eve::hypot(o, o, n) << "\n";
  std::cout << "-> hypot          (o, n, o)        = " << eve::hypot(o, n, o) << "\n";
  std::cout << "-> hypot          (n, o, o)        = " << eve::hypot(n, o, o) << "\n";
  std::cout << "-> hypot(n, n, n)                  = " << eve::hypot(n, n, n) << "\n";
  std::cout << "-> hypot(m, o, o)                  = " << eve::hypot(m, o, o)<< "\n";
  std::cout << "-> hypot(m, m, n)                  = " << eve::hypot(m, m, n)<< "\n";
  std::cout << "-> hypot(i, n)                     = " << eve::hypot(i, n) << "\n";
  std::cout << "-> hypot[pedantic](m, m)           = " << eve::hypot[eve::pedantic](m, m)<< "\n";
  std::cout << "-> hypot[pedantic](m, m, n)        = " << eve::hypot[eve::pedantic](m, m, n)<< "\n";
  std::cout << "-> hypot[pedantic](i, n)           = " << eve::hypot[eve::pedantic](i, n) << "\n";
  std::cout << "-> hypot[pedantic](v, v, n)        = " << eve::hypot[eve::pedantic](v, v, n)<< "\n";
  std::cout << "-> hypot[pedantic](m, m)           = " << eve::hypot[eve::pedantic](m, m)<< "\n";
  std::cout << "-> hypot(m, m, n)                  = " << eve::hypot(m, m, n)<< "\n";
  std::cout << "-> hypot(i, n, n)                  = " << eve::hypot(i, n, n) << "\n";
  std::cout << "-> hypot(i, n)                     = " << eve::hypot(i, n)    << "\n";
  std::cout << "-> hypot(v, v, n)                  = " << eve::hypot(v, v, n)<< "\n";
}
