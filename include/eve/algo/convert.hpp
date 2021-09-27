//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/detail/convert.hpp>

#include <eve/algo/concepts/relaxed.hpp>
#include <eve/algo/concepts/types_to_consider.hpp>
#include <eve/algo/concepts/value_type.hpp>
#include <eve/algo/detail/converting_iterator.hpp>
#include <eve/algo/range_ref.hpp>

namespace eve::algo
{
  template <typename I, typename T>
  struct converting_iterator;

  template <non_owning_range R, typename T>
  struct converting_range;

  template <typename Wrapped, typename T>
  EVE_FORCEINLINE auto convert_::no_tagged_dispatch(Wrapped&& wrapped, eve::as<T> tgt) const
  {
    if constexpr (relaxed_range<Wrapped>)
    {
      auto rng  = range_ref(std::forward<Wrapped>(wrapped));
      using Rng = decltype(rng);

           if constexpr (std::same_as<value_type_t<Rng>, T>        ) return rng;
      else if constexpr (detail::instance_of<Rng, converting_range>) return convert(rng.base, tgt);
      else                                                           return converting_range<Rng, T>{rng};
    }
    else
    {
      using I = std::remove_cvref_t<Wrapped>;
           if constexpr (std::same_as<value_type_t<I>, T>           ) return wrapped;
      else if constexpr (detail::instance_of<I, converting_iterator>) return convert(wrapped.base, tgt);
      else                                                            return converting_iterator<I, T>{wrapped};
    }
  }

  template <typename Wrapped, typename T>
    // we don't allow to sfinae on convert because it's difficult
  EVE_FORCEINLINE auto convert_::operator()(Wrapped&& wrapped, as<T> tgt) const
  {
    if constexpr (eve::detail::tag_dispatchable<convert_, decltype(std::forward<Wrapped>(wrapped)), as<T>>)
    {
      return tagged_dispatch(*this, std::forward<Wrapped>(wrapped), tgt);
    }
    else return no_tagged_dispatch( std::forward<Wrapped>(wrapped), tgt);
  }

  template <non_owning_range R, typename T>
  struct converting_range
  {
    R base;

    using is_non_owning = void;

    using types_to_consider = kumi::result::cat_t<
      kumi::tuple<T>, types_to_consider_for_t<R>>;

    EVE_FORCEINLINE auto begin() const { return convert(base.begin(), eve::as<T>{}); }
    EVE_FORCEINLINE auto end()   const { return convert(base.end(),   eve::as<T>{}); }

    template<typename Traits>
    EVE_FORCEINLINE friend auto tagged_dispatch(preprocess_range_, Traits tr, converting_range self)
    {
      auto tr_with_cardinal = default_to(tr, traits {consider_types<T>});
      auto processed        = preprocess_range(tr_with_cardinal, self.base);

      auto ret_tr = drop_key(consider_types_key, processed.traits());

      return preprocess_range_result {
          ret_tr, convert(processed.begin(), as<T>{}), convert(processed.end(), as<T>{})
      };
    }
  };
}
