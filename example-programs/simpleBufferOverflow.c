/*
  Example program from the CBMC tutorial: http://www.cprover.org/cprover-manual/cbmc/tutorial/

  Running `cbmc example-programs/simpleBufferOverflow.c --show-properties --bounds-check` e.g. should
  show a buffer overflow error.
*/
int main()
{
  int buffer[10];
  buffer[20] = 10;
}
