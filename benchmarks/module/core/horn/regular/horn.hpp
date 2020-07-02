//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/module/core/detail/generic/horn.hpp>

int main()
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  if constexpr(std::is_same_v<EVE_VALUE, double>)
  {
    using i_t =  eve::detail::as_integer_t<EVE_VALUE>;
    auto eve__horn = [](auto z){
      return eve::detail::horn<EVE_TYPE,
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
    eve::bench::experiment xp( eve::bench::optimal_size<EVE_TYPE> );
    run<EVE_VALUE> (EVE_NAME(eve__horn) , xp, eve__horn, arg0);
    run<EVE_TYPE>  (EVE_NAME(eve__horn) , xp, eve__horn, arg0);
  }
  else if constexpr(std::is_same_v<EVE_VALUE, float>)
  {
    using i_t =  eve::detail::as_integer_t<EVE_VALUE>;
    auto eve__horn = [](auto z){
      return eve::detail::horn<EVE_TYPE,
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
    eve::bench::experiment xp( eve::bench::optimal_size<EVE_TYPE> );
    run<EVE_VALUE> (EVE_NAME(eve__horn) , xp, eve__horn, arg0);
    run<EVE_TYPE>  (EVE_NAME(eve__horn) , xp, eve__horn, arg0);
  }
}
