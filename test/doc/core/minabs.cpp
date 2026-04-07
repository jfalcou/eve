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

  std::cout << "-> minabs(wf0, wf1)                 = " << eve::minabs(wf0, wf1) << "\n";
  std::cout << "-> minabs[ignore_last(2)](wf0, wf1) = " << eve::minabs[eve::ignore_last(2)](wf0, wf1) << "\n";
  std::cout << "-> minabs[wf0 != 0](wf0, wf1)       = " << eve::minabs[wf0 != 0](wf0, wf1) << "\n";
  std::cout << "-> minabs[pedantic](wf0, wf1)       = " << eve::minabs[eve::pedantic](wf0, wf1) << "\n";
  std::cout << "-> minabs[numeric ](wf0, wf1)       = " << eve::minabs[eve::numeric ](wf0, wf1) << "\n";
  std::cout << "-> minabs(wu0, wu1)                 = " << eve::minabs(wu0, wu1) << "\n";
  std::cout << "-> minabs(wi0, wi1)                 = " << eve::minabs(wi0, wi1) << "\n";

  float o = 1.0f;
  float i = eve::inf(eve::as(o));
  float n = eve::nan(eve::as(o));
  float z = eve::zero(eve::as(o));
  float m = (eve::valmax(eve::as(o))/3)*2;
  std::cout << "<- o                                = " << o << "\n";
  std::cout << "-> i                                = " << i << "\n";
  std::cout << "-> n                                = " << n << "\n";
  std::cout << "-> minabs(i, o, -i)                 = " << eve::minabs(i, o, -i) << "\n";
  std::cout << "-> minabs(i, o, n)                  = " << eve::minabs(i, o, -i) << "\n";
  std::cout << "-> minabs[pedantic](o, o, n)        = " << eve::minabs[eve::pedantic](o, o, n) << "\n";
  std::cout << "-> minabs[pedantic](o, n, o)        = " << eve::minabs[eve::pedantic](o, n, o) << "\n";
  std::cout << "-> minabs[pedantic](n, o, o)        = " << eve::minabs[eve::pedantic](n, o, o) << "\n";
  std::cout << "-> minabs[numeric ](o, o, n)        = " << eve::minabs[eve::numeric ](o, o, n) << "\n";
  std::cout << "-> minabs[numeric](o, n, o)         = " << eve::minabs[eve::numeric](o, n, o) << "\n";
  std::cout << "-> minabs[numeric](n, o, o)         = " << eve::minabs[eve::numeric](n, o, o) << "\n";
  std::cout << "-> minabs          (o, o, n)        = " << eve::minabs(o, o, n) << "\n";
  std::cout << "-> minabs          (o, n, o)        = " << eve::minabs(o, n, o) << "\n";
  std::cout << "-> minabs          (n, o, o)        = " << eve::minabs(n, o, o) << "\n";
  std::cout << "-> minabs(n, n, n)                  = " << eve::minabs(n, n, n) << "\n";
  std::cout << "-> minabs(m, o, o)                  = " << eve::minabs(m, o, o)<< "\n";
  std::cout << "-> minabs(i, o, n)                  = " << eve::minabs(i, o, n)<< "\n";
  std::cout << "-> minabs[drastic](z, o, n)       = " << eve::minabs[eve::drastic](z, o, n)<< "\n";
  std::cout << "-> minabs[numeric](z, o, n)         = " << eve::minabs[eve::numeric](z, o, n)<< "\n";
  std::cout << "-> minabs[pedantic](z, o, n)        = " << eve::minabs[eve::pedantic](z, o, n)<< "\n";
  std::cout << "-> minabs(z, o, n)                  = " << eve::minabs(z, o, n)<< "\n";
}
