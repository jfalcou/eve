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

Function performing reinterpretation of a pattern of bit to a possibly different type of same bit size.



********
Synopsis
********

.. code-block:: c++
  :linenos:

      template < typename T, typename U,  typename N> bitwise_cast( wide<U,N> const& v ) noexcept;
      template < typename T, typename U             > bitwise_cast( U const& s) noexcept;

* [1] Reinterpret a  :ref:`Value <concept-value>` *v* of type *wide<U,N>* as a :ref:`Value <concept-value>` of type *T*.
* [2] Reinterpret a scalar value  *s* of type *U* as a scalar value of type *T*

.. rubric:: Template parameters

* **T**: expected return type that satisfy:

  * [1] ``sizeof(T) == sizeof(wide<U,N>)`` and **T** must be a  :ref:`type-wide` type; 
  * [2] ``sizeof(T) == sizeof(U)``.
  
.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1-3] A value of type *T*.

.. rubric:: Notes

* `bitwise_cast` does not allow to cast :ref:`type-wide` instances to scalar ones because, for performance reasons, the `small`  :ref:`type-wide` types (i.e. smaller than the SIMD native registers of the architecture) are  stored as native SIMD registers and consequently does not share the  scalar sizes in the supported architectures. In fact the bit size of supported wides is always greater of equal to 128 bits and the size of supported scalars is always less or equal to 64 bits.


*******
Example
*******

.. include:: ../../../../test/doc/bitwise_cast.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/bitwise_cast.txt
  :literal:
