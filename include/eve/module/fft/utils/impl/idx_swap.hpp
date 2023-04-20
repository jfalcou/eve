//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/range.hpp>
#include <type_traits>

namespace eve::detail
{
  template<range R, integral_value I>
  EVE_FORCEINLINE void idx_swap_(EVE_SUPPORTS(cpu_)
                                , R & f
                                , I const & idx1
                                , I const & idx2) noexcept
  {
    EVE_ASSERT(eve::all(idx1 < std::size(f) && idx2 < std::size(f)), "some indexes are out of range");
    if constexpr(scalar_value<I>)
    {
      auto b =  f.data();
      auto z = *(b+idx1);  *(b+idx1) = *(b+idx2); *(b+idx2) = z;
    }
    else
    {
//       for(int i=0; i < cardinal_v<I> ; ++i)
//       {
//         idx_swap(f, idx1.get(i), idx2.get(i));
//       }
      auto fr =  gather(f.data(), idx1);
      auto fx =  gather(f.data(), idx2);
      scatter(f.data(), idx1, fx);
      scatter(f.data(), idx2, fr);
    }
  }

  template<range R, typename C, integral_value I>
  EVE_FORCEINLINE void idx_swap_(EVE_SUPPORTS(cpu_)
                                , R & f, C const & cond
                                , I const & idx1
                                , I const & idx2) noexcept
  {
    EVE_ASSERT(eve::all(idx1 < f.size() && idx2 < f.size()), "some indexes are out of range");
    if constexpr(scalar_value<I>)
    {
      auto b =  f.data();
      if(cond)
      {
        auto z = *(b+idx1);  *(b+idx1) = *(b+idx2); *(b+idx2) = z;
      }
    }
    else
    {

//       for(int i=0; i < cardinal_v<I> ; ++i)
//       {
//         std::cout << i << " -> " << +idx1.get(i) << "   " << +idx2.get(i)<< "   " << cond.get(i) << std::endl;
// //        if (cond.get(i)) idx_swap(f, idx1.get(i), idx2.get(i));
//       }
      auto fr =  gather(f.data(), idx1);
      auto fx =  gather(f.data(), idx2);
      scatter[cond](f.data(), idx1, fx);
      scatter[cond](f.data(), idx2, fr);
    }
  }
}
