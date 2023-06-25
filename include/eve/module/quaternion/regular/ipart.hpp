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
  //! @var ipart
  //!
  //! @brief Callable object computing ipart part of values.
  //!
  //! **Defined in header** `#include <eve/module/quaternion.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of ipart part                              |
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
  //! 0 if `x` is real, imag(x) if x is an instance of eve::complex,
  //! or the ipart (second component) of `x`
  //! if x is an instance of eve::quaternion.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/quaternion/regular/ipart.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct ipart_; }
  template<> struct supports_conditional<tag::ipart_> : std::false_type {};

  EVE_MAKE_CALLABLE(ipart_, ipart);

  namespace detail
  {
    template<value V>
    EVE_FORCEINLINE V ipart_( EVE_SUPPORTS(cpu_), V const& ) noexcept
    {
      return V(0);
    }

    template<value V>
    EVE_FORCEINLINE V ipart_( EVE_SUPPORTS(cpu_), eve::complex<V> const & z) noexcept
    {
      return imag(z);
    }
  }
}
