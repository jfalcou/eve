//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MAKE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MAKE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/as.hpp>

namespace eve { namespace detail
{
  template<typename Pack, typename V0, typename... Values>
  EVE_FORCEINLINE Pack make(as_<Pack> const&, eve::emulated_ const&, V0 v0, Values... vs) noexcept
  {
    Pack that;
    std::size_t i=0;

    that[i++] = v0;
    ((that[i++] = vs),...);

    return that;
  }

  template<typename Pack, typename Value>
  EVE_FORCEINLINE Pack make(as_<Pack> const&, eve::emulated_ const&, Value vs) noexcept
  {
    Pack that;

    for(auto& e : that) e = vs;

    return that;
  }
} }

#endif
