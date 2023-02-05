//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/algo/algo/detail/preprocess_range.hpp>

#include <eve/module/algo/algo/ptr_iterator.hpp>
#include <eve/traits.hpp>

#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>

namespace eve::algo
{
  namespace detail
  {
    template <typename T, typename A>
    EVE_FORCEINLINE auto ptr_to_iterator(eve::aligned_ptr<T, A> ptr)
    {
      return ptr_iterator<eve::aligned_ptr<T, A>, A>{ptr};
    }

    template <typename T>
    EVE_FORCEINLINE auto ptr_to_iterator(T* ptr)
    {
      using N          = eve::fixed<eve::nofs_cardinal_v<std::remove_const_t<T>>>;
      return ptr_iterator<T*, N>{ptr};
    }

    template <typename Traits, typename I>
    EVE_FORCEINLINE auto fix_up_cardinal(Traits, I i)
    {
      if constexpr( iterator_cardinal_v<I> != iteration_cardinal_t<Traits, I> {}() )
      {
        using N = iteration_cardinal_t<Traits, I>;
        auto i_ = i.cardinal_cast(N {});
        return i_;
      }
      else
      {
        return i;
      }
    }
  }

  template <typename Traits, typename I_, typename S_>
    requires detail::pointer_iterator_sentinel<I_, S_>
  EVE_FORCEINLINE auto preprocess_range_::operator()(Traits traits_, I_ f_, S_ l_) const
  {
    // We have to force cardinal here, because iterators
    // with different cardinals don't form a valid range.
    auto f = detail::fix_up_cardinal(traits_, detail::ptr_to_iterator(f_));
    auto l = detail::fix_up_cardinal(traits_, detail::ptr_to_iterator(l_));

    return operator()(traits_, f, l);
  }

  template<typename Traits, std::contiguous_iterator I, typename S>
    requires ( !std::is_pointer_v<I> )
  EVE_FORCEINLINE auto preprocess_range_::operator()(Traits traits_, I f, S l) const
  {
    auto* raw_f = std::to_address(f);
    auto* raw_l = raw_f + (l - f);

    return operator()(traits_, raw_f, raw_l);
  }

  // Base case. Should validate that I, S are a valid iterator pair
  template<typename Traits, iterator I_, sentinel_for<I_> S_>
  EVE_FORCEINLINE auto preprocess_range_::operator()(Traits with_equivalents_, I_ f_, S_ l_) const
  {
    auto traits_ = process_equivalents(with_equivalents_);
    auto f = detail::fix_up_cardinal(traits_, f_);
    auto l = detail::fix_up_cardinal(traits_, l_);

    using I = decltype(f);
    using S = decltype(l);

    auto deduced = []
    {
      if constexpr( partially_aligned_iterator<I> &&
                    std::same_as<I, S> &&
                    !always_aligned_iterator<I> )
          return algo::traits(divisible_by_cardinal);
      else return algo::traits();
    }();

    return preprocess_range_result { default_to(traits_, deduced), f, l};
  }
}
