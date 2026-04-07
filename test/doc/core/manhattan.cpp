// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>


int main()
{
  eve::wide wf0{0.01, 1.01, 2.01, 3.01, -1.01, -2.01, -3.01, -4.01};
  eve::wide wf1{0.01, -4.01, 1.01, -1.01, 2.01, -2.01, 3.01, -3.01};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wi1{0, -4, 1, -1, 2, -2, 3, -3};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};
  eve::wide wu1{7u, 6u, 5u, 4u, 3u, 2u, 1u, 0u};

  std::cout << "<- wf0                                 = " << wf0 << "\n";
  std::cout << "<- wf1                                 = " << wf1 << "\n";
  std::cout << "<- wi0                                 = " << wi0 << "\n";
  std::cout << "<- wi1                                 = " << wi1 << "\n";
  std::cout << "<- wu0                                 = " << wu0 << "\n";
  std::cout << "<- wu1                                 = " << wu1 << "\n";

  std::cout << "-> manhattan(wf0, wf1)                 = " << eve::manhattan(wf0, wf1) << "\n";
  std::cout << "-> manhattan[ignore_last(2)](wf0, wf1) = " << eve::manhattan[eve::ignore_last(2)](wf0, wf1) << "\n";
  std::cout << "-> manhattan[wf0 != 0](wf0, wf1)       = " << eve::manhattan[wf0 != 0](wf0, wf1) << "\n";
  std::cout << "-> manhattan[pedantic](wf0, wf1)       = " << eve::manhattan[eve::pedantic](wf0, wf1) << "\n";
  std::cout << "-> manhattan(wu0, wu1)                 = " << eve::manhattan(wu0, wu1) << "\n";
  std::cout << "-> manhattan(wi0, wi1)                 = " << eve::manhattan(wi0, wi1) << "\n";

  std::cout << std::hexfloat;
  std::cout << "-> manhattan[lower][strict](wf0, wf1)  = " << eve::manhattan[eve::lower][eve::strict](wf0, wf1) << "\n";
  std::cout << "-> manhattan[lower](wf0, wf1)          = " << eve::manhattan[eve::lower](wf0, wf1) << "\n";
  std::cout << "-> manhattan(wf0, wf1)                 = " << eve::manhattan(wf0, wf1) << "\n";
  std::cout << "-> manhattan[upper](wf0, wf1)          = " << eve::manhattan[eve::upper](wf0, wf1) << "\n";
  std::cout << "-> manhattan[upper][strict](wf0, wf1)  = " << eve::manhattan[eve::upper][eve::strict](wf0, wf1) << "\n";

  auto eps_2 = eve::eps(eve::as<float>())/2;
  auto tup = kumi::tuple{1.0f, eps_2, eps_2, eps_2};
  std::cout << "-> manhattan[kahan](tup)   = " << eve::manhattan[eve::kahan](tup) << "\n";


  float o = 1.0f;
  float i = eve::inf(eve::as(o));
  float n = eve::nan(eve::as(o));
  float m = (eve::valmax(eve::as(o))/3)*2;
  std::cout << "<- o                                   = " << o << "\n";
  std::cout << "-> i                                   = " << i << "\n";
  std::cout << "-> n                                   = " << n << "\n";
  std::cout << "-> manhattan(i, o, -i)                 = " << eve::manhattan(i, o, -i) << "\n";
  std::cout << "-> manhattan(i, o, n)                  = " << eve::manhattan(i, o,  n) << "\n";
  std::cout << "-> manhattan[pedantic](i, o, -i)       = " << eve::manhattan[eve::pedantic](i, o, -i) << "\n";
  std::cout << "-> manhattan[pedantic](i, o, n)        = " << eve::manhattan[eve::pedantic](i, o,  n) << "\n";
  std::cout << "-> manhattan[pedantic](o, o, n)        = " << eve::manhattan[eve::pedantic](o, o, n) << "\n";
  std::cout << "-> manhattan[pedantic](o, n, o)        = " << eve::manhattan[eve::pedantic](o, n, o) << "\n";
  std::cout << "-> manhattan[pedantic](n, o, o)        = " << eve::manhattan[eve::pedantic](n, o, o) << "\n";
  std::cout << "-> manhattan          (o, o, n)        = " << eve::manhattan(o, o, n) << "\n";
  std::cout << "-> manhattan          (o, n, o)        = " << eve::manhattan(o, n, o) << "\n";
  std::cout << "-> manhattan          (n, o, o)        = " << eve::manhattan(n, o, o) << "\n";
  std::cout << "-> manhattan(n, n, n)                  = " << eve::manhattan(n, n, n) << "\n";
  std::cout << "-> manhattan(m, o, o)                  = " << eve::manhattan(m, o, o)<< "\n";
  std::cout << "-> manhattan(m, m, n)                  = " << eve::manhattan(m, m, n)<< "\n";
  std::cout << "-> manhattan(i, n)                     = " << eve::manhattan(i, n) << "\n";
  std::cout << "-> manhattan[pedantic](m, m, n)        = " << eve::manhattan[eve::pedantic](m, m, n)<< "\n";
  std::cout << "-> manhattan[pedantic](i, n)           = " << eve::manhattan[eve::pedantic](i, n) << "\n";
}
