/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math
  //! @{
  //! @var rempio2
  //!
  //! @brief Callable object computing the rempio2 value.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the rempio2 value                       |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_value T> auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //! A tuple consisting of an [flint](@ref eve::is_flint) value designing the quadrant and two
  //! floating values of type `T` giving the remainder of `x` modulo \f$\pi/2\f$ and a corrective
  //! to the rounding error on the first result.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/rempio2.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct rempio2_; }

  namespace detail
  {

    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::rempio2_), [[maybe_unused]]  T const& x)
    {
      EVE_ASSERT(eve::all(is_nltz(x)), "[eve::rempio2] :  parameter must be positive or nan, found:" << x);
    }
 }


  namespace tag { struct rempio2_; }
  template<> struct supports_conditional<tag::rempio2_> : std::false_type {};

  EVE_MAKE_CALLABLE(rempio2_, rempio2);
}

#include <eve/module/math/regular/impl/rempio2.hpp>
