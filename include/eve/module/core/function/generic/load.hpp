//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <type_traits>

namespace eve
{
  template<typename T> concept scalar_pointer = requires(T a)
  {
    { *a };
    requires scalar_value<std::remove_cvref_t<decltype(*a)>>;
  };
}

namespace eve::detail
{
  //================================================================================================
  // SIMD
  //================================================================================================
  template<scalar_pointer Ptr>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), Ptr ptr) noexcept
                  -> as_wide_t<std::remove_cvref_t<decltype(*std::declval<Ptr>())>>
  {
    return as_wide_t<std::remove_cvref_t<decltype(*ptr)>>(ptr);
  }

  template<scalar_pointer Ptr, typename Cardinal>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), Ptr ptr, Cardinal const &) noexcept
                  -> as_wide_t<std::remove_cvref_t< decltype(*std::declval<Ptr>())>
                                                  , typename Cardinal::type
                                                  >
  {
    return as_wide_t<std::remove_cvref_t<decltype(*ptr)>, typename Cardinal::type>(ptr);
  }

  //================================================================================================
  // Scalar support
  //================================================================================================
  template<scalar_pointer Ptr>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), Ptr p, scalar_cardinal const&) noexcept
  {
    return *p;
  }

  template<scalar_pointer Ptr, scalar_value T>
  EVE_FORCEINLINE auto load_( EVE_SUPPORTS(cpu_)
                            , converter_type<T> const&, Ptr p, scalar_cardinal const&
                            ) noexcept
  {
    return static_cast<T>(*p);
  }
}
