// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>


template<size_t N, eve::floating_value... Ts>
EVE_FORCEINLINE constexpr  kumi::result::iota_t<sizeof...(Ts)-N, eve::common_value_t<Ts...>>
 mydiff( kumi::index_t<N> n, Ts... args) noexcept
{
  return eve::diff(n, kumi::make_tuple(args...));
}

int main()
{

  {
    kumi::tuple tt{1.5000, 2.2500, 3.3750, 5.0625, 7.5938, 11.3906, 17.0859, 25.6289};
    std::cout << " < - tt                        = " << tt << std::endl;
    std::cout << " -> diff(index_t<0>, tt)       = " << eve::diff(kumi::index_t<0>{}, tt) << std::endl;
    std::cout << " -> diff(tt)                   = " << eve::diff(tt) << std::endl;
    std::cout << " -> diff(index_t<1>, tt)       = " << eve::diff(kumi::index_t<1>{}, tt) << std::endl;
    std::cout << " -> diff(index_t<2>, tt)       = " << eve::diff(kumi::index_t<2>{}, tt) << std::endl;
    std::cout << " -> diff(index_t<7>, tt)       = " << eve::diff(kumi::index_t<7>{}, tt) << std::endl;
    std::cout << " -> diff(index_t<8>, tt)       = " << eve::diff(kumi::index_t<8>{}, tt) << std::endl;

  }
  {
    kumi::tuple tt{1.5000f, 2.2500f, 3.3750f, 5.0625f, 7.5938f, 11.3906f, 17.0859f, 25.6289f};
    std::cout << " < - tt                        = " << tt << std::endl;
    std::cout << " -> diff(index_t<0>, tt)       = " << eve::diff(kumi::index_t<0>{}, tt) << std::endl;
    std::cout << " -> diff(tt)                   = " << eve::diff(tt) << std::endl;
    std::cout << " -> diff(index_t<1>, tt)       = " << eve::diff(kumi::index_t<1>{}, tt) << std::endl;
    std::cout << " -> diff(index_t<2>, tt)       = " << eve::diff(kumi::index_t<2>{}, tt) << std::endl;
    std::cout << " -> diff(index_t<7>, tt)       = " << eve::diff(kumi::index_t<7>{}, tt) << std::endl;
    std::cout << " -> diff(index_t<8>, tt)       = " << eve::diff(kumi::index_t<8>{}, tt) << std::endl;
  }
  {
//    std::cout << " -> diff[eve::widen](index_t<0>, ...)       = " << mydiff(kumi::index_t<2>{}, 1.5000f, 2.2500f, 3.3750f, 5.0625f, 7.5938f, 11.3906f, 17.0859f, 25.6289f) << std::endl;
//    std::cout << " -> diff[eve::widen](index_t<0>, ...)       = " << eve::diff(kumi::index_t<2>{}, 1.5000f, 2.2500f, 3.3750f, 5.0625f, 7.5938f, 11.3906f, 17.0859f, 25.6289f) << std::endl;
//    std::cout << " -> diff[eve::widen](index_t<0>, ...)       = " << eve::diff(1.5000f, 2.2500f, 3.3750f, 5.0625f, 7.5938f, 11.3906f, 17.0859f, 25.6289f) << std::endl;
//    std::cout << " -> diff[eve::widen](index_t<8>, ...)       = " << eve::diff[eve::widen](kumi::index_t<8>{}, 1.5000f, 2.2500f, 3.3750f, 5.0625f, 7.5938f, 11.3906f, 17.0859f, 25.6289f) << std::endl;
  }
}
