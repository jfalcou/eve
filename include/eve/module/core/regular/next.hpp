//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/is_gez.hpp>
#include <eve/concept/value.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_internal
  //! @{
  //!   @var next
  //!   @brief Computes the nth next representable element
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
  //!      template< eve::value T, eve::integral_value N >
  //!      eve::common_compatible_t<T, U> next(T x, N n = 1) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`:  [floating argument](@ref eve::floating_value).
  //!
  //!     * `n` :  [integral value argument](@ref eve::integral_value).
  //!
  //!    **Return value**
  //!
  //!    The value of the nth representable value greater than `x` is returned.
  //!    If `n` is zero returns `x`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/next.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::next[mask](x, ...)` provides a masked
  //!     version of `next` which is
  //!     equivalent to `if_else(mask, next(x, ...), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/next.cpp}
  //!
  //!   * eve::pedantic
  //!
  //!     The call `eve::pedantic(eve::next)(x, ...)` provides a pedantic
  //!     version of `next` which ensures that the successor of eve::mzero is  eve::zero
  //!     for floating points entries
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/next.cpp}
  //!
  //!   * eve::saturated
  //!
  //!     The call `eve::pedantic(eve::next)(x, ...)` provides a pedantic
  //!     version of `next` which ensures that eve::minf and  eve::nan are fixed points.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/next.cpp}
  //!
  //! @}
  //================================================================================================
  namespace tag { struct next_; }

  namespace detail
  {
    template<conditional_expr C, value T, integral_value U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::next_),  C const &
                              , T const& ,  [[ maybe_unused]] U const & n)
    {
      EVE_ASSERT(eve::all(is_gez(n)), "[eve::next] : second parameter must be positive");
    }
    template<value T, integral_value U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::next_), T const& ,  [[ maybe_unused]] U const & n)
    {
      EVE_ASSERT(eve::all(is_gez(n)), "[eve::next] : second parameter must be positive");
    }

    template<conditional_expr C, value T, integral_value U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(saturated_type, eve::tag::next_),  C const &
                              , T const&,  [[ maybe_unused]] U const & n)
    {
      EVE_ASSERT(eve::all(is_gez(n)), "[eve::next] : second parameter must be positive");
    }
    template<value T, integral_value U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(saturated_type, eve::tag::next_), T const&,  [[ maybe_unused]]  U const & n)
    {
      EVE_ASSERT(eve::all(is_gez(n)), "[[eve::saturated([eve::next)] : second parameter must be positive");
    }
  }

  EVE_MAKE_CALLABLE(next_, next);
}

#include <eve/module/core/regular/impl/next.hpp>
