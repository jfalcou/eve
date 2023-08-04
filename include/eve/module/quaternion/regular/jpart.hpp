//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var jpart
  //!
  //! @brief Callable object computing jpart part of values.
  //!
  //! **Defined in header** `#include <eve/module/quaternion.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of jpart part                              |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value).
  //!
  //! **Return value**
  //! 0 if `x` is real or complex or the jpart (third component) of `x` if
  //! x is an instance of eve::quaternion.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/quaternion/regular/jpart.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct jpart_; }
  template<> struct supports_conditional<tag::jpart_> : std::false_type {};

  EVE_MAKE_CALLABLE(jpart_, jpart);

  namespace detail
  {
    template<value V>
    EVE_FORCEINLINE V jpart_( EVE_SUPPORTS(cpu_), V const& ) noexcept
    {
      return V(0);
    }

    template<value V>
    EVE_FORCEINLINE V jpart_( EVE_SUPPORTS(cpu_), eve::complex<V> const & ) noexcept
    {
      return V(0);
    }
  }
}
