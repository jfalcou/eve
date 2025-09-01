//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once


#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/bit_xor.hpp>
#include <eve/module/core/regular/bit_shl.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/traits/max_lanes.hpp>

namespace eve
{

  template<typename Options>
  struct bit_swap_pairs_t : strict_elementwise_callable<bit_swap_pairs_t, Options>
  {
    template<typename T, typename I0, typename I1>
    struct result
    {
      using type = detail::conditional_t<scalar_value<T> && scalar_value<I0> && scalar_value<I1>, T, as_wide_t<T, max_lanes_t<T, I0, I1>>>;
    };

    template<integral_value T, integral_value I0, integral_value I1>
    EVE_FORCEINLINE constexpr typename result<T, I0, I1>::type operator()(T v, I0 i0,  I1 i1) const noexcept
      requires same_lanes_or_scalar<T, I0, I1>
    {
      return EVE_DISPATCH_CALL(v, i0, i1);
    }

    template<integral_value T, std::ptrdiff_t I0, std::ptrdiff_t I1>
    EVE_FORCEINLINE constexpr T operator()(T a, index_t<I0> i0, index_t<I1> i1) const noexcept
    {
      return EVE_DISPATCH_CALL(a, i0, i1);
    }

    EVE_CALLABLE_OBJECT(bit_swap_pairs_t, bit_swap_pairs_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_swap_pairs
//!   @brief `strict_elementwise_callable` object swapping pairs.
//!
//!   @groupheader{Header file}
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
//!      // Regular overload
//!      constexpr auto bit_swap_pairs(integral_value auto x,
//!                                    integral_value auto i0, integral_value auto i1) noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto bit_swap_pairs[conditional_expr auto c](integral_value auto x,
//!                                    integral_value auto i0, integral_value auto i1) noexcept; // 2
//!      constexpr auto bit_swap_pairs[logical_value auto m](integral_value auto x,
//!                                     integral_value i0, integral_value auto i1) noexcept;     // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::integral_value).
//!     * `i0`: first index
//!     * `i1`: second index
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!       1. Return `x` with bit `i0` and `i1` swapped in each element of `x`. Assert if i0 or i1 are out of range.
//!       2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_swap_pairs.cpp}
//================================================================================================
  inline constexpr auto bit_swap_pairs = functor<bit_swap_pairs_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, conditional_expr C, value T, integral_value I0, integral_value I1>
    constexpr auto bit_swap_pairs_(EVE_REQUIRES(cpu_), C const& cx, O const&, T a, I0 i0, I1 i1) noexcept
    {
      if constexpr (scalar_value<T> && scalar_value<I0> && scalar_value<I1>)
      {
        return bit_swap_pairs(a, cx ? i0 : 0, cx ? i1 : 0);
      }
      else
      {
        using MC = max_lanes_t<T, I0, I1>;

        auto i0m = if_else(cx, as_wide_t<I0, MC>{i0}, zero);
        auto i1m = if_else(cx, as_wide_t<I1, MC>{i1}, zero);
        return bit_swap_pairs(as_wide_t<T, MC>{a}, i0m, i1m);
      }
    }

    template<callable_options O, value T, integral_value I0, integral_value I1>
    constexpr auto bit_swap_pairs_(EVE_REQUIRES(cpu_), O const&, T a, I0 i0, I1 i1) noexcept
    {
      // 1 if the bits of a at i0 and i1 are different, 0 otherwise
      auto x = bit_and(
                  bit_xor(
                      bit_shr(a, i0),
                      bit_shr(a, i1)
                  ),
                  one(as(a))
                );

      // if the bits are different, swap them by toggling both
      return bit_xor(a, bit_shl(x, i1), bit_shl(x, i0));
    }

    template<callable_options O, typename T, std::ptrdiff_t I0, std::ptrdiff_t I1>
    EVE_FORCEINLINE T bit_swap_pairs_(EVE_REQUIRES(cpu_), O const& o, T x, index_t<I0>, index_t<I1>) noexcept
    {
      constexpr std::ptrdiff_t C = sizeof(element_type_t<T>) * 8;
      static_assert((I0 >= 0) && (I1 >= 0) && (I0 < C) && (I1 < C), "some index(es) are out or range");
      return bit_swap_pairs[o](x, I0, I1);
    }
  }
}
