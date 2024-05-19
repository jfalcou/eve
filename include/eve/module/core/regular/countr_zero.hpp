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
#include <eve/module/core/decorator/core.hpp>
#include <bit>

namespace eve
{
  template<typename Options>
  struct countr_zero_t : elementwise_callable<countr_zero_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(countr_zero_t, countr_zero_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var countr_zero
//!   @brief Computes the number of consecutive 0 in a value starting from right
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
//!      template< eve::value T >
//!      T countr_zero(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!      The value of the number of consecutive 0 ("zero") bits in the value of `x`, starting
//!      from the least significant bit ("right"), with same type as `x`,
//!      is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/countr_zero.cpp}
//! @}
//================================================================================================
  inline constexpr auto countr_zero = functor<countr_zero_t>;

  namespace detail
  {
    template<value T, callable_options O>
    EVE_FORCEINLINE constexpr T countr_zero_(EVE_REQUIRES(cpu_),
                                             O const&,
                                             T x) noexcept
    {
      if constexpr( scalar_value<T> )
        return T(std::countr_zero(x));
      else
      {
        //      return map(countr_zero, x); // TO DO
        constexpr auto siz = sizeof(eve::element_type_t<T>) * 8;
        using elt_t        = element_type_t<T>;
        x &= eve::inc(~x);
        T c(sizeof(elt_t) * 8 - 1);
        if constexpr( siz == 8 )
        {
          c -= if_else(is_nez(x & T(0x0F)), T(4), zero);
          c -= if_else(is_nez(x & T(0x33)), T(2), zero);
          c -= if_else(is_nez(x & T(0x55)), T(1), zero);
        }
        else if constexpr( siz <= 16 )
        {
          c -= if_else(is_nez(x & T(0x00FF)), T(8), zero);
          c -= if_else(is_nez(x & T(0x0F0F)), T(4), zero);
          c -= if_else(is_nez(x & T(0x3333)), T(2), zero);
          c -= if_else(is_nez(x & T(0x5555)), T(1), zero);
        }
        else if constexpr( siz == 32 )
        {
          c -= if_else(is_nez(x & T(0x0000FFFF)), T(16), zero);
          c -= if_else(is_nez(x & T(0x00FF00FF)), T(8), zero);
          c -= if_else(is_nez(x & T(0x0F0F0F0F)), T(4), zero);
          c -= if_else(is_nez(x & T(0x33333333)), T(2), zero);
          c -= if_else(is_nez(x & T(0x55555555)), T(1), zero);
        }
        else if constexpr( siz == 64 )
        {
          c -= if_else(is_nez(x & T(0x00000000FFFFFFFF)), T(32), zero);
          c -= if_else(is_nez(x & T(0x0000FFFF0000FFFF)), T(16), zero);
          c -= if_else(is_nez(x & T(0x00FF00FF00FF00FF)), T(8), zero);
          c -= if_else(is_nez(x & T(0x0F0F0F0F0F0F0F0F)), T(4), zero);
          c -= if_else(is_nez(x & T(0x3333333333333333)), T(2), zero);
          c -= if_else(is_nez(x & T(0x5555555555555555)), T(1), zero);
        }
        return if_else(is_eqz(x), sizeof(elt_t) * 8, c);
//        return inc[is_eqz(x)](c);
      }
    }
  }
}

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/countr_zero.hpp>
#endif
