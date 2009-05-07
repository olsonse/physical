/** \file The types in this detail namespace are for facilitating conversion of
 * physical constants which have various aggregate units. */

namespace detail {
  using dimension::make_dim;
  using dimension::exp_dim;

  template < typename T >
  struct capacitance_per_length :
    make_dim<
      dimension::electric::capacitance,
      exp_dim<dimension::length,-1>::type
    >::dim<T> {};

  template < typename T >
  struct length_per_capacitance :
    make_dim< exp_dim<capacitance_per_length,-1>::type >::dim<T> {};

  template < typename T >
  struct sigma_SB_dims :
    make_dim<
      dimension::power,
      exp_dim<dimension::length,-2>::type,
      exp_dim<dimension::temperature,-4>::type
    >::dim<T> {};

  template < typename T >
  struct G_dims :
    make_dim<
      exp_dim<dimension::length,3>::type,
      exp_dim<dimension::mass,-1>::type,
      exp_dim<dimension::time,-2>::type
    >::dim<T> {};

  template < typename T >
  struct K_B_dims :
    make_dim<
      dimension::energy,
      exp_dim<dimension::temperature,-1>::type
    >::dim<T> {};
}
