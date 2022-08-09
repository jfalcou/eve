//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/core/detail/generic/poleval.hpp>
#include <eve/module/polynomial.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/wide.hpp>

int main()
{
  using v_t = eve::element_type_t<EVE_TYPE>;
  auto eve__horner = []<typename T>(T z) -> T{
    constexpr std::array < v_t, 5> a = {
      -4.497014141919556E+001,
      5.073465654089319E+001,
      -2.485774108720340E+001,
      7.222973196770240E+000,
      -1.544842782180211E+000,
    };
    return eve::horner(z, a);
  };
  auto eve__poleval = []<typename T>(T z) -> T{
    constexpr std::array < v_t, 5> a = {
      -4.497014141919556E+001,
      5.073465654089319E+001,
      -2.485774108720340E+001,
      7.222973196770240E+000,
      -1.544842782180211E+000,
    };
    return eve::detail::poleval(z, a);
  };
  auto lmin = EVE_VALUE(-1);
  auto lmax = EVE_VALUE(1);
  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  eve::bench::experiment xp;

  if constexpr(std::is_same_v<EVE_VALUE, double>)
  {
    using i_t = eve::as_integer_t<EVE_VALUE>;
    auto eve__horn = []<typename T>(T z) -> T{
      return eve::detail::horn<T,
      i_t(0x403c896240f3081dll),
      i_t(0xc03991aaac01ab68ll),
      i_t(0x401bdff5baf33e6all),
      i_t(0xbfe2079259f9290fll),
      i_t(0x3f684fc3988e9f08ll)
      >(z);
    };
    run<EVE_VALUE> (EVE_NAME(eve__horn) , xp, eve__horn, arg0);
    run<EVE_TYPE>  (EVE_NAME(eve__horn) , xp, eve__horn, arg0);
  }
  else if constexpr(std::is_same_v<EVE_VALUE, float>)
  {
    using i_t = eve::as_integer_t<EVE_VALUE>;
    auto eve__horn = []<typename T>(T z) -> T{
      return eve::detail::horn<T,
      i_t(0x3e2aaae4u),
      i_t(0x3d9980f6u),
      i_t(0x3d3a3ec7u),
      i_t(0x3cc617e3u),
      i_t(0x3d2cb352u)
      > (z);
    };
    run<EVE_VALUE> (EVE_NAME(eve__horn) , xp, eve__horn, arg0);
    run<EVE_TYPE>  (EVE_NAME(eve__horn) , xp, eve__horn, arg0);
  }
  run<EVE_VALUE> (EVE_NAME(eve__horner) , xp, eve__horner, arg0);
  run<EVE_VALUE> (EVE_NAME(eve__poleval) , xp, eve__poleval, arg0);
  run<EVE_TYPE>  (EVE_NAME(eve__horner) , xp, eve__horner, arg0);
  run<EVE_TYPE>  (EVE_NAME(eve__poleval) , xp, eve__poleval, arg0);
}
