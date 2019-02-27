.. _function-bitwise_cast:

##############
bitwise_cast
##############

**Required header:** ``#include <eve/function/bitwise_cast.hpp>``

.. code-block:: c++

   namespace eve
   {
      template < typename T, typename U,  typename N> bitwise_cast( wide<U,N> const& v ) noexcept;
      template < typename T, typename U             > bitwise_cast( U const& v) noexcept;
   }

Function reinterpreting the bit pattern of a value to a possibly different type of same size.

********
Synopsis
********

.. code-block:: c++
  :linenos:

      template < typename T, typename U,  typename N> bitwise_cast( wide<U,N> const& v ) noexcept;
      template < typename T, typename U             > bitwise_cast( U const& s) noexcept;

* [1] Reinterpret a :ref:`Value <concept-value>` **v** of type **wide<U,N>** as a :ref:`Value <concept-value>` of type **T**.
* [2] Reinterpret a scalar value **s** of type **U** as a scalar value of type **T**

.. rubric:: Template parameters

* **T**: expected return type that satisfy:

  * [1] ``sizeof(T) == sizeof(wide<U,N>)`` and **T** must be a :ref:`type-wide` type;
  * [2] ``sizeof(T) == sizeof(U)``.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1-3] A value of type **T**.

.. rubric:: Notes

* :ref:`function-bitwise_cast` does not allow to cast :ref:`type-wide` instances of cardinal 1 to
  scalar as, for performance reasons, such instances are stored as native SIMD registers and
  consequently do not have the proper size to be reinterpreted.

*******
Example
*******

.. include:: ../../../../test/doc/bitwise_cast.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/bitwise_cast.txt
  :literal:
