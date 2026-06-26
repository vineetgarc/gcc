/* Test generation of BTF type tags on a function's pointer return type and on
   its arguments.  PR/125991.

   btf_type_tag is only meaningful on a pointer type, so the directly-tagged
   return must be a pointer; here it carries two tags.  The arguments are
   tagged via typedefs.  Each tagged type results in a BTF_KIND_TYPE_TAG record
   inserted into the appropriate chain of the BTF_KIND_FUNC_PROTO:

     func: FUNC_PROTO -> ret  ptr -> type_tag("type2") -> type_tag("type1") -> int
                      -> arg0 typedef("TYP1") -> type_tag("type1") -> int
                      -> arg1 typedef("TYP2") -> type_tag("type2") -> int  */

/* { dg-do compile } */
/* { dg-options "-O0 -gbtf -dA" } */

#define __tag1 __attribute__((btf_type_tag ("type1")))
#define __tag2 __attribute__((btf_type_tag ("type2")))

typedef int __tag1 TYP1;
typedef int __tag2 TYP2;

int __tag1 __tag2 * func (TYP1 arg_a, TYP2 arg_b)
{
  return 0;
}

/* Return is a pointer carrying type2 -> type1.  */
/* { dg-final { scan-assembler-times " BTF_KIND_FUNC_PROTO ''(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_PTR ''\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_PTR ''(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG 'type2'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPE_TAG 'type2'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG 'type1'\\)" 1 } } */

/* Argument chains via typedefs.  */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPEDEF 'TYP1'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG 'type1'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPEDEF 'TYP2'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG 'type2'\\)" 1 } } */
