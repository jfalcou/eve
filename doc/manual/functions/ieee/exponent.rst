.. _function-exponent:

########
exponent
########

**Required header:** ``#include <eve/function/exponent.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ exponent = {};
   }

    This function object returns the internal exponent bit its arguments as an integral based value.



Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s) noexcept;

.. rubric:: Parameters

* **v**, **m**: Instance of :ref:`type-wide`.
* **s**, **n**: Scalar values.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter which must be floating-point based.

Notes
*****

     The exponent ``e`` and mantissa ``m`` of a floating point entry ``x`` are related by
    ``x =  m 2^e``, with  ``|m|`` in ``[1, 2[`` (except for ``x = 0``, where ``m=0`` and ``e=0`` ).

Example
*******

.. include:: ../../../../test/doc/exponent.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/exponent.txt
  :literal:



 