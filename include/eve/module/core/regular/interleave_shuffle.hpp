//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/function/interleave.hpp>
#include <eve/traits/overload.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/traits/cardinal.hpp>


namespace eve
{
  template<typename Options>
  struct interleave_shuffle_t : callable<interleave_shuffle_t, Options>
  {
    template<eve::value T, eve::value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    EVE_FORCEINLINE  as_wide_t<common_value_t<T,U>, typename cardinal_t<common_value_t<T,U>>::combined_type>
    operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    EVE_CALLABLE_OBJECT(interleave_shuffle_t, interleave_shuffle_);
  };

  inline constexpr auto interleave_shuffle = functor<interleave_shuffle_t>;

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    EVE_FORCEINLINE auto
    interleave_shuffle_(EVE_REQUIRES(cpu_), O const&, T a, U b) noexcept
    {
      if constexpr(scalar_value<T>)
        return interleave_shuffle(U(a), b);
      else if constexpr(scalar_value<U>)
        return interleave_shuffle(a , T(b));
      else
      {
        auto [l, h] = interleave(a, b);
        return as_wide_t<element_type_t<T>, typename cardinal_t<T>::combined_type> {l, h};
      }
    }
  }
}
