/* Test btf_type_tag on a function return type, attribute in the prefix
   position (before all declaration specifiers).  PR/125991.

     __attribute__((btf_type_tag("B"))) int *b (int y);

   The tag applies to the (pointer) return type:
     b: FUNC_PROTO -> ptr -> type_tag("B") -> int  */

/* { dg-do compile } */
/* { dg-options "-O0 -gbtf -dA" } */

__attribute__((btf_type_tag ("B"))) int *b (int y) { return 0; }

/* { dg-final { scan-assembler-times " BTF_KIND_FUNC_PROTO ''(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_PTR ''\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_PTR ''(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG 'B'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPE_TAG 'B'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_INT 'int'\\)" 1 } } */
