// revision 0
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  float a = 0;
  float b = 1;
  auto f =  [](auto x){return x-0.5f; }; //*eve::exp(x)-0.5; };
  auto r =  eve::dichotomy(f, a, b);
  std::cout << "dichotomy(f, a, b)   =  "<< r<< std::endl;
  std::cout << "f(r)                 =  "<< f(r) << std::endl;
}
