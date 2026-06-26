/* Test btf_type_tag on a function return type, attribute in the postfix
   position (after the declarator).  PR/125991.

     int *c (int z) __attribute__((btf_type_tag("C")));

   A postfix attribute is not permitted on a function definition, so 'c' is
   declared and referenced via a caller to force BTF emission.  The tag applies
   to the (pointer) return type:
     c: FUNC_PROTO -> ptr -> type_tag("C") -> int  */

/* { dg-do compile } */
/* { dg-options "-O0 -gbtf -dA" } */

int *c (int z) __attribute__((btf_type_tag ("C")));

int *caller (int z) { return c (z); }

/* { dg-final { scan-assembler-times " BTF_KIND_PTR ''(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG 'C'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPE_TAG 'C'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_INT 'int'\\)" 1 } } */
