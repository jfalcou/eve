.. _function-binarize:

########
binarize
########

**Required header:** ``#include <eve/function/binarize.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ binarize = {};
   }

Function object returning a constant or 0 according to test.

Synopsis
********

.. code-block:: c++

   template<typename T, typename U> constexpr T operator()( logical<T> c, U val = 1) noexcept;

* Computes a potentially  optimized version of ``if_else(c, T(val), T(0))``.

Parameters
**********

* ``c``: Instance of a :ref:`logical value <concept-logical>`.
* ``val``: Instance of a :ref:`concept-vectorizable` value convertible to ``T`` or ``eve::mone_`` or ``eve::allbits_``

Return value
**************

* A value with the same type as the base of the :ref:`concept-logical` first parameter (i.e. ``T``).

Notes
******

  - Be aware that for  the first parameter must not be a  :ref:`concept-value` 
    nor a bool but a :ref:`concept-logical` from the base of which the return type is infered.
  
  - U cannot be a vectorized type.

.. seealso::  :ref:`binarize_c <function-binarize_c>`,  :ref:`if_else <function-if_else>`

Example
*******

.. include:: ../../../../test/doc/core/binarize.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/binarize.txt
  :literal:
