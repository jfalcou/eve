.. _function-nb_values:

#########
nb_values
#########

**Required header:** ``#include <eve/function/nb_values.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ nb_values = {};
   }

Function object computing the numbers of representable values between two :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N> wide<T,N> operator()( wide<T,N> const& v, wide<T,N> const& w ) noexcept;
   template<typename T, typename N> wide<T,N> operator()( wide<T,N> const& v, T s ) noexcept;
   template<typename T, typename N> wide<T,N> operator()( T s, wide<T,N> const& v)
   template<typename T  constexpr   T         operator()( T s, T t ) noexcept;

* [1] Computes element-wise the number of representable values between two :ref:`wide <type-wide>`.
* [2] Computes element-wise the number of representable values between the :ref:`wide <type-wide>` and the scalar.
* [3] Computes the number of representable values between two scalars.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide`.
* **s**: Scalar value of type T.


.. rubric:: Return value

* [1,2] A value with the integral type associated to the parameters.


.. seealso::  :ref:`ulpdist <function-ulpdist>`,  :ref:`dist <function-dist>`

Example
*******

.. include:: ../../../../test/doc/core/nb_values.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/nb_values.txt
  :literal:
