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

template<typename TraitsSupport> struct copy_if_ : TraitsSupport
{
  template<typename O, typename P> struct delegate
  {
    O of;
    O ol;
    P p;

    static constexpr auto compress_copy()
    {
      auto density = density_for_compress_copy<typename TraitsSupport::traits_type>();
      return eve::compress_copy[eve::unsafe][density];
    }

    EVE_FORCEINLINE
    bool tail(auto f, auto ignore)
    {
      auto loaded = eve::load[ignore](f);
      auto m      = p(loaded);
      // this max is a bit annoying, it might not be needed.
      auto out_ignore = eve::keep_first(std::min(ol - of, eve::iterator_cardinal_v<O>));
      of              = compress_copy()[ignore][out_ignore](f, loaded, m, of);
      return of == ol;
    }

    EVE_FORCEINLINE
    std::ptrdiff_t left_for_stage1() const { return ol - of; }

    EVE_FORCEINLINE
    bool step_1(auto f)
    {
      auto loaded = eve::load(f);
      auto m      = p(loaded);
      of          = compress_copy()(f, loaded, m, of);
      return false;
    }

    EVE_FORCEINLINE
    bool step_2(auto f)
    {
      auto loaded = eve::load(f);
      auto m      = p(loaded);
      // ol - of < cardinal
      of = compress_copy()[eve::ignore_none][eve::keep_first(ol - of)](f, loaded, m, of);
      return of == ol;
    }
  };

  template<relaxed_range In, relaxed_range Out, typename P>
  EVE_FORCEINLINE auto operator()(In&& in, Out&& out, P p) const -> unaligned_iterator_t<Out>
  {
    if( in.begin() == in.end() || out.begin() == out.end() ) return out.begin();

    auto [processed_in, processed_out] = temporary_preprocess_ranges_hack(
        TraitsSupport::get_traits(), in, views::convert(out, as<value_type_t<In>> {}));

    auto iteration =
        two_stage_iteration(processed_in.traits(), processed_in.begin(), processed_in.end());

    auto of = unalign(processed_out.begin());
    auto ol = unalign(processed_out.end());

    delegate<decltype(of), P> d {of, ol, p};
    iteration(d);
    return eve::unalign(out.begin()) + (d.of - processed_out.begin());
  }
};

//================================================================================================
//! @addtogroup algos
//! @{
//!  @var copy_if
//!  @brief SIMD variation on std::copy_if.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/algo.hpp>
//!   @endcode
//!
//!   The main difference from std::copy_if is that it accepts output range and not
//!   an output iterator. If the output doesn't have enough space, algorithm will fill
//!   all of the avaliable output and then stop.
//!   The interface difference allows eve to store more then just selected elements
//!   which is important for efficiency.
//!
//!   @note fix-1656: unfortunately at the moment, we only return where writing output
//!   finished. We should return where the input stopped too but we couldn't solve that
//!   efficiently so far.
//!
//!   Tuning:
//!    * eve::algo::dense_output/eve::algo::sparse_output - if you expect very sparse
//!      output (one or two trues per register) - you can pass sparse_output to try to
//!      optimize for that.
//!    * Does not support unrolling at the moment. In the exepriments with compress it
//!      didn't prove beneficial, but you can always try with `eve::algo::for_each`, assuming you
//!      can overallocate the output.
//!    * Algorithm switches to a much slower version, when there is not enough space to write
//!      a full register. Allocating more than input size won't help though.
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve::algo
//!   {
//!      template<relaxed_range In, relaxed_range Out, typename P>
//!      auto copy_if(In&& in, Out&& out, P p) -> unaligned_iterator_t<Out>
//!   }
//!   @endcode
//!
//!   ** Parameters **
//!
//!    * in - relaxed_range input
//!    * out - relaxed_range output
//!    * p - simd prediocate for elmenets of `in`
//!
//!   ** Return value **
//!
//!    relaxed_iterator past the last written element.
//!
//!   @see `transform_copy_if`
//!
//! @}
//================================================================================================
inline constexpr auto copy_if = function_with_traits<copy_if_>;

}
