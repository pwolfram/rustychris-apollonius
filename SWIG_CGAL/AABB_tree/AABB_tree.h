// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_AABB_TREE_AABB_TREE_H
#define SWIG_CGAL_AABB_TREE_AABB_TREE_H

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Common/Iterator.h>
#include <SWIG_CGAL/Common/Optional.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Plane_3.h>
#include <SWIG_CGAL/AABB_tree/Object.h>
#include <SWIG_CGAL/Kernel/Segment_3.h>
#include <SWIG_CGAL/Kernel/Triangle_3.h>
#include <SWIG_CGAL/Kernel/Ray_3.h>
#include <SWIG_CGAL/Common/Input_iterator_wrapper.h>
#include <SWIG_CGAL/Common/Output_iterator_wrapper.h>


#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
template <class Primitive_object>
struct Primitive_iterator_helper
{
  typedef std::pair<Input_iterator_wrapper<Primitive_object,typename internal::Converter<Primitive_object>::result_type>,
                    Input_iterator_wrapper<Primitive_object,typename internal::Converter<Primitive_object>::result_type> >                      input;
  typedef boost::function_output_iterator< Container_writer<Primitive_object,typename internal::Converter<Primitive_object>::result_type > >     output;
  typedef boost::function_output_iterator< Container_writer<std::pair<Object,Primitive_object>,std::pair<CGAL::Object,typename internal::Converter<Primitive_object>::result_type > > >     output2;
};

typedef std::pair<Input_iterator_wrapper<Point_3,Point_3::cpp_base>,Input_iterator_wrapper<Point_3,Point_3::cpp_base> > Point_range;
#else
typedef Generic_input_iterator<Point_3> Point_range;
#endif

template <class Tree,class Primitive_object,class Primitive_id>
class AABB_tree_wrapper
{
  Tree data;
  typedef AABB_tree_wrapper<Tree,Primitive_object,Primitive_id> Self;
  //disable deep copy
  Self deepcopy();
  void deepcopy(const Self&);
public:
  #ifndef SWIG
  typedef Tree cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  #endif
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  typedef typename Primitive_iterator_helper<Primitive_object>::input Primitive_range;
  #else
  typedef Generic_input_iterator<Primitive_object> Primitive_range;
  #endif

  typedef std::pair<Point_3,Primitive_id> Point_and_primitive_id;
  typedef std::pair<Object,Primitive_id>  Object_and_primitive_id;
  typedef Optional<Primitive_id> Optional_primitive_id;
  typedef Optional<Object_and_primitive_id> Optional_object_and_primitive_id;


//Creation
  AABB_tree_wrapper(){}
  AABB_tree_wrapper(Primitive_range range):data(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range)){}
//Operations  
  void rebuild(Primitive_range range){ data.rebuild(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range)); }
  SWIG_CGAL_FORWARD_CALL_0(void,clear)
  SWIG_CGAL_FORWARD_CALL_0(int,size)
  SWIG_CGAL_FORWARD_CALL_0(bool,empty)
//Intersection Tests
  //do_intersect  
  SWIG_CGAL_FORWARD_CALL_1(bool,do_intersect,Segment_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,do_intersect,Triangle_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,do_intersect,Plane_3)
  SWIG_CGAL_FORWARD_CALL_1(bool,do_intersect,Ray_3)
  //number_of_intersected_primitives
  SWIG_CGAL_FORWARD_CALL_1(int,number_of_intersected_primitives,Segment_3)
  SWIG_CGAL_FORWARD_CALL_1(int,number_of_intersected_primitives,Triangle_3)
  SWIG_CGAL_FORWARD_CALL_1(int,number_of_intersected_primitives,Plane_3)
  SWIG_CGAL_FORWARD_CALL_1(int,number_of_intersected_primitives,Ray_3)
  //all_intersected_primitives
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  void all_intersected_primitives (const Segment_3 & query, typename Primitive_iterator_helper<Primitive_id>::output out) {data.all_intersected_primitives(query.get_data(),out);}
  void all_intersected_primitives (const Triangle_3& query, typename Primitive_iterator_helper<Primitive_id>::output out) {data.all_intersected_primitives(query.get_data(),out);}
  void all_intersected_primitives (const Plane_3   & query, typename Primitive_iterator_helper<Primitive_id>::output out) {data.all_intersected_primitives(query.get_data(),out);}
  void all_intersected_primitives (const Ray_3     & query, typename Primitive_iterator_helper<Primitive_id>::output out) {data.all_intersected_primitives(query.get_data(),out);}
  #else
  void all_intersected_primitives (const Segment_3 & query, Generic_output_iterator<Primitive_id> out) {data.all_intersected_primitives(query.get_data(),out);}
  void all_intersected_primitives (const Triangle_3& query, Generic_output_iterator<Primitive_id> out) {data.all_intersected_primitives(query.get_data(),out);}
  void all_intersected_primitives (const Plane_3   & query, Generic_output_iterator<Primitive_id> out) {data.all_intersected_primitives(query.get_data(),out);}
  void all_intersected_primitives (const Ray_3     & query, Generic_output_iterator<Primitive_id> out) {data.all_intersected_primitives(query.get_data(),out);}
  #endif
  //any_intersected_primitive
  Optional_primitive_id any_intersected_primitive(const Segment_3 & query) {
    boost::optional<typename Tree::Primitive::Id> res=data.any_intersected_primitive(query.get_data());
    if (res)
      return Optional_primitive_id(Primitive_id(*res));
    return Optional_primitive_id();
  }
  Optional_primitive_id any_intersected_primitive(const Triangle_3 & query) {
    boost::optional<typename Tree::Primitive::Id> res=data.any_intersected_primitive(query.get_data());
    if (res)
      return Optional_primitive_id(Primitive_id(*res));
    return Optional_primitive_id();
  }
  Optional_primitive_id any_intersected_primitive(const Plane_3 & query) {
    boost::optional<typename Tree::Primitive::Id> res=data.any_intersected_primitive(query.get_data());
    if (res)
      return Optional_primitive_id(Primitive_id(*res));
    return Optional_primitive_id();
  }

  Optional_primitive_id any_intersected_primitive(const Ray_3    & query) {
    boost::optional<typename Tree::Primitive::Id> res=data.any_intersected_primitive(query.get_data());
    if (res)
      return Optional_primitive_id(Primitive_id(*res));
    return Optional_primitive_id();
  }
//Intersections
  //any_intersection
  Optional_object_and_primitive_id any_intersection(const Segment_3& query)
  {
    boost::optional<std::pair<CGAL::Object,typename Tree::Primitive::Id> > res=data.any_intersection(query.get_data());
    if (res)
      return Optional_object_and_primitive_id(Object_and_primitive_id(*res));
    return Optional_object_and_primitive_id();
  }
  Optional_object_and_primitive_id any_intersection(const Plane_3& query)
  {
    boost::optional<std::pair<CGAL::Object,typename Tree::Primitive::Id> > res=data.any_intersection(query.get_data());
    if (res)
      return Optional_object_and_primitive_id(Object_and_primitive_id(*res));
    return Optional_object_and_primitive_id();
  }
  Optional_object_and_primitive_id any_intersection(const Triangle_3& query)
  {
    boost::optional<std::pair<CGAL::Object,typename Tree::Primitive::Id> > res=data.any_intersection(query.get_data());
    if (res)
      return Optional_object_and_primitive_id(Object_and_primitive_id(*res));
    return Optional_object_and_primitive_id();
  }
  Optional_object_and_primitive_id any_intersection(const Ray_3& query)
  {
    boost::optional<std::pair<CGAL::Object,typename Tree::Primitive::Id> > res=data.any_intersection(query.get_data());
    if (res)
      return Optional_object_and_primitive_id(Object_and_primitive_id(*res));
    return Optional_object_and_primitive_id();
  }
  //all_intersections
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE  
  void all_intersections (const Segment_3  & query, typename Primitive_iterator_helper<Primitive_id>::output2 out) {data.all_intersections(query.get_data(),out);}
  void all_intersections (const Plane_3    & query, typename Primitive_iterator_helper<Primitive_id>::output2 out) {data.all_intersections(query.get_data(),out);}
  void all_intersections (const Triangle_3 & query, typename Primitive_iterator_helper<Primitive_id>::output2 out) {data.all_intersections(query.get_data(),out);}
  void all_intersections (const Ray_3      & query, typename Primitive_iterator_helper<Primitive_id>::output2 out) {data.all_intersections(query.get_data(),out);}
  #else
  void all_intersections (const Segment_3  & query, Generic_output_iterator< std::pair<Object,Primitive_id> > out) {data.all_intersections(query.get_data(),out);}
  void all_intersections (const Plane_3    & query, Generic_output_iterator< std::pair<Object,Primitive_id> > out) {data.all_intersections(query.get_data(),out);}
  void all_intersections (const Triangle_3 & query, Generic_output_iterator< std::pair<Object,Primitive_id> > out) {data.all_intersections(query.get_data(),out);}
  void all_intersections (const Ray_3      & query, Generic_output_iterator< std::pair<Object,Primitive_id> > out) {data.all_intersections(query.get_data(),out);} 
  #endif
  
//Distance Queries
  SWIG_CGAL_FORWARD_CALL_1(double,squared_distance,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(Point_3,closest_point,Point_3)
  SWIG_CGAL_FORWARD_CALL_1(Point_and_primitive_id,closest_point_and_primitive,Point_3)
//Accelerating the Distance Queries
  SWIG_CGAL_FORWARD_CALL_0(bool,accelerate_distance_queries)
  SWIG_CGAL_FORWARD_CALL_2(double,squared_distance,Point_3,Point_3)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Point_3,closest_point,Point_3,Point_3)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Point_and_primitive_id,closest_point_and_primitive,Point_3,Point_and_primitive_id)  
  void accelerate_distance_queries (Point_range range) {data.accelerate_distance_queries(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range));}  
};


#endif //SWIG_CGAL_AABB_TREE_AABB_TREE_H




