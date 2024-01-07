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
struct allbits_t : constant_callable<allbits_t, Options, downward_option, upward_option>
{
  template<typename T>
  static EVE_FORCEINLINE T value(eve::as<T> const&, auto const&)
  {
    using e_t           = element_type_t<T>;
    using i_t           = as_integer_t<e_t, unsigned>;
    constexpr auto mask = ~0ULL;

    if constexpr( std::integral<e_t> ) return T(mask);
    else                               return T(bit_cast(i_t(mask), as<e_t>()));
  }

  template<typename T>
  requires(plain_scalar_value<element_type_t<T>>)
  EVE_FORCEINLINE T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(allbits_t, allbits_);
};

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var allbits
//!   @brief Computes a constant with all bits set.
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
//!     template<eve::value T> constexpr T allbits(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!   **Return value**
//!
//!   The call `eve::allbits(as<T>())` returns a value of type `T` with all bits set.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/core/constant/allbits.cpp}
//! @}
//================================================================================================
inline constexpr auto allbits = functor<allbits_t>;

// Required for if_else optimisation detections
using callable_allbits_ = tag_t<allbits>;
}
