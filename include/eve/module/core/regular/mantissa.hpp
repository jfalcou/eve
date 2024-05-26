//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve
{

  template<typename Options>
  struct mantissa_t : elementwise_callable<mantissa_t, Options, raw_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(mantissa_t, mantissa_);
  };


//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var mantissa
//!   @brief Computes the IEEE mantissa of the floating value.
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
//!      T mantissa(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real argument](@ref eve::value).
//!
//!    In particular:
//!      *  `nan` returns nan
//!      *  zero returns zero
//!
//!    **Return value**
//!
//!    The value of the IEEE mantissa is returned.
//!
//! @note
//!    *  The exponent \f$e\f$ and mantissa \f$m\f$ of a floating point entry \f$x\f$
//!       are related by \f$x =  m\times 2^e\f$, with  \f$|m| \in \{0, nan\} \cup [1, 2[\f$.
//!
//!   @groupheader{Semantic Modifiers}
//!
//!   * raw Call
//!
//!     The call `eve::abs[raw](x)` is identical except that results for zero and nan
//!     inputs are unspecified.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/mantissa.cpp}
//! @}
//================================================================================================

  inline constexpr auto mantissa = functor<mantissa_t>;

  namespace detail
  {
    template<floating_value T, callable_options O>
    constexpr T  mantissa_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      auto r =  bit_or(bit_and(a, mantissamask(eve::as<T>())), one(eve::as<T>()));
      if constexpr(O::contains(raw2))
        return   bit_or(bit_and(a, mantissamask(eve::as<T>())), one(eve::as<T>()));
      else
        return  if_else(is_nan(a), allbits,  bit_or(bit_and(a, mantissamask(eve::as<T>())), one[is_nez(a)](eve::as<T>())));
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/mantissa.hpp>
#endif
