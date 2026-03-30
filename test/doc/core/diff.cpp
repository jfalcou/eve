// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>


int main()
{
  std::cout << std::hexfloat << std::endl;
  {
    kumi::tuple tt{1.5000e-5, 2.2500, 3.3750, 5.0625, 7.0, 11.0, 17.0, 25.0};
    std::cout << " < - tt                        = " << tt << std::endl;
    std::cout << " -> diff(index_t<0>, tt)       = " << eve::diff(kumi::index_t<0>{}, tt) << std::endl;
    std::cout << " -> diff(tt)                   = " << eve::diff(tt) << std::endl;
    std::cout << " -> diff(index_t<1>, tt)       = " << eve::diff(kumi::index_t<1>{}, tt) << std::endl;
    std::cout << " -> diff(index_t<2>, tt)       = " << eve::diff(kumi::index_t<2>{}, tt) << std::endl;
    std::cout << " -> diff(index_t<7>, tt)       = " << eve::diff(kumi::index_t<7>{}, tt) << std::endl;
    std::cout << " -> diff(index_t<8>, tt)       = " << eve::diff(kumi::index_t<8>{}, tt) << std::endl;
    std::cout << "float"  << 8*sizeof(kumi::get<0>(eve::diff(kumi::index_t<1>{}, tt))) << std::endl;

  }
  {
    kumi::tuple tt{1.5000e-5f, 2.2500f, 3.3750f, 5.0625f, 7.0f, 11.0f, 17.0f, 25.0f};
    std::cout << " < - tt                        = " << tt << std::endl;
    std::cout << " -> diff(index_t<0>, tt)       = " << eve::diff(kumi::index_t<0>{}, tt) << std::endl;
    std::cout << " -> diff(tt)                   = " << eve::diff(tt) << std::endl;
    std::cout << " -> diff(index_t<1>, tt)       = " << eve::diff(kumi::index_t<1>{}, tt) << std::endl;
    std::cout << " -> diff(index_t<2>, tt)       = " << eve::diff(kumi::index_t<2>{}, tt) << std::endl;
    std::cout << " -> diff(index_t<7>, tt)       = " << eve::diff(kumi::index_t<7>{}, tt) << std::endl;
    std::cout << " -> diff(index_t<8>, tt)       = " << eve::diff(kumi::index_t<8>{}, tt) << std::endl;
    std::cout << "float"  << 8*sizeof(kumi::get<0>(eve::diff(kumi::index_t<1>{}, tt))) << std::endl;
  }
  using eve::widen;
  {
    kumi::tuple tt{1.5000e-5f, 2.2500f, 3.3750f, 5.0625f, 7.0f, 11.0f, 17.0f, 25.0f};
    std::cout << " < - tt                        = " << tt << std::endl;
    std::cout << " -> diff[widen](index_t<0>, tt)       = " << eve::diff[widen](kumi::index_t<0>{}, tt) << std::endl;
    std::cout << " -> diff[widen](tt)                   = " << eve::diff[widen](tt) << std::endl;
    std::cout << " -> diff[widen](index_t<1>, tt)       = " << eve::diff[widen](kumi::index_t<1>{}, tt) << std::endl;
    std::cout << " -> diff[widen](index_t<2>, tt)       = " << eve::diff[widen](kumi::index_t<2>{}, tt) << std::endl;
    std::cout << " -> diff[widen](index_t<7>, tt)       = " << eve::diff[widen](kumi::index_t<7>{}, tt) << std::endl;
    std::cout << " -> diff[widen](index_t<8>, tt)       = " << eve::diff[widen](kumi::index_t<8>{}, tt) << std::endl;
    std::cout << "float"  << 8*sizeof(kumi::get<0>(eve::diff[widen](kumi::index_t<1>{}, tt))) << std::endl;

  }
  {
   std::cout << " -> diff( ...)                      = " << eve::diff(1.5000e-5f, 2.2500f, 3.3750f, 5.0625f, 7.0f, 11.0f, 17.0f, 25.0f) << std::endl;
   std::cout << " -> diff(index_t<1>, ...)           = " << eve::diff(kumi::index_t<1>{}, 1.5000e-5f, 2.2500f, 3.3750f, 5.0625f, 7.0f, 11.0f, 17.0f, 25.0f) << std::endl;
   std::cout << " -> diff[widen]( ...)               = " << eve::diff[widen](1.5000e-5f, 2.2500f, 3.3750f, 5.0625f, 7.0f, 11.0f, 17.0f, 25.0f) << std::endl;
   std::cout << " -> diff[widen](index_t<1>, ...)    = " << eve::diff[widen](kumi::index_t<1>{}, 1.5000e-5f, 2.2500f, 3.3750f, 5.0625f, 7.0f, 11.0f, 17.0f, 25.0f) << std::endl;
  }
}
