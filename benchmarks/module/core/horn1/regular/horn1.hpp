//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/core/detail/generic/horn1.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <type_traits>

int main()
{
  using EVE_VALUE = eve::element_type_t<EVE_TYPE>;
  if constexpr(std::is_same_v<EVE_VALUE, double>)
  {
    using i_t =  eve::as_integer_t<EVE_VALUE>;
    auto eve__horn1 =  []<typename T>(T z) -> T{
      return eve::detail::horn1<T,
      i_t(0x403c896240f3081dll),
      i_t(0xc03991aaac01ab68ll),
      i_t(0x401bdff5baf33e6all),
      i_t(0xbfe2079259f9290fll),
      i_t(0x3f684fc3988e9f08ll)
      >(z);
    };
    auto lmin = EVE_VALUE(-1);
    auto lmax = EVE_VALUE(1);
    auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
    eve::bench::experiment xp;
    run<EVE_VALUE> (EVE_NAME(eve__horn1) , xp, eve__horn1, arg0);
    run<EVE_TYPE>  (EVE_NAME(eve__horn1) , xp, eve__horn1, arg0);
  }
  else if constexpr(std::is_same_v<EVE_VALUE, float>)
  {
    using i_t =  eve::as_integer_t<EVE_VALUE>;
    auto eve__horn1 = []<typename T>(T z) -> T{
      return eve::detail::horn1<T,
      i_t(0x3e2aaae4u),
      i_t(0x3d9980f6u),
      i_t(0x3d3a3ec7u),
      i_t(0x3cc617e3u),
      i_t(0x3d2cb352u)
      > (z);
    };
    auto lmin = EVE_VALUE(-1);
    auto lmax = EVE_VALUE(1);
    auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
    eve::bench::experiment xp;
    run<EVE_VALUE> (EVE_NAME(eve__horn) , xp, eve__horn1, arg0);
    run<EVE_TYPE>  (EVE_NAME(eve__horn) , xp, eve__horn1, arg0);
  }
}
