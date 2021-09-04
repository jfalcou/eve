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
    // we don't allow to sfinae on convert because it's difficult
  EVE_FORCEINLINE auto convert_::operator()(Wrapped&& wrapped, eve::as<T> tgt) const
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

  template <non_owning_range R, typename T>
  struct converting_range
  {
    R base;

    using is_non_owning = void;

    auto begin() const { return convert(base.begin(), eve::as<T>{}); }
    auto end()   const { return convert(base.end(),   eve::as<T>{}); }

    template <typename Traits>
    friend auto tagged_dispatch(preprocess_range_, Traits tr, converting_range self)
    {
      if constexpr (has_type_overrides_v<Traits> ) return preprocess_range(tr, self.base);
      else
      {
        auto processed = preprocess_range(default_to(tr, traits {common_with_types<T>}), self.base);
        return preprocess_range_result {drop_key(common_with_types_key, processed.traits()),
                                        processed.begin(),
                                        processed.end()};
      }
    }
  };
}
