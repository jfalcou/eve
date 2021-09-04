//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/detail/preprocess_range.hpp>

#include <eve/algo/concepts/value_type.hpp>
#include <eve/algo/convert.hpp>
#include <eve/algo/ptr_iterator.hpp>

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
      return aligned_ptr_iterator<T, A>{ptr};
    }

    template <typename T>
    EVE_FORCEINLINE auto ptr_to_iterator(T* ptr)
    {
      using N          = eve::fixed<eve::expected_cardinal_v<std::remove_const_t<T>>>;
      return unaligned_ptr_iterator<T, N>{ptr};
    }

    template <typename Traits, typename I>
    EVE_FORCEINLINE auto fix_up_type_and_cardinal(Traits traits_, I i)
    {
      if constexpr( !std::same_as<typename I::value_type, iteration_type_t<Traits, I>> )
      {
        using T = iteration_type_t<Traits, I>;
        auto i_ = convert(i, eve::as<T> {});
        return fix_up_type_and_cardinal(traits_, i_);
      }
      else if constexpr( typename I::cardinal {}() !=
                         forced_cardinal_t<Traits, typename I::value_type> {}() )
      {
        using N = forced_cardinal_t<Traits, typename I::value_type>;
        auto i_ = i.cardinal_cast(N {});
        return fix_up_type_and_cardinal(traits_, i_);
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
    auto f = detail::fix_up_type_and_cardinal(traits_, detail::ptr_to_iterator(f_));
    auto l = detail::fix_up_type_and_cardinal(traits_, detail::ptr_to_iterator(l_));

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
  EVE_FORCEINLINE auto preprocess_range_::operator()(Traits traits_, I_ f_, S_ l_) const
  {
    auto f = detail::fix_up_type_and_cardinal(traits_, f_);
    auto l = detail::fix_up_type_and_cardinal(traits_, l_);

    using I = decltype(f);
    using S = decltype(l);

    auto deduced = []
    {
      if constexpr( !partially_aligned_iterator<I> )
        return traits {};
      else
      {
        if constexpr( std::same_as<I, S> && !always_aligned_iterator<I> )
          return algo::traits(no_aligning, divisible_by_cardinal);
        else
          return algo::traits(no_aligning);
      }
    }();

    return preprocess_range_result { default_to(traits_, deduced), f, l};
  }
}
