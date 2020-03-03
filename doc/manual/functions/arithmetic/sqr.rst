.. _function-sqr:

###
sqr
###

**Required header:** ``#include <eve/function/sqr.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ sqr = {};
   }

Function object computing the square value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise square value of the :ref:`wide <type-wide>`.
* [2] Computes the square value of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Options
*******

  - ``:ref:`saturated_ <feature-decorator>```: for an integral entry ``a`` the call to ``saturated_(sqr)(a)`` return ``Valmax(as(a))`` as soon as the
    absolute value of ``a`` is greater than ``SqrtValmax(as(a))``

Example
*******

.. include:: ../../../../test/doc/core/sqr.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/sqr.txt
  :literal:
