//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/concept/value.hpp>

namespace eve
{

  template<typename Options>
  struct maxabs_t : elementwise_callable<maxabs_t, Options, numeric_option, pedantic_option, saturated_option>
  {
    template<eve::ordered_value T0, ordered_value T1, ordered_value... Ts>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr  kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup t) const noexcept  requires(kumi::size_v<Tup> >= 2) { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(maxabs_t, maxabs_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var maxabs
//!   @brief Computes the  maximum  of the absolute value of its arguments.
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
//!      template< eve::value T, eve::value... Ts >
//!      auto maxabs(T x, Ts ... xs) noexcept;
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `xs...` : [real](@ref eve::value) arguments
//!
//!    **Return value**
//!
//!    The value of the maximum of the absolute value of the arguments is returned.
//!
//!   @note
//!     * If any element of the inputs is a `Nan`, the corresponding output element
//!       is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/maxabs.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::maxabs[mask](x, ...)` provides a masked
//!     version of `maxabs` which is
//!     equivalent to `if_else(mask, maxabs(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/maxabs.cpp}
//!
//!   * eve::pedantic, eve::numeric
//!
//!     * The call `pedantic(maxabs)(x,args,...)`  ensures the conformity
//!       to the standard behaviour, that is
//!       for two parameters  (on an  [elementwise](@ref glossary_elementwise) basis)
//!       to be semanticaly equivalent to:
//!       `(|x| < |y|) ? |y| : |x|` and this behaviour is also ensured on n parameters calls
//!       as if this scheme was recursively used.
//!
//!     *  The call `numeric(maxabs)(x,args,...)`  ensures that  if any element of the
//!        inputs is not a `Nan`, the corresponding
//!        output element will not be a `Nan`.
//!
//!     **Example**
//!
//!        @godbolt{doc/core/pedantic/maxabs.cpp}
//! @}
//================================================================================================
inline constexpr auto maxabs = functor<maxabs_t>;
}

namespace eve::detail
{
  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
  maxabs_(EVE_REQUIRES(cpu_), O const & o, T0 a0, T1 a1, Ts... as) noexcept
  {
    auto abso = abs[o.drop(pedantic2,numeric2)];
    return eve::max[o.drop(saturated2)](abso(a0), abso(a1), abso(as)...);
  }

  template<kumi::non_empty_product_type Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto maxabs_(EVE_REQUIRES(cpu_), O const & o, Ts tup) noexcept
  {
    return kumi::apply( [&](auto... a) { return eve::maxabs[o](a...); }, tup);
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/maxabs.hpp>
#endif
