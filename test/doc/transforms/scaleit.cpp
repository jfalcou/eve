#include <eve/module/complex.hpp>
#include <eve/module/algo.hpp>
#include <eve/module/transforms.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>
#include <vector>

template <eve::algo::relaxed_range R>
auto toto(R & v){
  std::cout << "toto" << std::endl;
  return  v;
}

int main()
{
  auto pr = [](auto title, auto v){
    std::cout << title << " = (";
    for(size_t i=0; i < v.size() ; ++i) std::cout << eve::read(v.data()+i) << " ";
    std::cout << ")\n";
  };

  using e_t = float;
  using aos_et = std::vector<e_t>;
  aos_et aosv(4, 1.0f);
  eve::scaleit(aosv, 2);
  pr("aosv", aosv);

  aos_et aosvr(4, 1.0f);
  aos_et aosvi(4, -1.0f);
  eve::scaleit(aosvr, aosvi, 2);
  pr("aosvr", aosvr);
  pr("aosvi", aosvi);

  using c_t = eve::complex<e_t>;
  using aos_ct = std::vector<c_t>;
  aos_ct aosvri(4, c_t(1.0f, -1.0f));
  eve::scaleit(aosvri, 2, true); // pourquoi ca ne compile pas si true n'est pas la ?
  pr("aosvri", aosvri);

  using soa_ct = eve::algo::soa_vector<c_t>;
  soa_ct soavri{c_t(1.0f, -1.0f), c_t(1.0f, -1.0f), c_t(1.0f, -1.0f), c_t(1.0f, -1.0f)};
  eve::scaleit(soavri, 2);
  pr("soavri", soavri);

  return 0;
}
