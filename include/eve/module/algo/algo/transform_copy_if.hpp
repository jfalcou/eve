//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/algo/algo/common_forceinline_lambdas.hpp>
#include <eve/module/algo/algo/traits.hpp>
#include <eve/module/algo/algo/two_stage_iteration.hpp>
#include <eve/module/algo/algo/views/convert.hpp>
#include <eve/module/core.hpp>

namespace eve::algo
{

  namespace detail
  {
    template<typename TraitsSupport> struct transform_copy_if_ : TraitsSupport
    {
      template<typename O, typename F> struct delegate
      {
        O of;
        O ol;
        F func;

        EVE_FORCEINLINE
        void load_apply_func_and_store(auto f, auto in_ignore, auto out_ignore)
        {
          auto loaded = eve::load[in_ignore](f);
          auto [vals, mask] = func(loaded);
          using out_t = eve::element_type_t<decltype(vals)>;
          auto cvt_and_store_it = views::convert(of, eve::as<out_t>{});
          auto write_end = eve::compress_store[eve::unsafe][in_ignore][out_ignore](vals, mask, cvt_and_store_it);
          of += write_end - cvt_and_store_it;
        }

        EVE_FORCEINLINE
        bool tail(auto f, auto ignore)
        {
          auto out_ignore   = eve::keep_first(std::min(ol - of, eve::iterator_cardinal_v<O>));
          load_apply_func_and_store(f, ignore, out_ignore);
          return of == ol;
        }

        EVE_FORCEINLINE
        std::ptrdiff_t left_for_stage1() const
        {
          return ol - of;
        }

        EVE_FORCEINLINE
        bool step_1(auto f)
        {
          load_apply_func_and_store(f, eve::ignore_none, eve::ignore_none);
          return false;
        }

        EVE_FORCEINLINE
        bool step_2(auto f)
        {
          // ol - of < cardinal
          auto out_ignore   = eve::keep_first(ol - of);
          load_apply_func_and_store(f, eve::ignore_none, out_ignore);
          return of == ol;
        }
      };

      template<relaxed_range In, relaxed_range Out, typename Func>
      EVE_FORCEINLINE
      auto operator()(In&& in, Out&& out, Func func) const -> unaligned_iterator_t<Out>
      {
        if( in.begin() == in.end() || out.begin() == out.end() )
          return out.begin();

        auto [processed_in, processed_out] = temporary_preprocess_ranges_hack(
          TraitsSupport::get_traits(), in, out);

        auto iteration = two_stage_iteration(processed_in.traits(), processed_in.begin(), processed_in.end());

        auto of = unalign(processed_out.begin());
        auto ol = unalign(processed_out.end());

        delegate<decltype(of), Func> d {of, ol, func};
        iteration(d);
        return eve::unalign(out.begin()) + (d.of - processed_out.begin());
      }

    };
  }

  //==============================================================================================
  //! @addtogroup algos
  //! @{
  //!   @var transform_copy_if
  //!
  //!   **Defined in header**
  //!
  //!   @code
  //!   #include <eve/module/algo.hpp>
  //!   @endcode
  //!
  //!   @brief Similar to applying `eve::transform_to` and `eve::copy_if` at the same time.
  //!
  //!   Conditionally copies values from an input range to an output range,
  //!   transforming them in the process.
  //!
  //!   If the output range is too small, fills all the available space and then stops.
  //!   
  //!   If the output range's element type is different from the type of the values returned by the transforming function, performs the appropriate conversions.
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve::algo
  //!   {
  //!     template <eve::algo::relaxed_range In, eve::algo::relaxed_range Out, typename Func>
  //!     auto transform_copy_if(In&& in, Out&& out, Func func) const -> unaligned_iterator_t<Out>
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!    * `in`: Input range
  //!    * `out`: Output range
  //!    * `func`: Function that takes elements from `in` as SIMD registers and returns a pair of:
  //!        - the transformed values
  //!        - a logical mask.
  //!
  //!   **Return value**
  //!
  //!   Output iterator past the last written element.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/algo/transform_copy_if.cpp}
  //!
  //! @}
  //==============================================================================================
  inline constexpr auto transform_copy_if = function_with_traits<detail::transform_copy_if_>;

}
