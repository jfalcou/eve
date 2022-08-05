//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var ulpdist
//!   @brief Computes the unit in the last place distance of its [arguments](@ref eve::value).
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
//!      template< eve::value T, eve::value U >
//!      eve::common_compatible_t<T, U> ulpdist(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!      Computes [elementwise](@ref glossary_elementwise) the
//!      'units in the last place' distance
//!      betwween `x` and `y`. This is semantically equivalent to:`
//!
//!      * if is_ordered(x,y), nb_values(x,y)/2.0 is returned
//!      * otherwise a `Nan` is returned
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/ulpdist.cpp}
//!
//! @}
//================================================================================================

namespace tag
{
  struct ulpdist_;
}
template<> struct supports_conditional<tag::ulpdist_> : std::false_type
{};

EVE_MAKE_CALLABLE(ulpdist_, ulpdist);
}

#include <eve/module/core/regular/impl/ulpdist.hpp>
