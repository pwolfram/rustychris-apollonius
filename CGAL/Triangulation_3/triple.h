#ifndef CGAL_SWIG_TRIPLE_H
#define CGAL_SWIG_TRIPLE_H

namespace CGAL_SWIG{
  template <class T1, class T2, class T3>
  class Triple
  {
    typedef Triple<T1, T2, T3> Self;

  public:

    typedef T1 first_type;
    typedef T2 second_type;
    typedef T3 third_type;

    T1 first;
    T2 second;
    T3 third;

    Triple() {}

    Triple(const T1& a, const T2& b, const T3& c)
    : first(a), second(b), third(c)
    {}

    template <class U, class V, class W>
    Triple(const U& a, const V& b, const W& c)
    : first(a), second(b), third(c)
    {}

    #ifndef SWIGPYTHON
    template <class U, class V, class W>
    Triple& operator=(const Triple<U, V, W> &t) {
      first = t.first;
      second = t.second;
      third = t.third;
      return *this;
    }
    #endif
  };
  
  template <class T1,class T2,class T3>
  Triple<T1,T2,T3> make_triple(const T1& t1,const T2& t2,const T3& t3){
    return Triple<T1,T2,T3>(t1,t2,t3);
  }  
}

#endif //CGAL_SWIG_TRIPLE_H