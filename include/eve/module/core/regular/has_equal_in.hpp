//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/traits/common_value.hpp>
#include <eve/module/core/regular/is_equal.hpp>
#include <eve/module/core/regular/try_each_group_position.hpp>
#include <eve/module/core/regular/logical_or.hpp>
#include <eve/concept/invocable.hpp>

namespace eve
{
  template<typename Options>
  struct has_equal_in_t : callable<has_equal_in_t, Options>
  {
    template<simd_value T, simd_value U, simd_predicate<T, U> Op>
    constexpr EVE_FORCEINLINE std::invoke_result_t<Op, T, U> operator()(T x, U match_against, Op op) const noexcept
      requires (same_lanes<T, U>)
    {
      return EVE_DISPATCH_CALL(x, match_against, op);
    }

    template<simd_value T>
    constexpr EVE_FORCEINLINE as_logical_t<T> operator()(T x, T match_against) const noexcept
    {
      return EVE_DISPATCH_CALL(x, match_against, is_equal);
    }

    EVE_CALLABLE_OBJECT(has_equal_in_t, has_equal_in_);
  };

  //================================================================================================
  //! @addtogroup core_simd
  //! @{
  //!    @var has_equal_in
  //!    @brief
  //!    Given two simd_values: `x`, `match_against` returns a logical mask.
  //!    The res[i] == eve::any(x[i] == match_against);
  //!
  //!    Optional last parameter allows to ovewrite the equality from `eve::is_equal`
  //!    to an arbitrary simd binary predicate.
  //!
  //!    We took the idea for the operation from:
  //!    "Faster-Than-Native Alternatives for x86 VP2INTERSECT Instructions"
  //!    by Guillermo Diez-Canas.
  //!    Link: https://arxiv.org/abs/2112.06342
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template<simd_value T>
  //!      constexpr auto has_equal_in(T x, T match_against) noexcept;           // 1
  //!
  //!      template<simd_value T, typename Op>
  //!      constexpr auto has_equal_in(T x, T match_against, Op op) noexcept;    // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!     * `x` : [argument](@ref eve::simd_value).
  //!     * `match_against` [argument](@ref eve::simd_value).
  //!     * `op` : The binary predicate to use for the comparison.
  //!
  //!   **Return value**
  //!
  //!   1. A [logical SIMD value](@ref eve::logical_simd_value) built as described previously.
  //!   2. Same as 1. but uses a custom predicate instead of `eve::is_equal`.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/has_equal_in.cpp}
  //================================================================================================
  inline constexpr auto has_equal_in = functor<has_equal_in_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}

#include <eve/module/core/regular/impl/has_equal_in.hpp>

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/has_equal_in.hpp>
#endif
