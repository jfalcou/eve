//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/decorator/roundings.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/as.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_constants
  //! @{
  //!   @var zero
  //!   @brief Computes the constant 0
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
  //!      template< eve::value T >
  //!      T zero(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::zero(as<T>())` is semantically equivalent to  `T(0)`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/constant/zero.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(zero_, zero);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE T zero_(EVE_SUPPORTS(cpu_), eve::as<T> const &) noexcept
    {
      if constexpr ( kumi::product_type<T> )
      {
        // Can't just T{kumi::map} because that does not work for scalar product types
        T res;
        // This better inline.
        kumi::for_each([](auto& m) { m = zero(as(m)); }, res);

        return res;
      }
      else return T(0);
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto zero_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      return zero(as<T>());
    }
  }
}
