/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_nltz.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup trigonometric
  //! @{
  //! @var rempio2
  //!
  //! @brief Callable object computing the rempio2 value.
  //!
  //! **Required header:** `#include <eve/function/rempio2.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the rempio2 value   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_value T> auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!A tuple consisting of an flint value  designing the quadrant an two floating values of type T giving
  //!the remainder of `x` modulo \f$\pi/2\f$ and a corrective to the rounding erreor on the first result.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/rempio2.cpp
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

#include <eve/module/real/math/function/regular/generic/rempio2.hpp>
