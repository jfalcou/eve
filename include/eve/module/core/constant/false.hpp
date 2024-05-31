//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
template<typename Options>
struct false_t : constant_callable<false_t, Options, downward_option, upward_option>
{
  template<typename T>
  static constexpr EVE_FORCEINLINE as_logical_t<T> value(eve::as<T> const&, auto const&)
  {
    return as_logical_t<T>(false);
  }

  template<typename T>
  EVE_FORCEINLINE constexpr as_logical_t<T>  operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(false_t, false__);
};

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var false_
//!   @brief Computes the false logical value.
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
//!      template<eve::value T> constexpr eve::as_logical<T> false_(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!   **Return value**
//!
//!   The call `eve::false_(as<T>())` returns the `false` logical value for type `T`.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/core/constant/false_.cpp}
//! @}
//================================================================================================
inline constexpr auto false_ = functor<false_t>;
}
