//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/complex.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var angle
  //!
  //! @brief Callable object computing angleinary part of values.
  //!
  //! **Defined in header** `#include <eve/module/quaternion.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of angle part                         |
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
  //!   (1, 0, 0) if `x` is real or the unreal part of `x/abs(x)` if x is an instance of eve::quaternion or eve::complex
  //!
  //! #### Example
  //!
  //! @godbolt{doc/quaternion/regular/angle.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct angle_; }
  template<> struct supports_conditional<tag::angle_> : std::false_type {};

  EVE_MAKE_CALLABLE(angle_, angle);

  namespace detail
  {
    template<value V>
    EVE_FORCEINLINE auto angle_( EVE_SUPPORTS(cpu_), V const &) noexcept
    {
      return V(0); //it's identitity here so I choose as angle what I want
    }

    template<value V>
    EVE_FORCEINLINE V angle_( EVE_SUPPORTS(cpu_), eve::complex<V> const & z) noexcept
    {
      return 2*arg(z);
    }
  }
}
