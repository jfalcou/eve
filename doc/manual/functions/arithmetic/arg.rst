.. _function-arg:

#######
arg
#######

**Required header:** ``#include <eve/function/arg.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ arg = {};
   }

Function object computing argument of a :ref:`IEEEValue <concept-ieeevalue>`.


Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise argument of the :ref:`wide <type-wide>`.
* [2] Computes the argument of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Options
*******

 -  With the :ref:`pedantic_ <feature-decorator>` decorator this function return a Nan for a Nan entry.

Notes
*****

This function is not defined for :ref:`concept-integralvalue` types.
For :ref:`IEEEValue <concept-ieeevalue>`  entries it returns the value zero if the bit of sign of the entry is not set and the value ``pi`` if it is set.
Its use will be extended in a future complex module.

Example
*******

.. include:: ../../../../test/doc/core/arg.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/arg.txt
  :literal:
