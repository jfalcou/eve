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
  struct negminabs_t : tuple_callable<negminabs_t, Options, numeric_option, pedantic_option, saturated_option>
  {
    template<eve::ordered_value T0, ordered_value T1, ordered_value... Ts>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr  kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup t) const noexcept  requires(kumi::size_v<Tup> >= 2) { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(negminabs_t, negminabs_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var negminabs
//!   @brief Computes the negated value of the element of  the minimal absolute value.
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
//!      template< eve::value T,  eve::value... Ts>
//!      eve::common_value_t<T, Ts ...> negminabs( T x, Ts ... xs ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,  `...xs`: [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The negated negated value of the element of the minimal  absolute value
//!    is returned.
//!
//!    @note
//!     If any element of the inputs is a NaN,
//!     the corresponding output element is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/negminabs.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::negminabs[mask](x, ...)` provides a masked version of `eve::negminabs` which
//!     is equivalent to `eve::if_else (mask, negminabs(x, ...), x)`
//!
//!   * eve::pedantic,  eve::numeric
//!
//!     The call `d(eve::negminabs)(...)`, where d is one of these two decorators has the
//!     same behaviour,  but internally `d(eve::min)` is used.
//!
//! @}
//================================================================================================
inline constexpr auto negminabs = functor<negminabs_t>;
}

#include <eve/module/core/regular/impl/negminabs.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/negminabs.hpp>
#endif
