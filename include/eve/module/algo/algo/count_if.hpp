//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//=================

#pragma once

#include <eve/module/algo/algo/common_forceinline_lambdas.hpp>
#include <eve/module/algo/algo/traits.hpp>
#include <eve/module/algo/algo/for_each_iteration.hpp>
#include <eve/module/algo/algo/views/convert.hpp>
#include <eve/module/core.hpp>
#include <vector>
namespace eve::algo
{

template<typename TraitsSupport> struct count_if_ : TraitsSupport
{
  template<typename P> struct delegate
    {
    P p;
    std::ptrdiff_t count = 0;

    EVE_FORCEINLINE bool step(auto f, auto )
    {
        auto loaded = eve::load(f);
        count += eve::count_true(p(loaded));
        return false;
    }

    EVE_FORCEINLINE bool step(auto f, auto ignore, auto)
    {
        auto loaded = eve::load[ignore](f);
        count += eve::count_true[ignore](p(loaded));
        return false;
    }

    EVE_FORCEINLINE bool tail(auto f, auto ignore)
    {
        auto loaded = eve::load[ignore](f);
        count += eve::count_true[ignore](p(loaded)); 
        return true;
    }
    };

  template<relaxed_range In, typename P>
  EVE_FORCEINLINE auto operator()(In&& in, P p) const -> std::ptrdiff_t
  {
    if( in.begin() == in.end() ) return 0;

    auto processed_in = preprocess_range(TraitsSupport::get_traits(), in);

    auto iteration = for_each_iteration(
        processed_in.traits(), 
        processed_in.begin(), 
        processed_in.end()    
    );

    delegate<P> d {p, 0};
    iteration(d);
    
    return d.count;
  }
};

//================================================================================================
//! @addtogroup algos
//! @{
//!   @var count_if
//!
//!   @brief a SIMD version of `std::count_if`
//!
//!   Counts how many elements in the range match the predicate.
//!   by default aligns and unrolls 4 times.
//!
//!   **Alternative Header**
//!
//!   @code
//!   #include <eve/module/algo.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve::algo
//!   {
//!     template <eve::algo::relaxed_range Rng, typename P>
//!     std::ptrdiff_t count_if(Rng&& rng, P p);
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    * `rng`: Relaxed input range to process
//!    * 'p':   Predicate
//!
//!   **Return value**
//!
//!   The number of elements for which unary `p` returns `true`.
//!   Returns `0` if the range is empty.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/algo/count_if.cpp}
//!
//! @}
//================================================================================================
inline constexpr auto count_if = function_with_traits<count_if_>;

}


