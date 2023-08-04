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
  //! @var kpart
  //!
  //! @brief Callable object computing kpart part of values.
  //!
  //! **Defined in header** `#include <eve/module/quaternion.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of kpart part                              |
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
  //! 0 if `x` is real or complex or the kpart (third component)  of `x`
  //! if x is an instance of eve::quaternion.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/quaternion/regular/kpart.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct kpart_; }
  template<> struct supports_conditional<tag::kpart_> : std::false_type {};

  EVE_MAKE_CALLABLE(kpart_, kpart);

  namespace detail
  {
    template<value V>
    EVE_FORCEINLINE V kpart_( EVE_SUPPORTS(cpu_), V const& ) noexcept
    {
      return V(0);
    }

    template<value V>
    EVE_FORCEINLINE V kpart_( EVE_SUPPORTS(cpu_), eve::complex<V> const & ) noexcept
    {
      return V(0);
    }
  }
}
