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

namespace eve
{
  template<typename Options>
  struct min_t : elementwise_callable<min_t, Options, pedantic_option, numeric_option>
  {
    template<eve::ordered_value T, ordered_value U>
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T t, U u) const noexcept { return EVE_DISPATCH_CALL(t, u); }

    template<eve::ordered_value T0, ordered_value T1, ordered_value... Ts>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0,  t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const & t) const noexcept  requires(kumi::size_v<Tup> >= 2) { return EVE_DISPATCH_CALL(t); }

    template<typename Callable>
    requires(!kumi::product_type<Callable> && !eve::ordered_value<Callable>)
    EVE_FORCEINLINE constexpr auto operator()(Callable const & f) const noexcept { return EVE_DISPATCH_CALL(f); }

    EVE_CALLABLE_OBJECT(min_t, min_);
  };


//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var min
//!   @brief Computes the  minimum  of its arguments.
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
//!      eve::common_value_t<T, Ts...> min(T x, Ts ... xs) noexcept;
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `xs...` :  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of the minimum  of the arguments is returned.
//!
//!   @note
//!     * If any element of the inputs is a `Nan`, the corresponding output element
//!       is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/min.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::min[mask](x, ...)` provides a masked
//!     version of `min` which is
//!     equivalent to `if_else(mask, min(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/min.cpp}
//!
//!   * eve::pedantic, eve::numeric
//!
//!     * The call `pedantic(min)(x,args,...)`  ensures the conformity
//!       to the standard behaviour, that is
//!       for two parameters  (on an  [elementwise](@ref glossary_elementwise) basis)
//!       to be semantically equivalent to:
//!       `(x < y) ? x : y` and this behaviour is also ensured on n parameters calls
//!       as if this scheme was recursively used.
//!
//!     *  The call `numeric(min)(x,args,...)`  ensures that  if any element of the
//!        inputs is not a `Nan`, the corresponding
//!        output element will not be a `Nan`.
//!
//!     **Example**
//!
//!        @godbolt{doc/core/pedantic/min.cpp}
//! @}
//================================================================================================
inline constexpr auto min = functor<min_t>;
}

#include <eve/module/core/regular/impl/min.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/min.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/min.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/min.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/min.hpp>
#endif
