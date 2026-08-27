//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/store_equivalent.hpp>
#include <eve/module/core/regular/unalign.hpp>
#include <eve/module/core/regular/write.hpp>

namespace eve::_
{
  struct scatter_helper_t
  {

    // Single-value scatter
    template<typename T, typename O>
    static EVE_FORCEINLINE void sc(auto base, auto idx, auto vn, auto vc, auto vv) noexcept
    {
      // We only write if mask is set
      if constexpr(match_option<condition_key,O,ignore_none_>) write(vv.get(vn),base+idx.get(vn));
      else
      {
        auto vm = vc.mask( as<as_logical_t<T>>{} );
        if(vm.get(vn)) write(vv.get(vn),base+idx.get(vn));
      }
    };
  };

  template<typename T, typename Idx, typename Ptr, callable_options O>
  EVE_FORCEINLINE void scatter_(EVE_REQUIRES(cpu_), O const& o, T const& v, Ptr p, Idx const& idx)
  {
    // Aggregate can be optimised if there is no mask
    // Mask would require slice on ignore_*** which we don't do atm
    if constexpr(aggregated_abi<T> && !O::contains(condition_key))
    {
      // slice and scatter both parts;
      auto[lv,hv] = v.slice();
      auto[li,hi] = idx.slice();

      // Unalign is required as the alignment of p (if any) is on the total size not the small one
      scatter[o](hv,unalign(p) + lv.size(),hi);
      scatter[o](lv,p                     ,li);
    }
    else
    {
      // Retrieve element to scatter
      auto se   = store_equivalent(o[condition_key],v,p);

      // Extract the pointer from a potential aligned_ptr
      auto base = unalign(get<2>(se));

      // Scatter all (clang doesn't like capturing structured bindings)
      eve::_::for_<0, 1, T::size()>([&](auto... I) {
                                      ( scatter_helper_t::sc<T, O>(base, idx, I,get<0>(se),get<1>(se)), ...); }
                                   );
    }
  }
}
