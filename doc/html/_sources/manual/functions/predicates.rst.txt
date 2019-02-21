.. _function-predicates:

Predicates Functions
====================

These functions provide scalar and SIMD version of logical  predicates functions.
Thes functions always return a :ref:`concept-logical` type
For most of them, the semantic are the same as regular language operators
or functions with the one restriction that both parameters must share a type unless specified
otherwise and return a  :ref:`concept-logical` value associated to this common type.

.. toctree::
   :maxdepth: 1
   :glob:

   predicates/*
