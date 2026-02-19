/* { dg-do compile } */
/* { dg-options "-O2 -mcpu=v4" } */

extern int bpf_copy_from_user_str(int dst__sz);

_Bool verify_sleepable_user_copy_str(void)
{
 int ret;
 char data_short_pad[4];

 ret = bpf_copy_from_user_str(sizeof(data_short_pad));
 if (ret != 4)
  return false;

 ret = bpf_copy_from_user_str(sizeof(data_short_pad));
 if (ret != 4)
  return false;

  return true;
}

/* Generate an explicit cast of return as next call's arg.  */
/* { dg-final { scan-assembler-times {\(s32\)\sr0} 1 } } */
