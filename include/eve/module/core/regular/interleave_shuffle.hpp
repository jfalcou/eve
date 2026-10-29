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
#include <eve/arch/width.hpp>

//TODO doc
namespace eve
{
  template<typename Options>
  struct interleave_shuffle_t : callable<interleave_shuffle_t, Options>
  {
    template <typename T, typename U>
    struct result;

    template <simd_value T, typename U>
    struct result<T, U>
    {
      using type = typename T::template rescale<(width_v<T> * 2)>;
    };

    template <typename T, simd_value U>
    requires( !simd_value<T> )
    struct result<T, U>
    {
      using type = typename U::template rescale<(width_v<U> * 2)>;
    };

    template<eve::value T, eve::value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    EVE_ABI typename result<T, U>::type
    operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    EVE_CALLABLE_OBJECT(interleave_shuffle_t, interleave_shuffle_);
  };

  inline constexpr auto interleave_shuffle = functor<interleave_shuffle_t>;

  namespace _
  {
    template<typename T, typename U, callable_options O>
    auto
    interleave_shuffle_(EVE_REQUIRES(cpu_), O const&, T a, U b) noexcept
    {
      if constexpr(scalar_value<T>)
        return interleave_shuffle(U(a), b);
      else if constexpr(scalar_value<U>)
        return interleave_shuffle(a , T(b));
      else
      {
        auto [l, h] = interleave(a, b);
        return as_wide_t<element_type_t<T>, T::size() * 2> {l, h};
      }
    }
  }
}
