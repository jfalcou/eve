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
  struct count_true_t : elementwise_callable<count_true_t, Options>
  {
    constexpr EVE_FORCEINLINE ptrdiff_t operator()(bool v) const  noexcept
    { return EVE_DISPATCH_CALL(v); }

    template<eve::value T>
    constexpr EVE_FORCEINLINE ptrdiff_t operator()(logical<T> v) const  noexcept
    { return EVE_DISPATCH_CALL(v); }

    template<logical_simd_value L>
    constexpr EVE_FORCEINLINE ptrdiff_t operator()(top_bits<L> m) const  noexcept
    { return EVE_DISPATCH_CALL(m); }

    EVE_CALLABLE_OBJECT(count_true_t, count_true_);
  };


//================================================================================================
//! @addtogroup core_reduction
//! @{
//!   @var count_true
//!   @brief Computes the number of non 0 elements
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
//!      T count_true(T x) noexcept;                 //1
//!   }
//!      template< eve::top_bits M >
//!      as_wide_as<unsigned, M> any(M m) noexcept;  //2
//!   }
//!   @endcode
//!
//!   * 1. The T value  of the number of non 0 elements.
//!   * 2  The unsigned  value  of the number of non 0 elements.
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of the number of non 0 elements
//!    is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/count_true.cpp}
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::$name$[mask](x, ...)` provides a masked
//!     version of `count_true which count the non masked non zero element
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/count_true.cpp}
//! @}
//================================================================================================
inline constexpr auto count_true = functor<count_true_t>;

}

#include <eve/module/core/regular/impl/count_true.hpp>

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/count_true.hpp>
#endif
