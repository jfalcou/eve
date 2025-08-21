// revision 0
#include <eve/module/core.hpp>
#include <eve/module/combinatorial.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  double p =  (1ul << 50) -27;
  eve::wide w0{1.0, 10.0, 25.0, 33.0, 27.0, 13.0, 18.0, 4.0};
  eve::wide w1{0.0, 25.0, 33.0, 12.0, 20.0, 18.0, 6.0, 10.0};
  w0+= floor(p/8);
  w1+= floor(p/4)-100;
  std::cout << std::setprecision(20);
  std::cout << "<- p                    = " << p << "\n";
  std::cout << "<- w0                   = " << w0 << "\n";
  std::cout << "<- w1                   = " << w1 << "\n";
  std::cout << "-> rec[mod = p](w0) = " << eve::rec[eve::mod = p](w0) << "\n";
  std::cout << "-> rec[mod = p](w1) = " << eve::rec[eve::mod = p](w1) << "\n";
  std::cout << "-> mul[mod = p](rec[mod = p](w0), w0) " << eve::mul[eve::mod = p](eve::rec[eve::mod = p](w0), w0)<< "\n";
  std::cout << "-> mul[mod = p](rec[mod = p](w1), w1) " << eve::mul[eve::mod = p](eve::rec[eve::mod = p](w1), w1)<< "\n";
  std::cout << std::endl;
  std::cout << eve::mul[eve::mod = p](p-1, p-1) << std::endl;

  double a = 10.0;
  double b = eve::rec[eve::mod = p](a);
  double c = eve::mul[eve::mod = p](a, b);
  std::cout << "a " << a << std::endl;
  std::cout << "b " << b << std::endl;
  std::cout << "c " << c << std::endl;
  std::cout << "p " << p << std::endl;

  double pp = 2*3*7.0;
  double d = 2*3*4.0;
  std::cout << "pp             " << pp<< std::endl;
  std::cout << "d              " << d << std::endl;
  double rd = eve::rec[eve::mod = pp](d);
  std::cout << "rd             " << rd << std::endl;
  std::cout << "rd*p mod pp =  " << eve::mul[eve::mod = pp](d, rd)<< std::endl;


}
