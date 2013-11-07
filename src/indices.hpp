#ifndef INDICES_HPP
#define INDICES_HPP

template <
        unsigned... Indices
        >
 struct indices{
 using next = indices<Indices..., sizeof...(Indices)>;
};

template <
         unsigned N
         >
struct build_indices{
 using type = typename build_indices<N-1>::type::next;
};

template <>
 struct build_indices<0>{
 using type = indices<>;
};

template<unsigned N>
using IndicesFor = typename build_indices<N>::type;

#endif // INDICES_HPP
