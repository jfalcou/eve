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
  //! @var axis
  //!
  //! @brief Callable object computing axisinary part of values.
  //!
  //! **Defined in header** `#include <eve/module/quaternion.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of axis part                         |
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
  //! @godbolt{doc/quaternion/regular/axis.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct axis_; }
  template<> struct supports_conditional<tag::axis_> : std::false_type {};

  EVE_MAKE_CALLABLE(axis_, axis);

  namespace detail
  {
    template<value V>
    EVE_FORCEINLINE auto axis_( EVE_SUPPORTS(cpu_), V const &) noexcept
    {
      return std::array<V, 3>{1, 0, 0}; //it's identitity here so I choose as axis what I want
    }

    template<value V>
    EVE_FORCEINLINE V axis_( EVE_SUPPORTS(cpu_), eve::complex<V> const & z) noexcept
    {
      return std::array<V, 3>{imag(z)/abs(z), 0, 0};
    }
  }
}
