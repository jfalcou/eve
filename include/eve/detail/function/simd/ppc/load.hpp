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

#include <eve/as.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/spy.hpp>
#include <eve/memory/aligned_ptr.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto load(as_<wide<T, N>> const &tgt, eve::ppc_ const &, T const* ptr) noexcept
  {
    if constexpr( N::value * sizeof(T) >= limits<eve::vmx_>::bytes )
    {
      if constexpr( current_api == spy::vmx_ )
      {
        if constexpr( sizeof(T) <= 8 )
        {
          return vec_perm(vec_ld(0, ptr), vec_ld(16, ptr), vec_lvsl(0, ptr));
        }
        else
        {
          return load(tgt, cpu_ {}, ptr);
        }
      }
      else if constexpr( current_api == spy::vsx_ )
      {
        if constexpr( std::is_integral_v<T> )
        {
          using type = typename wide<T, N>::storage_type *;
          return vec_vsx_ld(0, type(ptr));
        }
        else
        {
          return vec_vsx_ld(0, ptr);
        }
      }
    }
    else
    {
      typename wide<T, N>::storage_type that;
      std::memcpy(&that, ptr, N::value * sizeof(T));
      return that;
    }
  }

  template<real_scalar_value T, typename N, std::size_t Align>
  EVE_FORCEINLINE auto
  load(as_<wide<T, N>> const &tgt, eve::ppc_ const &mode, aligned_ptr<T const, Align> ptr) noexcept
  {
    if constexpr( N::value * sizeof(T) >= limits<eve::vmx_>::bytes )
    {
      if constexpr( current_api == spy::vmx_ )
      {
        if constexpr( sizeof(T) <= 8 )
        {
          if constexpr( Align >= 16 )
          {
            return vec_ld(0, ptr.get());
          }
          else
          {
            return load(tgt, mode, ptr.get());
          }
        }
      }
      else if constexpr( current_api == spy::vsx_ )
      {
        if constexpr( std::is_integral_v<T> )
        {
          using type = typename wide<T, N>::storage_type *;
          return vec_vsx_ld(0, type(ptr.get()));
        }
        else
        {
          return vec_vsx_ld(0, ptr.get());
        }
      }
    }
    else
    {
      typename wide<T, N>::storage_type that;
      std::memcpy(&that, ptr.get(), N::value * sizeof(T));
      return that;
    }
  }

  template<real_scalar_value T, typename N, std::size_t Align>
  EVE_FORCEINLINE auto
  load(as_<wide<T, N>> const &tgt, eve::ppc_ const & mode, aligned_ptr<T, Align>  ptr) noexcept
  {
    return load(tgt, mode, aligned_ptr<T const, Align>(ptr));
  }
}

