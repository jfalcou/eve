//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/interleave.hpp>
#include <eve/constant/zero.hpp>

namespace eve::detail
{
  template<typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N> convert_impl ( EVE_SUPPORTS(vsx_)
                                          , wide<double,N> v, as<U> const &tgt
                                          ) noexcept
  requires ppc_abi<abi_t<double, N>>
  {
    constexpr auto c_o = categorize<wide<U, N>>();
    auto r = v.storage();

          if constexpr(c_o == category::int64x2  ) return vec_cts(r, 0);
    else  if constexpr(c_o == category::uint64x2 ) return vec_ctu(r, 0);
    else  return map(convert,v,tgt);
  }

  template<typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N> convert_impl ( EVE_SUPPORTS(vmx_)
                                          , wide<float,N> v, as<U> const &tgt
                                          ) noexcept
  requires ppc_abi<abi_t<float, N>>
  {
    constexpr auto c_o = categorize<wide<U, N>>();
    auto r = v.storage();

          if constexpr(c_o == category::int32x4  ) return vec_cts(r, 0);
    else  if constexpr(c_o == category::uint32x4 ) return vec_ctu(r, 0);
    else  return map(convert,v,tgt);
  }

  template<integral_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N> convert_impl ( EVE_SUPPORTS(vmx_)
                                          , wide<T,N> v, as<U> const &tgt
                                          ) noexcept
  requires ppc_abi<abi_t<T, N>>
  {
    if constexpr(std::is_floating_point_v<U>)
    {
      if constexpr(sizeof(T) == sizeof(U))  return vec_ctf(v.storage(), 0);
      else                                  return convert( convert(v, as<as_integer_t<U>>{}), tgt);
    }
    else  if constexpr(std::is_integral_v<U>)
    {
      // k->2.k integral conversion use interleave
      if constexpr(sizeof(U)/sizeof(T) == 2)
      {
        if constexpr(N::value == 1)
        {
          return wide<U,N>{static_cast<U>(v.get(0))};
        }
        else
        {
          auto il = [](auto w)
          {
            if constexpr(std::is_signed_v<T>) return eve::interleave((w<0).mask(),w);
            else                              return eve::interleave(zero(as(w)),w);
          };

          auto[l,h] = il(v);
          eve::wide<U,N> that { eve::bit_cast(l, eve::as<eve::wide<U,typename N::split_type>>{})
                              , eve::bit_cast(h, eve::as<eve::wide<U,typename N::split_type>>{})
                              };
          return that;
        }
      }
      // k->2^n.k integral conversion use computed vec_perm
      else if constexpr(sizeof(T)/sizeof(U) >= 2)
      {
        // Compute the byte index from the relative sizeof
        constexpr auto idx = [](auto I)
        {
          return ((1+I/sizeof(U)) * sizeof(T))-sizeof(U) + I%sizeof(U);
        };

        // Use a raw mask
        auto mask = [&]<std::size_t... I>(std::index_sequence<I...>)
        {
          using type = __vector unsigned char;
          return type{(idx(I)<16 ? idx(I) : 128)...};
        }(std::make_index_sequence<16>{});

        // Extract relevant bytes from the largest integer
        auto bv = bit_cast(v, as<typename wide<T,N>::template rebind<std::uint8_t>>{});
        return bit_cast( vec_perm(bv.storage(),bv.storage(), mask), as<wide<U,N>>{} );
      }
      else return convert_integers(v,tgt);
    }
  }
}
