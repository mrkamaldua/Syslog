#include<stdio.h>
#include<string.h>
#include<dirent.h>
int fad=0;
char*tempfilename="C:\\Users\\Kamal Dua\\Documents\\Virtual Machines\\";
char filename[130]="C:\\Users\\Kamal Dua\\Documents\\Virtual Machines\\";
char*tempfilepath="d:\\vmdata\\";
char filePath[50]="d:\\vmdata\\";
char num[10];
int currentDisplay=0;
int bluetooth=0;
char serialNumber[5];
FILE*fptr=NULL,*fptr1=NULL,*fptr2;
typedef struct
   {
    int i;
    char tag[20];
     char date[20];
     char time[30];
     char type[10];
     char message[9000];
   }LogRecord;
void avoidRepeat(char *str,LogRecord*lr)
{
           fputs(itoa(lr->i,num,10),fptr1);
           fputc('T',fptr1);
           fputs(str,fptr1);
           fputc('T',fptr1);
           fputs(lr->date,fptr1);
           fputc('T',fptr1);
           fputs(lr->time,fptr1);
           fputc('T',fptr1);
           fputs(lr->type,fptr1);
           fputc('T',fptr1);
           fputs(lr->message,fptr1);
           fputc('\n',fptr1);   
}
  
void filerToNewLogFile(FILE*LogFileKaNaam,FILE*FilterFileKaNaam)
{
    LogRecord lr;
     lr.i=1;
   while(1)
     {
  fscanf(LogFileKaNaam,"%[^T]s",lr.date);
  fseek(LogFileKaNaam,1,SEEK_CUR);
  fscanf(LogFileKaNaam,"%[^|]s",lr.time);
  fseek(LogFileKaNaam,1,SEEK_CUR);
  fscanf(LogFileKaNaam,"%[^|]s",lr.type);
  fseek(LogFileKaNaam,1,SEEK_CUR);
 if(fscanf(LogFileKaNaam,"%[^\n]s",lr.message)==EOF)
  {
      break;
  }
       if(lr.i==1)
       {
           avoidRepeat("GeneralOPEN",&lr);
       }
       if(strstr(lr.message,"Host is")!=NULL)
       {
           avoidRepeat("GeneralHostDetails",&lr);
       }
       if(strstr(lr.message,"Hostname")!=NULL)
       {
           avoidRepeat("GeneralHostname",&lr);
       }
       if(strstr(lr.message,"IP=")!=NULL)
       {
           avoidRepeat("NetworkIP",&lr);
       }
       if(strstr(lr.message,"System uptime")!=NULL)
       {
           avoidRepeat("PerforUptime",&lr);
       }
       if(strstr(lr.message,"CPUID vendor")!=NULL||strstr(lr.message,"CPUID name")!=NULL)
       {
           avoidRepeat("ConfigProcessor",&lr);
       }
       if(strstr(lr.message,"ERRORS")!=NULL)
       {
           avoidRepeat("GeneralERRORS",&lr);   
       }
       if(strstr(lr.message,"sata0:1.fileName")!=NULL)
       {
           avoidRepeat("GeneralIsoLocation",&lr);
       }
       if(strstr(lr.message,"sharedFolder")&&strstr(lr.message,"hostPath"))
       {
           avoidRepeat("GeneralSharedFolder",&lr);
       }
       if(strstr(lr.message,"NumVCPUs")!=NULL)
       {
           avoidRepeat("ConfigVCPUS",&lr);
       }
       if(strstr(lr.message,"Opening disks")!=NULL)
       {
           avoidRepeat("PerforDiskAccess",&lr);
       }
       if(strstr(lr.message,"HOSTINFO")!=NULL)
       {
           avoidRepeat("Generaltscrate",&lr);
       }
       if(strstr(lr.message,"Bluetooth host backend")!=NULL&&bluetooth==0)
       {
           bluetooth=1;
           avoidRepeat("NetworkBluetooth",&lr);
       }
       if(strstr(lr.message,"error"))
       {
           avoidRepeat("ERROR",&lr);
       }
    
    fseek(LogFileKaNaam,2,SEEK_CUR);
       
       if(strstr(lr.message,"cleanup")!=NULL)
         {
           fputs(itoa(lr.i,num,10),FilterFileKaNaam);
           fputc('T',FilterFileKaNaam);
           fputs("GeneralCLOSE",FilterFileKaNaam);
           fputc('T',FilterFileKaNaam);
           fputs(lr.date,FilterFileKaNaam);
           fputc('T',FilterFileKaNaam);
           fputs(lr.time,FilterFileKaNaam);
           fputc('T',FilterFileKaNaam);
           fputs(lr.type,FilterFileKaNaam);
           fputc('T',FilterFileKaNaam);
           fputs(lr.message,FilterFileKaNaam);
           break;
        }
     lr.i++;
     }
    bluetooth=0;
  }     
void printingTheGeneralDetailsInVm(FILE*FilterFileKaNaam)
{
    LogRecord lr;
       while(1)
                   {
                       fscanf(FilterFileKaNaam,"%[^T]s",serialNumber);
                       fseek(FilterFileKaNaam,1,SEEK_CUR);
                       fscanf(FilterFileKaNaam,"%[^T]s",lr.tag);
                       fseek(FilterFileKaNaam,1,SEEK_CUR);
                       fscanf(FilterFileKaNaam,"%[^T]s",lr.date);
                       fseek(FilterFileKaNaam,1,SEEK_CUR);
                       fscanf(FilterFileKaNaam,"%[^T]s",lr.time);
                       fseek(FilterFileKaNaam,1,SEEK_CUR);
                       fscanf(FilterFileKaNaam,"%[^T]s",lr.type);
                       fseek(FilterFileKaNaam,1,SEEK_CUR);
                       fscanf(FilterFileKaNaam,"%[^\n]s",lr.message);
                       if(strstr(lr.tag,"General")!=NULL)
                       {
                           printf("<tr><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>",lr.tag,lr.message,lr.date,lr.time);
                       }
                       if(feof(fptr1))
                       {
                           break;
                       }
                       fseek(fptr1,2,SEEK_CUR);  
                      
                   }
}
  checkFiltration(char*actualMachine)
  {   
      strcat(filePath,actualMachine);
      strcat(filePath," vmware.txt");
      fptr1=fopen(filePath,"r");
      if(!fptr1)
          return;
      else
      {
                       LogRecord lr1,lr2;
                       fscanf(fptr1,"%[^T]s",serialNumber);
                       fseek(fptr1,1,SEEK_CUR);
                       fscanf(fptr1,"%[^T]s",lr1.tag);
                       fseek(fptr1,1,SEEK_CUR);
                       fscanf(fptr1,"%[^T]s",lr1.date);
                       fseek(fptr1,1,SEEK_CUR);
                       fscanf(fptr1,"%[^T]s",lr1.time);
                       fclose(fptr1);
                       strcat(filename,actualMachine);
                       strcat(filename,"\\vmware.log");
                       fptr=fopen(filename,"r");
                       fscanf(fptr,"%[^T]s",lr2.date);
                       fseek(fptr,1,SEEK_CUR);
                       fscanf(fptr,"%[^|]s",lr2.time);
                       fclose(fptr);
          if(!strcmp(lr1.date,lr2.date)&&!strcmp(lr1.time,lr2.time))
          {
              fad=1;
          }            
      }
  }
void newFunc(char*actualMachine,char*str)
  {
    strcpy(filename,tempfilename);
    strcpy(filePath,tempfilepath);
    strcat(filename,actualMachine);
    strcat(filename,str);
    strcat(filename,".log");
    fptr=fopen(filename,"r");
    strcat(filePath,actualMachine);
    strcat(filePath," ");
    strcat(filePath,&str[1]);
    strcat(filePath,".txt");
    if(!fad)
    {
        fptr1=fopen(filePath,"w");
      filerToNewLogFile(fptr,fptr1);
    }
    fclose(fptr1);
    fclose(fptr);
    fptr1=fopen(filePath,"r");
    printf("<tr><th colspan=4></b>%s</b></th></tr>",&str[1]);
    printingTheGeneralDetailsInVm(fptr1);
  }
int main()
{
  int i=0;
    char machine[20];
    char actualMachine[20];    
  char *data;
  LogRecord lr;
  printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
  data=getenv("QUERY_STRING");
  sscanf(data,"machine=%s",actualMachine);
    while(actualMachine[i]!='\0')
    {
        if(actualMachine[i]=='+')
        {
            actualMachine[i]=' ';
        }
        i++;
    }
    
     printf(" <html><head><meta name=viewport http-equiv=Content-Type content=\"text/html; charset=utf-8\" content-width=device-width, initial-scale=1/><style>body {font-family: Lato, sans-serif;}.sidenav {height: 100%%;width: 350px;position: fixed;z-index: 1;top: 0;left: 0;background-color: #111;overflow-x: hidden;padding-top:20px;}.sidenav a {padding: 6px 8px 6px 16px;text-decoration: none;font-size: 25px;color: #818181;display: block;}.sidenav a:hover {color: #f1f1f1;}.main {margin-left: 350px; font-size: 28px; padding: 0px 10px;}@media screen and (max-height: 450px) {.sidenav {padding-top: 15px;}.sidenav a {font-size: 18px;}}li {color: cyan;} </style></head>");
            printf("<body>"); printf("<div class=sidenav>");
         struct dirent *de; 
           DIR *dr = opendir("C:\\Users\\Kamal Dua\\Documents\\Virtual Machines"); 
           if (dr == NULL) 
           { 
            printf("Could not open current directory" );  
           }
           else{
              printf("<ul>");
              while ((de = readdir(dr)) != NULL)
              {
                  if(strcmp(de->d_name,".")==0||strcmp(de->d_name,"..")==0)
                      continue;
                  strcpy(machine,de->d_name);
                  int i=0;
                  while(machine[i]!='\0')
                  {
                      if(machine[i]==' ')
                      {
                          machine[i]='+';
                      }
                      i++;
                  }
              printf("<li><a href=Vm.cgi?machine=%s>%s</a>",machine,de->d_name);
                  if(strcmp(actualMachine,de->d_name)==0)
                  {
                  printf("<ul><li><a href=Network.cgi?machine=%s>Network Details</a></li><li><a href=Configuration.cgi?machine=%s>Configuration Details</a></li><li><a href=Performance.cgi?machine=%s>Performance Details</a></li><li><a href=ErrorPool.cgi?machine=%s>Error Pool</a></li><li><a href=Stats.cgi?machine=%s>Statistics</li></a></ul>",machine,machine,machine,machine,machine);
                  }
                  
              }
               
           }
           closedir(dr);  
           printf("</ul></div>");
           printf("<div class=main><center><h2>Welcome to your Virtual Machine</h2></center>");
    
    
    printf("<center><h1>%s</h1></center>",actualMachine);
    printf("<center><table border=1 style=border-collapse:collapse;><tr><th>General Details</th><th>Remarks</th><th>Date</th><th>Time</th></tr>");
    checkFiltration(actualMachine);
    newFunc(actualMachine,"\\vmware");
    
    newFunc(actualMachine,"\\vmware-0");
    
    newFunc(actualMachine,"\\vmware-1");

    newFunc(actualMachine,"\\vmware-2");
               printf("</table></center>");
    
    
    printf("</div></body></html>");
return 0;
}