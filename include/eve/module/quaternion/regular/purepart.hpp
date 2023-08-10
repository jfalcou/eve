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
  //! @var purepart
  //!
  //! @brief Callable object computing purepart part of values.
  //!
  //! **Defined in header** `#include <eve/module/quaternion.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of purepart part                              |
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
  //! or the purepart (second component) of `x`
  //! if x is an instance of eve::quaternion.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/quaternion/regular/purepart.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct purepart_; }
  template<> struct supports_conditional<tag::purepart_> : std::false_type {};

  EVE_MAKE_CALLABLE(purepart_, purepart);

  namespace detail
  {
    template<value V>
    EVE_FORCEINLINE auto purepart_( EVE_SUPPORTS(cpu_), V const& ) noexcept
    {
      return std::array<V, 3>{0, 0, 0};
    }

    template<value V>
    EVE_FORCEINLINE auto purepart_( EVE_SUPPORTS(cpu_), eve::complex<V> const & z) noexcept
    {
      return  std::array<V, 3>{imag(z), 0, 0};
    }
  }
}
