/* Test generation of BTF type tags on a function whose return type and
   arguments are tagged typedefs.  PR/125888.

     foo: FUNC_PROTO -> ret  typedef("PERCPU_T") -> type_tag("percpu") -> int
                     -> args typedef("CPU_T")    -> type_tag("cpu")    -> int  */

/* { dg-do compile } */
/* { dg-options "-O0 -gbtf -dA" } */

#define __tag1 __attribute__((btf_type_tag("percpu")))
#define __tag2 __attribute__((btf_type_tag("cpu")))

typedef int __tag1 PERCPU_T;
typedef int __tag2 CPU_T;

PERCPU_T foo (CPU_T a, CPU_T b)
{
  PERCPU_T c = a + b;
  return c;
}

/* Return is the tagged typedef PERCPU_T.  */
/* { dg-final { scan-assembler-times " BTF_KIND_FUNC_PROTO ''(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPEDEF 'PERCPU_T'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPEDEF 'PERCPU_T'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG 'percpu'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPE_TAG 'percpu'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_INT 'int'\\)" 1 } } */

/* Arguments are the tagged typedef CPU_T.  */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPEDEF 'CPU_T'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG 'cpu'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPE_TAG 'cpu'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_INT 'int'\\)" 1 } } */
