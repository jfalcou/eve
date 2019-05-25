.. _function-fma:

##############
fma
##############

**Required header:** ``#include <eve/function/fma.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ fma = {};
   }

Function object performing a fused multiply/add between three :ref:`Values <concept-value>` of same element type


********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v, wide<T,N> const& w , wide<T,N> const& x ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v U s, U t ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, wide<T,N> const& w , U s ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, U s , wide<T,N> const& w)
   template<typename U>                       constexpr T operator()( U r, U s, U t ) noexcept;

* [1] performs element-wise fused multiply/add of the three parameters
* [2:4] convert the scalar type U to the wide type and perform element-wise fused multiply/add of the three parameters
* [5] computesfused multiply/add of the three parameters

.. rubric:: Parameters

* **v**, **w**, **x**: Instances of **wide<T,N>**
* **r**, **s**, **t**: Scalar value  of type **U**


.. rubric:: Return value

* [1:4] A value of the type **wide<T,N>**                  
* [5]     A value of type **U**


*****
Notes
*****

    The call ``fma(x, y, z)`` is similar to ``x*y+z``

    But really conformant fused multiply/add also implies

    - only one rounding

    - no "intermediate" overflow

    Our ``fma`` provides this for all integral types and also each time it is reasonable
    in terms of performance for floating ones (i.e. if the system has the hard
    wired capability).

    If you need pedantic fma capabilities in all circumstances in your own
    code you can use the pedantic_ option (although it can be very expensive).
    pedantic_ option ensures the fused conformant properties and allows SIMD 
    acceleration if available.

*******
Options
*******

    - pedantic_: ``fma[pedantic_](x,y,z)`` ensures the fma conformant properties
      and allows SIMD acceleration if available.

*******
Example
*******

.. include:: ../../../../test/doc/fma.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/fma.txt
  :literal:
