//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_PPC_VSX_LOAD_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_PPC_VSX_LOAD_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/as.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

#if defined(EVE_COMP_IS_GNUC)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wignored-attributes"
#  pragma GCC diagnostic ignored "-Wdeprecated"
#endif

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto load(as_<wide<T, N>> const &,
                            eve::ppc_ const &,
                            T *ptr) noexcept
  requires(typename wide<T, N>::storage_type,
           Vectorizable<T>,
           If<(sizeof(T) == 8)>)
  {
    if constexpr(std::is_integral_v<T>)
    {
      using type = typename wide<T, N>::storage_type *;
      return vec_vsx_ld(0, type(ptr));
    }
    else
    {
      return vec_vsx_ld(0, ptr);
    }
  }

  template<typename T, typename N, std::size_t Align>
  EVE_FORCEINLINE auto
  load(as_<wide<T, N>> const &,
       eve::ppc_ const &,
       aligned_ptr<T, Align> ptr) noexcept
  requires(typename wide<T, N>::storage_type,
           Vectorizable<T>,
           If<(sizeof(T) == 8)>)
  {
    if constexpr(std::is_integral_v<T>)
    {
      using type = typename wide<T, N>::storage_type *;
      return vec_vsx_ld(0, type(ptr.get()));
    }
    else
    {
      return vec_vsx_ld(0, ptr.get());
    }

    using type = typename wide<T, N>::storage_type *;
    return vec_vsx_ld(0, type(ptr.get()));
  }
}

#if defined(EVE_COMP_IS_GNUC)
#  pragma GCC diagnostic pop
#endif

#endif
