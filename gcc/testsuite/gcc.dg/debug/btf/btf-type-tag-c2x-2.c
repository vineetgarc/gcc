/* Test btf_type_tag on a function's pointer return type using C23 standard
   attribute syntax.  C23 attributes do not "slide" (unlike __attribute__), so
   the tag applies to the pointer return type only when it appears after the
   '*'.  Before the '*' it applies to the pointee, which is a non-pointer and
   is dropped.  PR/125991.  */

/* { dg-do compile } */
/* { dg-options "-O0 -gbtf -dA -std=c23" } */

#define __tag_after  [[gnu::btf_type_tag ("after")]]
#define __tag_before [[gnu::btf_type_tag ("before")]]

/* After '*': tags the pointer return type.
   f: FUNC_PROTO -> ptr -> type_tag("after") -> int  */
int * __tag_after f (int x) { return 0; }

/* Before '*': tags the pointee 'int' (non-pointer) -> dropped, no tag.  */
int __tag_before * g (int x) { return 0; }

/* { dg-final { scan-assembler-times " BTF_KIND_PTR ''(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG 'after'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPE_TAG 'after'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_INT 'int'\\)" 1 } } */
/* { dg-final { scan-assembler-not "BTF_KIND_TYPE_TAG 'before'" } } */
