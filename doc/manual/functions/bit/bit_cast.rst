.. _function-bit_cast:

##############
bit_cast
##############

**Required header:** ``#include <eve/function/bit_cast.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bit_cast = {};
   }

Function reinterpreting the bit pattern of a value to a possibly different type of same size.

Synopsis
********

.. code-block:: c++

   template<typename T, typename U>  U operator()( T const& x, as_<U> const & target) noexcept;


* Reinterpret a :ref:`Value <concept-value>` of type ``T`` as a :ref:`Value <concept-value>` of type ``U``.

Parameters
**********

* ``T`` and ``U`` must be simultaneously  :ref:`concept-vectorized` or  :ref:`concept-vectorizable` and of the same global size.
* ``x``: Instance of a  :ref:`Value <concept-value>`.
* ``target``: Instance of a :ref:` targeted value <concept-targetvalue>`.

Return value
************

*  A value of type ``U``.

Notes
*****

* :ref:`function-bit_cast` does not allow to cast :ref:`type-wide` instances of cardinal ``1`` to
  :ref:`concept-vectorizable` types as, for performance reasons, such instances are stored as native SIMD registers and
  consequently do not have the proper size to be reinterpreted.

Example
*******

.. include:: ../../../../test/doc/core/bit_cast.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/bit_cast.txt
  :literal:
