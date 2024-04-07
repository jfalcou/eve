#include <eve/module/core.hpp>
#include <tts/tts.hpp>



void basic()
{
  using w_t = eve::wide<std::uint32_t, eve::fixed<4>>;

  w_t x{2, 3, 1, 4};

  TTS_EXPECT(eve::all(w_t{1, 2, 3, 4} == eve::sort(x)));
  TTS_EXPECT(eve::all(w_t{1, 2, 3, 4} == eve::sort(x, eve::is_less)));
  TTS_EXPECT(eve::all(w_t{4, 3, 2, 1} == eve::sort(x, eve::is_greater)));
}

void sort_by_key()
{
  using k_v = kumi::tuple<int, double>;
  using w_t = eve::wide<k_v, eve::fixed<4>>;

  w_t x {
    k_v{ 12, 0.3 },
    k_v{ 4,  0.1 },
    k_v{ 8,  0.2 },
    k_v{ 2,  0.3 },
  };
  w_t expected {
    k_v{ 2,  0.3 },
    k_v{ 4,  0.1 },
    k_v{ 8,  0.2 },
    k_v{ 12, 0.3 },
  };
  w_t x_sorted = eve::sort(x, [](w_t k_v0, w_t k_v1) {
    return get<0>(k_v0) < get<0>(k_v1);
  });
  TTS_EXPECT(eve::all(expected == x_sorted));
}

int main()
{
  basic();
  sort_by_key();
}
