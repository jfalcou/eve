#include <eve/module/algo.hpp>
#include <eve/module/core.hpp>

#include <string>
#include <vector>

#include <tts/tts.hpp>

void
basic_example()
{
  std::vector<int> in {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> out(in.size(), 0);
  out.erase(eve::algo::copy_if(in, out, eve::is_even), out.end());

  TTS_EQUAL(out, std::vector({2, 4, 6}));
}

void
not_enough_output_space()
{
  // We copy up to out.size()
  std::vector<int> in {5, 0, 4, 12, 11, 1, 2};
  std::vector<int> out {0, 0};

  // fix-1656 - no way to know where we stopped in `in`
  auto out_it = eve::algo::copy_if(in, out, [](auto x) { return x > 4; });
  TTS_EQUAL(out_it, out.end());
  TTS_EQUAL(out, std::vector({5, 12}));
}

void
sparse_output()
{
  std::vector<int> in(10'000, 0);
  in[153]  = 1;
  in[9002] = 2;
  std::vector<int> out {0, 0};

  // Tell the library that you expect fairly few element
  eve::algo::copy_if[eve::algo::sparse_output](in, out, [](auto x) { return x != 0; });
  TTS_EQUAL(out, std::vector({1, 2}));
}

void
tst()
{
  std::vector<std::int8_t> v {93, 1,  1,   25,  49, 27,  0,   23,  61, 53, 110,
                              49, 7,  40,  110, 32, -8,  10,  108, 14, 74, 39,
                              54, 79, -61, 108, 51, 117, 121, 89,  -5, -83};
  std::vector<std::int8_t> out(30, 0);

  auto p = [](auto x) { return x != 0; };
  auto end = eve::algo::copy_if(v, out, p);
  TTS_EQUAL(end - out.end(), 0);
}

int
main()
{
  basic_example();
  not_enough_output_space();
  sparse_output();
}
