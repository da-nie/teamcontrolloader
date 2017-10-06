#include <windows.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

//------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevstance,LPSTR lpstrCmdLine,int nCmdShow)
{
 char FileName[MAX_PATH];
 GetModuleFileName(NULL,FileName,MAX_PATH);
 //отматываем до черты
 long size=strlen(FileName);
 if (size>0) size--;
 while(size>0)
 {
  unsigned char s=FileName[size];
  if (s==0 || s=='\\')
  {
   FileName[size+1]=0;
   break;
  }
  size--;
 }
 SetCurrentDirectory(FileName);
 FILE *file=fopen("TeamControlClient.exe","rb");
 if (file!=NULL) 
 {
  fclose(file);
  //удаляем программу
  while(1)
  {
   if (DeleteFile("TeamControlClient.exe")==TRUE) break;
   HANDLE event=CreateEvent(NULL,FALSE,FALSE,NULL);
   ResetEvent(event);
   WaitForSingleObject(event,100);
   DeleteObject(event);
  }
 }
 //выполняем переименование программы
 MoveFile("TeamControlClient_New.exe","TeamControlClient.exe"); 
 //запускаем основную программу
 ShellExecute(NULL,NULL,"TeamControlClient.exe",NULL,NULL,SW_SHOWNORMAL);
 return(0);
}