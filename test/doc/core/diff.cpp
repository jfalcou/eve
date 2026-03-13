// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>


int main()
{

  {
    kumi::tuple tt{1.5000, 2.2500, 3.3750, 5.0625, 7.5938, 11.3906, 17.0859, 25.6289};
//    auto tt =  kumi::generate<8>([](auto t){return eve::pow(1.5, p)});
    std::cout << " < - tt                                               = " << tt << std::endl;
    std::cout << " -> diff(index_t<0>, tt)       = " << eve::diff(kumi::index_t<0>{}, tt) << std::endl;
    std::cout << " -> diff(index_t<1>, tt)       = " << eve::diff(kumi::index_t<1>{}, tt) << std::endl;
    std::cout << " -> diff(index_t<2>, tt)       = " << eve::diff(kumi::index_t<2>{}, tt) << std::endl;
    std::cout << " -> diff(index_t<7>, tt)       = " << eve::diff(kumi::index_t<7>{}, tt) << std::endl;
    std::cout << " -> diff(index_t<_>, tt)       = " << eve::diff(kumi::index_t<8>{}, tt) << std::endl;
  }

}
