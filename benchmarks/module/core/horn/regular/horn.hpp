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
#include <eve/memory/aligned_ptr.hpp>
#include <tts/tests/relation.hpp>
#include <type_traits>

int main()
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  if constexpr(std::is_same_v<EVE_VALUE, double>)
  {
    using i_t =  eve::detail::as_integer_t<EVE_VALUE>;
    auto f = [](auto z){
      return eve::detail::horn<EVE_TYPE,
      i_t(0x403c896240f3081dll),
      i_t(0xc03991aaac01ab68ll),
      i_t(0x401bdff5baf33e6all),
      i_t(0xbfe2079259f9290fll),
      i_t(0x3f684fc3988e9f08ll)
      >(z);
    };
    EVE_REGISTER_BENCHMARK(f, EVE_TYPE
                          , eve::bench::random<EVE_TYPE>(-1., 1.));
    eve::bench::start_benchmarks(argc, argv);
  }
  else if constexpr(std::is_same_v<EVE_VALUE, float>)
  {
    using i_t =  eve::detail::as_integer_t<EVE_VALUE>;
    auto f = [](auto z){
      return eve::detail::horn<EVE_TYPE,
      i_t(0x3e2aaae4u),
      i_t(0x3d9980f6u),
      i_t(0x3d3a3ec7u),
      i_t(0x3cc617e3u),
      i_t(0x3d2cb352u)
      > (z);
    };
    EVE_REGISTER_BENCHMARK(f, EVE_TYPE
                          , eve::bench::random<EVE_TYPE>(-1.f, 1.f));
    eve::bench::start_benchmarks(argc, argv);
  }
}
