//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_PPC_VMX_SLICE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_PPC_VMX_SLICE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <cstddef>

namespace eve::detail
{
  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE auto slice(wide<T, N, ppc_> const &a,
                             Slice const &) noexcept requires(wide<T, typename N::split_type>,
                                                              If<(N::value > 1)>)

  {
    if constexpr(Slice::value)
    {
      auto select = [](auto const &v, auto size) {
        auto mask = [&](auto... I) {
          auto                   offset = (sizeof(T) * size) / 2;
          __vector unsigned char m      = {static_cast<std::uint8_t>(offset + I % offset)...};
          return m;
        };

        return vec_perm(v.storage(), v.storage(), apply<16>(mask));
      };

      return wide<T, typename N::split_type>(select(a, N{}));
    }
    else
    {
      return wide<T, typename N::split_type>(a.storage());
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE auto
  slice(wide<T, N, ppc_> const &a) noexcept requires(std::array<wide<T, typename N::split_type>, 2>,
                                                     If<(N::value > 1)>)
  {
    std::array<wide<T, typename N::split_type>, 2> that{slice(a, lower_), slice(a, upper_)};
    return that;
  }
}

#endif
