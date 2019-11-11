.. _function-fnms:

##############
fnms
##############

**Required header:** ``#include <eve/function/fnms.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ fnms = {};
   }

Function object performing a fused negate-multiply/sub between three :ref:`Values <concept-value>` of same element type


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

* [1] performs element-wise fused negate-multiply/sub of the three parameters
* [2:4] convert the scalar type U to the wide type and perform element-wise fused negate-multiply/sub of the three parameters
* [5]  computes  fused negate-multiply/sub of the three parameters

.. rubric:: Parameters

* **v**, **w**, **x**: Instances of **wide<T,N>**
* **r**, **s**, **t**: Scalar value  of type **U**


.. rubric:: Return value

* [1:4] A value of the type **wide<T,N>**
* [6]     A value of type **U**


*****
Notes
*****

    The call ``fnms(x, y, z)`` is similar to ``-x*y-z``

    But really conformant fused multiply/sub also implies

    - only one rounding

    - no "intermediate" overflow

    Our ``fnms`` provides this for all :ref:`concept-integralvalue` types and also each time it is reasonable
    in terms of performance for :ref:`concept-ieeevalue` ones (i.e. if the system has the hard
    wired capability).

    If you need pedantic fnms capabilities in all circumstances in your own
    code you can use the pedantic_ option (although it can be very expensive).
    pedantic_ option ensures the fnms properties and allows SIMD acceleration if available.

*******
Options
*******

    - pedantic_: ``fnms[pedantic_](x,y,z)`` ensures the fnms conformant properties and allows SIMD
      acceleration if available.

*******
Example
*******

.. include:: ../../../../test/doc/core/fnms.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/fnms.txt
  :literal:
