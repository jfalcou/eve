// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>


int main()
{

  {
    kumi::tuple tt{0.01,1.01,2.01,3.01,-1.01,-2.01,-3.01,-4.01};
    kumi::tuple x{1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0};
    std::cout << " < - x                                                 = " << x << std::endl;
    std::cout << " < - tt                                                = " << tt << std::endl;
    std::cout << " -> trapz(0.01,1.01,2.01,3.01,-1.01,-2.01,-3.01,-4.01) = " << eve::trapz(0.01,1.01,2.01,3.01,-1.01,-2.01,-3.01,-4.01) << std::endl;
    std::cout << " -> trapz(tt)                                          = " << eve::trapz(tt) << std::endl;
    std::cout << " -> trapz(x, tt)                                       = " << eve::trapz(x, tt) << std::endl;
    using w_t = eve::wide<double>;
    auto f = [](auto p){return w_t([p](auto q, auto){return p*p+q*3; }); };
    auto g = [](auto p){return 2*(p+1); };
    w_t h([](auto p, auto){return p+1; });
    kumi::tuple tt1(kumi::generate<8>(f));
    kumi::tuple xx(kumi::generate<8>(g));
    std::cout << " <- xx                                                 = " << xx << std::endl;
    std::cout << " <- tt1                                                = " << tt1 << std::endl;
    std::cout << " <- h                                                  = " << h   << std::endl;
    std::cout << " -> trapz(tt1)                                         = " << eve::trapz(tt1) << std::endl;
    std::cout << " -> trapz(tt1)                                         = " << eve::trapz(tt1) << std::endl;
    std::cout << " -> trapz(2.0, tt1)                                    = " << eve::trapz(2.0, tt1) << std::endl;
    std::cout << " -> trapz(h, tt1)                                      = " << eve::trapz(h, tt1) << std::endl;
    std::cout << " -> trapz(x   tt1)                                     = " << eve::trapz(x, tt1) << std::endl;
  }

}
