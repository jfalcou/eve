//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/decorator/roundings.hpp>

#include <type_traits>

namespace eve
{
//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var mzero
//!   @brief Computes the negative zero value
//!
//!    For integral type there is no difference between eve::zero and eve::mzero,
//!    but for floating ones the bit of sign differs.
//!
//!    However, eve::mzero always satisfies the equality predicate with eve::zero.
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
//!      T mzero(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::mzero(as<T>())` is semantically equivalent to `T(-0.0)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/mzero.cpp}
//! @}
//================================================================================================


EVE_MAKE_CALLABLE(mzero_, mzero);

namespace detail
{
  template<typename T>
  requires(plain_scalar_value<element_type_t<T>>)
  EVE_FORCEINLINE constexpr auto mzero_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) { return T(-0.0f); }
    else if constexpr( std::is_same_v<t_t, double> ) { return T(-0.0); }
    else { return T(0); }
  }

  template<typename T, typename D>
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  EVE_FORCEINLINE constexpr auto mzero_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
  -> decltype(mzero(as<T>()))
  {
    return mzero(as<T>());
  }
}
}
