//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_FILL_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_FILL_HPP_INCLUDED

#include <eve/arch.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename Generator, typename ABI, typename Pack>
  EVE_FORCEINLINE auto
  fill(as_<Pack> const&, ABI const&, Generator&& g, int offset = 0) noexcept
  {
    if constexpr(is_aggregated_v<ABI>)
    {
      using sub_t = typename Pack::storage_type::value_type;

      return combine( EVE_CURRENT_API{},
                      sub_t ( [&](auto i, auto c)
                              {
                                return std::forward<Generator>(g)(i,Pack::static_size);
                              }
                            ),
                      sub_t ( [&](auto i, auto c)
                              {
                                return std::forward<Generator>(g)(i+Pack::static_size/2,Pack::static_size);
                              }
                            )
                    );
    }
    else
    {
      Pack that;

      for(typename Pack::size_type i = 0; i < Pack::static_size; ++i)
        that[i] = std::forward<Generator>(g)(i, Pack::static_size);

      return that;
    }
  }
}

#if defined(EVE_COMP_IS_GNUC)
#  pragma GCC diagnostic pop
#endif


#endif
