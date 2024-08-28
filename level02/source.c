int main(void)

{
  int iVar1;
  char *local_10;
  char *local_a8;
  char *local_14;
  char *local_118;
  char *local_78;

  local_10 = fopen("/home/users/level03/.pass","r");
  if (local_10 == (FILE *)0x0) {
    fwrite("ERROR: failed to open password file\n",1,0x24,stderr);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  sVar2 = fread(local_a8,1,0x29,local_10);
  local_14 = (int)sVar2;
  sVar2 = strcspn((char *)local_a8,"\n");
  *(undefined *)((long)local_a8 + sVar2) = 0;
  if (local_14 != 0x29) {
    fwrite("ERROR: failed to read password file\n",1,0x24,stderr);
    fwrite("ERROR: failed to read password file\n",1,0x24,stderr);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  fclose(local_10);
  puts("===== [ Secure Access System v1.0 ] =====");
  puts("/***************************************\\");
  puts("| You must login to access this system. |");
  puts("\\**************************************/");
  printf("--[ Username: ");
  fgets((char *)local_78,100,stdin);
  sVar2 = strcspn((char *)local_78,"\n");
  *(undefined *)((long)local_78 + sVar2) = 0;
  printf("--[ Password: ");
  fgets((char *)local_118,100,stdin);
  sVar2 = strcspn((char *)local_118,"\n");
  *(undefined *)((long)local_118 + sVar2) = 0;
  puts("*****************************************");
  iVar1 = strncmp((char *)local_a8,(char *)local_118,0x29);
  if (iVar1 == 0) {
    printf("Greetings, %s!\n",local_78);
    system("/bin/sh");
    return 0;
  }
  printf((char *)local_78);
  puts(" does not have access!");
  exit(1);
}