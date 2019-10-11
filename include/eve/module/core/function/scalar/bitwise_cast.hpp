//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_CAST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_CAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/as.hpp>
#include <cstring>

namespace eve::detail
{
  template<typename T, typename Target>
  EVE_FORCEINLINE auto bitwise_cast_(EVE_SUPPORTS(cpu_),
                                     T const &a,
                                     as_<Target> const &) noexcept
  requires(Target, Vectorizable<T>)
  {
    if constexpr(std::is_same_v<T, Target>)
    {
      return a;
    }
    else
    {
      Target that;

      void const *src = reinterpret_cast<detail::alias_t<void const> *>(&a);
      void *      dst = reinterpret_cast<detail::alias_t<void> *>(&that);
      std::memcpy(dst, src, sizeof(a));

      return that;
    }
  }
}

#endif
