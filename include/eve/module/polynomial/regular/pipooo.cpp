#include <iostream>;
#include <array>;
struct pipo{
  pipo(std::array < float, 3> const & v) :data(v){};
  auto operator+= (pipo_wished const & v) {
    // write with transform or transform_to the equivalent of
    // without duplicating v
    for(int i=0; i < 3; ++i) { data[i] += v[i];  }
    return *this;
  }
  std::array<float, 3> data;
};

int main()
{
  std::array<float,3>  v{1.0f,2.0f,3.0f};
  std::array<float,3>  w{4.0f,1.0f,-3.0f};
  pipo pv(v),pw(w);
  v+=w;
  for(size_t i=0;i<3;++i)
    std::cout<< v.data[i] <<std::endl;
  return 0;
};
