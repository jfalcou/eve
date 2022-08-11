//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include "producers.hpp"
#include "generator.hpp"
#include <cmath>

TTS_CASE_TPL("Random check for eve::prev", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());

  if constexpr(eve::floating_value<e_t>)
  {
    auto std_prev = [](auto e)
      {
        return    (e == eve::minf(eve::as<e_t>()))
        ? eve::nan(eve::as<e_t>())
        : std::nextafter(e, eve::minf(eve::as<e_t>()));
      };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_prev, eve::prev );
  }
  else
  {
    auto std_prev = [](auto e) -> e_t{ return e == eve::valmin(eve::as<e_t>()) ? eve::valmax(eve::as<e_t>()): e-1; };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_prev, eve::prev );
  }


  auto std_pedantic_prev = [](auto e)  -> e_t{
    if constexpr(eve::floating_value<T>)
    {
      return  (e == 0) && eve::is_positive(e)
                ? e_t(-0.)
                : ((e ==  eve::minf(eve::as<e_t>()))
                    ? eve::nan(eve::as<e_t>())
                    : std::nextafter(e, eve::minf(eve::as<e_t>()))
                  );
    }
    else
    {
      return e == eve::valmin(eve::as(e)) ? e : e-1;
    }
  };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_pedantic_prev, eve::pedantic(eve::prev));

  auto std_saturated_prev = [](auto e) -> e_t {
    if constexpr(eve::floating_value<T>)
    {
      return (e == eve::minf(eve::as(e)))
      ?  eve::nan(eve::as<e_t>())
      : std::nextafter(e, eve::minf(eve::as<e_t>()));
    }
    else
    {
      return e == eve::valmin(eve::as(e)) ? e : e-1;
    }
  };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax), std_saturated_prev, eve::saturated(eve::prev));
};
