
void log_wrapper(FILE *param_1,char *param_2,char *param_3)

{
  char cVar1;
  size_t sVar2;
  ulong uVar3;
  ulong uVar4;
  char *pcVar5;
  long in_FS_OFFSET;
  byte bVar6;
  undefined8 local_120;
  char local_118 [264];
  long local_10;
  
  bVar6 = 0;
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_120 = param_1;
  strcpy(local_118,param_2);
  uVar3 = 0xffffffffffffffff;
  pcVar5 = local_118;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + (ulong)bVar6 * -2 + 1;
  } while (cVar1 != '\0');
  uVar4 = 0xffffffffffffffff;
  pcVar5 = local_118;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + (ulong)bVar6 * -2 + 1;
  } while (cVar1 != '\0');
  snprintf(local_118 + (~uVar4 - 1),0xfe - (~uVar3 - 1),param_3);
  sVar2 = strcspn(local_118,"\n");
  local_118[sVar2] = '\0';
  fprintf(local_120,"LOG: %s\n",local_118);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


int main(int param_1,undefined8 *param_2)
{
  char cVar1;
  int __fd;
  int iVar2;
  FILE *pFVar3;
  FILE *__stream;
  ulong uVar4;
  undefined8 *puVar5;
  long in_FS_OFFSET;
  byte bVar6;
  char local_79;
  undefined8 local_78;
  undefined2 local_70;
  char local_6e;
  long local_10;
  
  bVar6 = 0;
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_79 = -1;
  if (param_1 != 2) {
    printf("Usage: %s filename\n",*param_2);
  }
  pFVar3 = fopen("./backups/.log","w");
  if (pFVar3 == (FILE *)0x0) {
    printf("ERROR: Failed to open %s\n","./backups/.log");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  log_wrapper(pFVar3,"Starting back up: ",param_2[1]);
  __stream = fopen((char *)param_2[1],"r");
  if (__stream == (FILE *)0x0) {
    printf("ERROR: Failed to open %s\n",param_2[1]);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  local_78._0_1_ = '.';
  local_78._1_1_ = '/';
  local_78._2_1_ = 'b';
  local_78._3_1_ = 'a';
  local_78._4_1_ = 'c';
  local_78._5_1_ = 'k';
  local_78._6_1_ = 'u';
  local_78._7_1_ = 'p';
  local_70._0_1_ = 's';
  local_70._1_1_ = '/';
  local_6e = '\0';
  uVar4 = 0xffffffffffffffff;
  puVar5 = &local_78;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *(char *)puVar5;
    puVar5 = (undefined8 *)((long)puVar5 + (ulong)bVar6 * -2 + 1);
  } while (cVar1 != '\0');
  strncat((char *)&local_78,(char *)param_2[1],99 - (~uVar4 - 1));
  __fd = open((char *)&local_78,0xc1,0x1b0);
  if (__fd < 0) {
    printf("ERROR: Failed to open %s%s\n","./backups/",param_2[1]);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  while( true ) {
    iVar2 = fgetc(__stream);
    local_79 = (char)iVar2;
    if (local_79 == -1) break;
    write(__fd,&local_79,1);
  }
  log_wrapper(pFVar3,"Finished back up ",param_2[1]);
  fclose(__stream);
  close(__fd);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return 0;
}
