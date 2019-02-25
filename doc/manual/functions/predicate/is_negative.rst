.. _function-is_negative:

################
is_negative
################

**Required header** ``#include <eve/function/is_negative.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ is_negative = {};
   }

Function object determining if the given :ref:`Value <concept-value>` has it bit of sign set

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             as_logical_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T            > constexpr   as_logical_t<T>         operator()( T s ) noexcept;

* [1] For each element of **v** returns :ref:`True <constant-true_>` if the element has it bit of sign set.
* [2] returns :ref:`True <constant-true_>` if **s** has it bit of sign set.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value 

* [1] A value of type **as_logical_t<wide<T,N>>**.
* [2] A value of type **as_logical_t<T>**.

.. rubric:: Notes

* The computation ``is_negative(x)`` is equivalent to ``is_less(x, Zero(as(x)))`` 
  for :ref:`IntegralValues <concept-integralvalue>`, but for for :ref:`IEEEValues <concept-ieeevalue>` 
  the object returns :ref:`True <constant-true>` if the most significant bit of the element is set. 
  Peculiarly -0.0 and -0.0f are 'negative' but are not 'less than zero'.



Example
*******

.. include:: ../../../../test/doc/is_negative.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_negative.txt
  :literal:

