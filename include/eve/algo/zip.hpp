//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/as_range.hpp>
#include <eve/algo/range_ref.hpp>
#include <eve/algo/concepts/relaxed.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/traits.hpp>
#include <eve/algo/zip_iterator.hpp>

#include <eve/algo/concepts/detail.hpp>

#include <eve/algo/detail/preprocess_zip_range.hpp>

#include <eve/detail/kumi.hpp>

namespace eve::algo
{
  template <typename ZipTraits, relaxed_range ...Rngs>
  struct zip_range;

  namespace detail
  {
    template <relaxed_range Rng>
    struct rng_ref
    {
      Rng* rng;

      // FIX-874: non member ones should be used
      auto begin() const { return rng->begin(); }
      auto end()   const { return rng->end(); }

      template <typename Traits>
      EVE_FORCEINLINE friend auto tagged_dispatch(preprocess_range_, Traits traits, rng_ref self)
      {
        return preprocess_range(traits, *self.rng);
      }
    };
  }

  template <typename TraitsSupport>
  // this is zip traits, not algo traits.
  struct zip_ : TraitsSupport
  {
   private:
     template <typename ...Components>
     EVE_FORCEINLINE std::ptrdiff_t compute_distance(Components&& ... components) const
     {
       std::ptrdiff_t res = -1;
       auto process_one = [&]<typename C>(C const& c) mutable {
         if constexpr (relaxed_range<C>)
         {
           std::ptrdiff_t cur = c.end() - c.begin();
           if (res == -1) res = cur;
           // We'd need to support zipping to min size at some point
           EVE_ASSERT(res == cur, "Can't zip ranges of different sizes");
         }
       };
       (process_one(components), ...);
       return res;
     }

     template <typename ...Components>
     EVE_FORCEINLINE auto perform_replacements(std::ptrdiff_t distance, Components&& ... components) const
     {
       return kumi::tuple{
         [&]<typename C>(C&& c)
         {
           if constexpr (relaxed_range<C>) return range_ref(std::forward<C>(c));
           else                            return as_range(c, unalign(c) + distance);
         }(components)...
       };
     }

   public:

    template <typename ...Components>
      requires ((relaxed_range<Components> || relaxed_iterator<Components>) && ...)
    EVE_FORCEINLINE auto operator()(Components&& ... components) const
    {
      if constexpr ((relaxed_iterator<Components> && ... ))
      {
        return zip_iterator{components...};
      }
      else
      {
        std::ptrdiff_t distance = compute_distance(components...);
        return zip_range{TraitsSupport::get_traits(), perform_replacements(distance, components...)};
      }
    }
  };

  inline constexpr auto zip = function_with_traits<zip_>;

  template <typename ZipTraits, relaxed_range ...Rngs>
  struct zip_range : kumi::tuple<Rngs...>
  {
    ZipTraits zip_tr;

    EVE_FORCEINLINE zip_range(ZipTraits zip_tr, kumi::tuple<Rngs...> ranges):
      kumi::tuple<Rngs...>(ranges),
      zip_tr(zip_tr)
    {
    }

    // Traits support
    template<typename Settings>
    EVE_FORCEINLINE auto operator[](traits<Settings> tr) const
    {
      return kumi::apply([&](Rngs... rngs) { return zip[zip_tr][tr](rngs...); }, *this);
    }

    template <rbr::concepts::option Trait>
    EVE_FORCEINLINE auto operator[](Trait one_tr) const
    {
      return operator[](eve::algo::traits(one_tr));
    }

    ZipTraits get_traits() const
    {
      return zip_tr;
    }

    EVE_FORCEINLINE auto begin() const
    {
      return zip_iterator(kumi::map([](auto r) { return r.begin(); }, *this));
    }

    EVE_FORCEINLINE auto end() const
    {
      return zip_iterator(kumi::map([](auto r) { return r.end(); }, *this));
    }

    template <typename Traits>
    EVE_FORCEINLINE friend auto tagged_dispatch(preprocess_range_, Traits tr, zip_range self)
    {
      return detail::preprocess_zip_range(tr, self.zip_tr, self);
    }
  };
}

namespace std
{
  template <typename Traits, typename ...Ranges>
  struct tuple_size<eve::algo::zip_range<Traits, Ranges...>> :
    std::tuple_size<kumi::tuple<Ranges...>>
  {
  };

  template <std::size_t I, typename Traits, typename ...Ranges>
  struct tuple_element<I, eve::algo::zip_range<Traits, Ranges...>> :
    std::tuple_element<I, kumi::tuple<Ranges...>>
  {
  };
}
