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
#include <eve/forward.hpp>
#include <eve/module/core/regular/countl_zero.hpp>

namespace eve
{
  template<typename Options>
  struct bit_width_t : elementwise_callable<bit_width_t, Options, saturated_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(bit_width_t, bit_width_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_width
//!   @brief Computes elementwise the number of bits needed to store the parameter.
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
//!      template< eve::unsigned_value T >
//!      T bit_width(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [unsigned argument](@ref eve::unsigned_value).
//!
//!    **Return value**
//!
//!    The value of  number of bits needed to store the value `x`,  i.e.
//!    \f$1+\lfloor\log2(x)\rfloor\f$
//!    is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/bit_width.cpp}
//! @}
//================================================================================================
  inline constexpr auto bit_width = functor<bit_width_t>;

  namespace detail
  {
    template<unsigned_value T, callable_options O>
    constexpr T  bit_width_(EVE_REQUIRES(cpu_), O const&, T const& v) noexcept
    {
      using elt_t = element_type_t<T>;
      return sizeof(elt_t) * 8 - countl_zero(v);
    }
  }
}
