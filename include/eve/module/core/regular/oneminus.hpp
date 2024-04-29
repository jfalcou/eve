//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/binarize.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>

namespace eve
{
  template<typename Options>
  struct oneminus_t : elementwise_callable<oneminus_t, Options, saturated_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const
    { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(oneminus_t, oneminus_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var oneminus
//!   @brief Computes the value of one minus the input.
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
//!      T oneminus(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) argument.
//!
//!    **Return value**
//!
//!    The value of `1-x` is returned.
//!
//!    @note
//!      If an  [element](@ref glossary_elementwise) of the expected result is not representable in
//!      the result type, the corresponding result [element](@ref glossary_elementwise) is
//!      undefined.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/oneminus.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::oneminus[mask](x, ...)` provides a masked
//!     version of `oneminus` which is
//!     equivalent to `if_else(mask, oneminus(x, ...), x)`
//!
//!   * eve::saturated
//!
//!      The call `saturated(oneminus)(x)` is semantically equivalent to `eve::saturated(eve::sub)(
//!      eve::one (as(x)), x)` and is never undefined.
//!
//! @}
//================================================================================================
  inline constexpr auto oneminus = functor<oneminus_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    oneminus_(EVE_REQUIRES(cpu_), O const &, T v) noexcept
    {
      using elt_t = element_type_t<T>;
      if constexpr( std::is_floating_point_v<elt_t> || !O::contains(saturated2) )
      {
        return one(eve::as<T>()) - v;
      }
      else
      {
        if constexpr( std::is_unsigned_v<elt_t> )
        {
          return binarize(is_eqz(v));
        }
        else if constexpr( scalar_value<T> )
        {
          return (v <= valmin(eve::as(v)) + 2) ? valmax(eve::as(v)) : oneminus(v);
        }
        else if constexpr( simd_value<T> )
        {
          return if_else(v < valmin(eve::as(v)) + 2, valmax(eve::as(v)), oneminus(v));
        }
      }
    }
  }
}
