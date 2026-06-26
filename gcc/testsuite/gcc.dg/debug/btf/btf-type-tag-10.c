/* Test btf_type_tag on a function's pointer return type with the
   __attribute__ placed immediately after the '*' (i.e. on the pointer
   itself).  The tag applies to the pointer return type.  PR/125991.

     f: FUNC_PROTO -> ptr -> type_tag("A") -> int  */

/* { dg-do compile } */
/* { dg-options "-O0 -gbtf -dA" } */

int * __attribute__((btf_type_tag ("A"))) f (int x) { return 0; }

/* { dg-final { scan-assembler-times " BTF_KIND_FUNC_PROTO ''(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_PTR ''\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_PTR ''(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG 'A'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPE_TAG 'A'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_INT 'int'\\)" 1 } } */
