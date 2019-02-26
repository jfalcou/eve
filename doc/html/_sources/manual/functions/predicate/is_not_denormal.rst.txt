.. _function-is_not_denormal:

################
is_not_denormal
################

**Required header** ``#include <eve/function/is_not_denormal.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ is_not_denormal = {};
   }

Function object determining if the given :ref:`IEEEValue <concept-ieeevalue>` is subnormal

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             as_logical_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T            > constexpr   as_logical_t<T>         operator()( T s ) noexcept;

* [1] For each element of **v** returns :ref:`True <constant-true_>` if the element is not subnormal.
* [2] returns :ref:`True <constant-true_>` if **s** is not subnormal.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1] A value of type **as_logical_t<wide<T,N>>**.
* [2] A value of type **as_logical_t<T>**.

.. rubric:: Notes

* For :ref:`IEEEValues <concept-ieeevalue>` ,the computation is equivalent to for each input element **x** ``is_not less(abs(x), Smallestposval(as(x))) || is_eqz(x)``
* For :ref:`IntegralValues <concept-integralvalue>` the object is still defined, but always returns :ref:`True <constant-true_>`

Options
*******

Example
*******

.. include:: ../../../../test/doc/is_not_denormal.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_not_denormal.txt
  :literal:

