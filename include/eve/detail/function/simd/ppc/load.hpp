//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/spy.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/pointer.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, simd_compatible_ptr<wide<T,N>> Ptr>
  EVE_FORCEINLINE wide<T, N> load_( EVE_SUPPORTS(vmx_)
                                  , ignore_none_ const&, safe_type const&
                                  , eve::as<wide<T, N>> const& tgt, Ptr ptr
                                  )
  requires ppc_abi<abi_t<T, N>>
  {
    if constexpr( N::value * sizeof(T) >= ppc_::bytes )
    {
      if constexpr( current_api >= eve::vsx )
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
      else if constexpr( current_api >= eve::vmx )
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
    }
    else
    {
      typename wide<T, N>::storage_type that{};
      std::memcpy(&that, ptr, N::value * sizeof(T));
      return that;
    }
  }

  template<real_scalar_value T, real_scalar_value U, typename N, typename Lanes>
  EVE_FORCEINLINE wide<T, N> load_( EVE_SUPPORTS(vmx_)
                                  , ignore_none_ const&, safe_type const&
                                  , eve::as<wide<T, N>> const& tgt
                                  , aligned_ptr<U, Lanes> ptr
                                  )
  requires ppc_abi<abi_t<T, N>> && simd_compatible_ptr<aligned_ptr<U, Lanes>,wide<T, N>>
  {
    if constexpr( N::value * sizeof(T) >= ppc_::bytes )
    {
      if constexpr( current_api >= eve::vsx )
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
      else if constexpr( current_api >= eve::vmx )
      {
        if constexpr( sizeof(T) <= 8 )
        {
          if constexpr( aligned_ptr<T, Lanes>::alignment() >= 16 )  return vec_ld(0, ptr.get());
          else                                                      return load(tgt, ptr.get());
        }
      }
    }
    else
    {
      typename wide<T, N>::storage_type that{};
      std::memcpy(&that, ptr.get(), N::value * sizeof(T));
      return that;
    }
  }
}
