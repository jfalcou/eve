//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/converting_iterator.hpp>
#include <eve/algo/detail/preprocess_range.hpp>
#include <eve/algo/ptr_iterator.hpp>

#include <iterator>
#include <type_traits>
#include <utility>

namespace eve::algo
{
  template<typename Traits, std::contiguous_iterator I, typename S>
  EVE_FORCEINLINE auto preprocess_range_::operator()(Traits traits_, I f, S l) const
  {
    using T  = std::remove_reference_t<decltype(*f)>;
    using it = unaligned_ptr_iterator<
        T,
        forced_cardinal_t<Traits, typename std::iterator_traits<I>::value_type>>;

    T *raw_f = nullptr;
    T *raw_l = raw_f;

    if( f != l )
    {
      raw_f = &*f;
      raw_l = raw_f + (l - f);
    }

    return enhance_to_output(operator()(traits_, it {raw_f}, it {raw_l}),
                             [f, raw_f](it i) { return f + (i.ptr - raw_f); });
  }

  template<typename Traits, typename T, typename A>
  EVE_FORCEINLINE auto
  preprocess_range_::operator()(Traits traits_, eve::aligned_ptr<T, A> f, T *l) const
  {
    using N = forced_cardinal_t<Traits, T>;

    if constexpr( N {}() > A {}() ) return operator()(traits_, f.get(), l);
    else
    {
      using aligned_it   = aligned_ptr_iterator<T, N>;
      using unaligned_it = unaligned_ptr_iterator<T, N>;

      return enhance_to_output(operator()(traits_, aligned_it(f), unaligned_it(l)),
                               [](unaligned_it i) { return i.ptr; });
    }
  }

  template<typename Traits, typename T, typename A1, typename A2>
  EVE_FORCEINLINE auto
  preprocess_range_::operator()(Traits traits_, eve::aligned_ptr<T, A1> f, eve::aligned_ptr<T, A2> l) const
  {
    using N = forced_cardinal_t<Traits, T>;

         if constexpr( N {}() > A2 {}() ) return operator()(traits_, f, l.get());
    else if constexpr( N {}() > A1 {}() ) return operator()(traits_, f.get(), l);
    else
    {
      using aligned_it = aligned_ptr_iterator<T, forced_cardinal_t<Traits, T>>;

      return enhance_to_output(operator()(traits_, aligned_it(f), aligned_it(l)),
                               [](unaligned_t<aligned_it> i) { return i.ptr; });
    }
  }

  // Base case. Should validate that I, S are a valid iterator pair
  template<typename Traits, iterator I, sentinel_for<I> S>
  EVE_FORCEINLINE auto preprocess_range_::operator()(Traits traits_, I f, S l) const
  {
    if constexpr( !std::same_as<typename I::value_type, iteration_type_t<Traits, I>> )
    {
      using T = iteration_type_t<Traits, I>;
      auto f_ = convert(f, eve::as<T> {});
      auto l_ = convert(l, eve::as<T> {});
      return enhance_to_output(preprocess_range(traits_, f_, l_),
                               [](unaligned_t<decltype(f_)> i)
                               { return convert(i, eve::as<typename I::value_type> {}); });
    }
    else if constexpr( typename I::cardinal {}()
                       > forced_cardinal_t<Traits, typename I::value_type> {}() )
    {
      using N = forced_cardinal_t<Traits, typename I::value_type>;
      auto f_ = f.cardinal_cast(N {});
      return enhance_to_output(preprocess_range(traits_, f_, l.cardinal_cast(N {})),
                               [](unaligned_t<decltype(f_)> i)
                               { return i.cardinal_cast(typename I::cardinal {}); });
    }
    else
    {
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

      return preprocess_range_result {
          default_to(traits_, deduced), f, l, [](unaligned_t<I> i) { return i; }};
    }
  }
}
