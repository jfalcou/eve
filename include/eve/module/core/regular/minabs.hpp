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

namespace eve
{

  template<typename Options>
  struct minabs_t : tuple_callable<minabs_t, Options, numeric_option, pedantic_option, saturated_option>
  {
    template<eve::ordered_value T0, ordered_value T1, ordered_value... Ts>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr  kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup t) const noexcept  requires(kumi::size_v<Tup> >= 2) { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(minabs_t, minabs_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var minabs
//!   @brief Computes the  minimum  of the absolute value of its arguments.
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
//!      auto minabs(T x, Ts ... xs) noexcept;
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `xs...` : [real](@ref eve::value) arguments.
//!
//!    **Return value**
//!
//!    The value of the minimum of the absolute value of the arguments is returned.
//!
//!   @note
//!     * If any element of the inputs is a `Nan`, the corresponding output element
//!       is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/minabs.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::minabs[mask](x, ...)` provides a masked
//!     version of `minabs` which is
//!     equivalent to `if_else(mask, minabs(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/minabs.cpp}
//!
//!   * eve::pedantic, eve::numeric
//!
//!     * The call `pedantic(minabs)(x,args,...)`  ensures the conformity
//!       to the standard behaviour, that is
//!       for two parameters  (on an  [elementwise](@ref glossary_elementwise) basis)
//!       to be semanticaly equivalent to:
//!       `(|x| < |y|) ? |x| : |y|` and this behaviour is also ensured on n parameters calls
//!       as if this scheme was recursively used.
//!
//!     *  The call `numeric(minabs)(x,args,...)`  ensures that  if any element of the
//!        inputs is not a `Nan`, the corresponding
//!        output element will not be a `Nan`.
//!
//!     **Example**
//!
//!        @godbolt{doc/core/pedantic/minabs.cpp}
//! @}
//================================================================================================
inline constexpr auto minabs = functor<minabs_t>;
}

#include <eve/module/core/regular/impl/minabs.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/minabs.hpp>
#endif
