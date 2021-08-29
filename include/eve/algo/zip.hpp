//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/as_range.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/traits.hpp>
#include <eve/algo/zip_iterator.hpp>

#include <eve/algo/detail/preprocess_zip_range.hpp>

#include <eve/detail/kumi.hpp>

namespace eve::algo
{
  template <typename ZipTraits, typename ...Rngs>
  struct zip_range
  {
    ZipTraits zip_tr;
    kumi::tuple<Rngs...> ranges;

    EVE_FORCEINLINE auto begin() const
    {
      return zip_iterator(kumi::map([](auto r) { return r.begin(); }, ranges));
    }

    EVE_FORCEINLINE auto end() const
    {
      return zip_iterator(kumi::map([](auto r) { return r.end(); }, ranges));
    }

    template <typename Traits>
    EVE_FORCEINLINE friend auto tagged_dispatch(preprocess_range_, Traits tr, zip_range self)
    {
      return preprocess_zip_range(tr, self.zip_tr, self.ranges);
    }
  };

  template <typename ZipTraits, typename ...Rngs>
  zip_range(ZipTraits zip_tr, kumi::tuple<Rngs...>) -> zip_range<ZipTraits, Rngs...>;

  namespace detail
  {
    // FIX-874: we should do this proper
    template <typename Rng>
    concept light_range = requires (Rng& rng) {
      { rng.begin() };
      { rng.end() };
    };

    template <light_range Rng>
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
         if constexpr (detail::light_range<C>)
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
           using no_ref = std::remove_reference_t<C>;
                if constexpr (instance_of<no_ref, detail::rng_ref>) return c;
           else if constexpr (detail::light_range<no_ref>         ) return detail::rng_ref<no_ref>{&c};
           else                                                     return as_range(c, unalign(c) + distance);
         }(components)...
       };
     }

   public:

    template <typename ...Components>
    EVE_FORCEINLINE auto operator()(Components&& ... components) const
    {
      if constexpr ((!detail::light_range<Components> && ... ))
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
}
