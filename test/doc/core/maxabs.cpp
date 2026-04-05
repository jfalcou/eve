// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wf1{0.0, -4.0, 1.0, -1.0, 2.0, -2.0, 3.0, -3.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wi1{0, -4, 1, -1, 2, -2, 3, -3};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};
  eve::wide wu1{7u, 6u, 5u, 4u, 3u, 2u, 1u, 0u};

  std::cout << "<- wf0                              = " << wf0 << "\n";
  std::cout << "<- wf1                              = " << wf1 << "\n";
  std::cout << "<- wi0                              = " << wi0 << "\n";
  std::cout << "<- wi1                              = " << wi1 << "\n";
  std::cout << "<- wu0                              = " << wu0 << "\n";
  std::cout << "<- wu1                              = " << wu1 << "\n";

  std::cout << "-> maxabs(wf0, wf1)                 = " << eve::maxabs(wf0, wf1) << "\n";
  std::cout << "-> maxabs[ignore_last(2)](wf0, wf1) = " << eve::maxabs[eve::ignore_last(2)](wf0, wf1) << "\n";
  std::cout << "-> maxabs[wf0 != 0](wf0, wf1)       = " << eve::maxabs[wf0 != 0](wf0, wf1) << "\n";
  std::cout << "-> maxabs[pedantic](wf0, wf1)       = " << eve::maxabs[eve::pedantic](wf0, wf1) << "\n";
  std::cout << "-> maxabs[numeric ](wf0, wf1)       = " << eve::maxabs[eve::numeric ](wf0, wf1) << "\n";
  std::cout << "-> maxabs(wu0, wu1)                 = " << eve::maxabs(wu0, wu1) << "\n";
  std::cout << "-> maxabs(wi0, wi1)                 = " << eve::maxabs(wi0, wi1) << "\n";

  float o = 1.0f;
  float i = eve::inf(eve::as(o));
  float n = eve::nan(eve::as(o));
  float m = (eve::valmax(eve::as(o))/3)*2;
  std::cout << "<- o                                = " << o << "\n";
  std::cout << "-> i                                = " << i << "\n";
  std::cout << "-> n                                = " << n << "\n";
  std::cout << "-> maxabs(i, o, -i)                 = " << eve::maxabs(i, o, -i) << "\n";
  std::cout << "-> maxabs(i, o, n)                  = " << eve::maxabs(i, o, -i) << "\n";
  std::cout << "-> maxabs[pedantic](o, o, n)        = " << eve::maxabs[eve::pedantic](o, o, n) << "\n";
  std::cout << "-> maxabs[pedantic](o, n, o)        = " << eve::maxabs[eve::pedantic](o, n, o) << "\n";
  std::cout << "-> maxabs[pedantic](n, o, o)        = " << eve::maxabs[eve::pedantic](n, o, o) << "\n";
  std::cout << "-> maxabs[numeric ](o, o, n)        = " << eve::maxabs[eve::numeric ](o, o, n) << "\n";
  std::cout << "-> maxabs[numeric](o, n, o)         = " << eve::maxabs[eve::numeric](o, n, o) << "\n";
  std::cout << "-> maxabs[numeric](n, o, o)         = " << eve::maxabs[eve::numeric](n, o, o) << "\n";
  std::cout << "-> maxabs          (o, o, n)        = " << eve::maxabs(o, o, n) << "\n";
  std::cout << "-> maxabs          (o, n, o)        = " << eve::maxabs(o, n, o) << "\n";
  std::cout << "-> maxabs          (n, o, o)        = " << eve::maxabs(n, o, o) << "\n";
  std::cout << "-> maxabs(n, n, n)                  = " << eve::maxabs(n, n, n) << "\n";
  std::cout << "-> maxabs(m, o, o)                  = " << eve::maxabs(m, o, o)<< "\n";
  std::cout << "-> maxabs(i, o, n)                  = " << eve::maxabs(i, o, n)<< "\n";
  std::cout << "-> maxabs[nan_aware](i, o, n)       = " << eve::maxabs[eve::nan_aware](i, o, n)<< "\n";
  std::cout << "-> maxabs(i, o, n)                  = " << eve::maxabs(i, o, n)<< "\n";

}
