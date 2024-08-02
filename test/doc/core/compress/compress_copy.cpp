#include <eve/module/core.hpp>

#include <vector>

#include <tts/tts.hpp>

// In abscense of eve::algo, we could write `copy_if` like this

std::vector<int>::iterator
copy_non_zeroes(const std::vector<int>& in, std::vector<int>& out)
{
  const int *in_f = in.data();
  const int *in_l = in.data() + in.size();

  int *out_f = out.data();
  int *out_l = out.data() + out.size();

  using w_t = eve::wide<int>;

  // We do the same thing in main loop and for the tail, difference is that
  // in the tail we can't read and write w_t::size().
  //
  // This is where ignore helps:
  // eve::compress_copy_unsafe_sparse[ignore] - will become safe for the tail.
  auto copy_if_step = [&](eve::relative_conditional_expr auto ignore_in,
                          eve::relative_conditional_expr auto ignore_out) mutable
  {
    auto in_w = eve::load[ignore_in](in_f);
    auto m    = in_w != 0;

    // because we already have an in_w we pass it here.
    // eve::compress_copy_unsafe_sparse[...](in_f, m, out_f) would have the same result.
    out_f =
        eve::compress_copy[eve::unsafe][eve::dense][ignore_in][ignore_out](in_f, in_w, m, out_f);
    in_f += w_t::size();
  };

  while( (in_l - in_f) >= w_t::size() && (out_l - out_f) >= w_t::size() )
  {
    copy_if_step(eve::ignore_none, eve::ignore_none);
  }

  while( in_l - in_f >= w_t::size() && (out_f != out_l) )
  {
    copy_if_step(eve::ignore_none, eve::keep_first(out_l - out_f));
  }

  copy_if_step(eve::keep_first(in_l - in_f), eve::keep_first(out_l - out_f));
  return out.begin() + (out_f - out.data());
}

int
main()
{
  const std::vector<int> input {1, 2, 3, 0, 4, 5, 0, 6, 0, 7};

  {
    std::vector<int> enough(input.size(), 0);
    enough.erase(copy_non_zeroes(input, enough), enough.end());
    TTS_EQUAL(enough, std::vector({1, 2, 3, 4, 5, 6, 7}));
  }

  {
    std::vector<int> not_enough(4, 0);
    TTS_EQUAL(copy_non_zeroes(input, not_enough), not_enough.end());
    TTS_EQUAL(not_enough, std::vector({1, 2, 3, 4}));
  }
}
