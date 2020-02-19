#include<stdio.h>
#include<dirent.h>
#include<string.h>
typedef struct
{
  char configSetting[40];
    char configMessage[100];
}Config;
typedef struct
{
    char serialNo[10];
    char tag[25];
    char date[15];
    char time[20];
    char type[20];
    char message[100];
}LogRecord;
Config cf;
LogRecord lr;
FILE*fptr,*fptr1,*fptr2;
void removeDot(char *str)
{
    int i=0;
    while(str[i]!='\0')
    {
        if(str[i]=='.')
        {
            str[i]=' ';
        }
        i++;
    }
}
int main()
{
    char *data;
    char filename[130]="C:\\Users\\Kamal Dua\\Documents\\Virtual Machines\\";
    char actualMachine[30];
    char vmdkFile[130];
    char vmdkData[300];
    char machine[30];
    char filePath[30]="d:\\vmdata\\";
    int i=0;
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
    printf(" <html><head><meta name=viewport content=width=device-width, initial-scale=1><style>body {font-family: Lato, sans-serif;}.sidenav {height: 100%%;width: 350px;position: fixed;z-index: 1;top: 0;left: 0;background-color: #111;overflow-x: hidden;padding-top:20px;}.sidenav a {padding: 6px 8px 6px 16px;text-decoration: none;font-size: 25px;color: #818181;display: block;}.sidenav a:hover {color: #f1f1f1;}.main {margin-left: 350px; font-size: 28px; padding: 0px 10px;}@media screen and (max-height: 450px) {.sidenav {padding-top: 15px;}.sidenav a {font-size: 18px;}}li {color: cyan;} </style></head>");
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
                   i=0;
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
           strcat(filename,actualMachine);
           strcat(filename,"\\");
           strcat(filename,actualMachine);
           strcpy(vmdkFile,filename);
           strcat(filename,".vmx");
           fptr=fopen(filename,"r");
           if(fptr==NULL)
           {
               printf("<b>Error is coming</b>");
           }
           else
           {
               printf("<center><table border=1 style=border-collapse:collapse;><tr><th>Settings</th><th>Configuration</th></tr>");
               strcat(filePath,actualMachine);
               strcat(filePath," vmware");
               strcat(filePath,".txt");
               fptr1=fopen(filePath,"r");
               if(fptr1==NULL)
               {
                   printf("\n error is coming before table");
               }
               else
               {
                   printf("<tr><th colspan=2><center>Processors Description</center></th></tr>");
                   while(1)
                   {
                       
                       fscanf(fptr1,"%[^T]s",lr.serialNo);
                       fseek(fptr1,1,SEEK_CUR);
                       fscanf(fptr1,"%[^T]s",lr.tag);
                       fseek(fptr1,1,SEEK_CUR);
                       fscanf(fptr1,"%[^T]s",lr.date);
                       fseek(fptr1,1,SEEK_CUR);
                       fscanf(fptr1,"%[^T]s",lr.time);
                       fseek(fptr1,1,SEEK_CUR);
                       fscanf(fptr1,"%[^T]s",lr.type);
                       fseek(fptr1,1,SEEK_CUR);
                       fscanf(fptr1,"%[^\n]s",lr.message);
                       if(strstr(lr.tag,"Config")!=NULL)
                       {
                           printf("<tr><td><center>%s</center></td><td><center>%s</center></td></tr>",lr.tag,lr.message);
                       }
                       if(feof(fptr1))
                       {
                           break;
                       }
                       fseek(fptr1,2,SEEK_CUR);
                   }
               }
               printf("<tr><th colspan=2>Virtual Machine Configuration</center></th></tr>");
              while(1)
               {
               fscanf(fptr,"%[^=]s",cf.configSetting);
               fseek(fptr,1,SEEK_CUR);
               fscanf(fptr,"%[^\n]s",cf.configMessage);
                   removeDot(cf.configSetting);
                  printf("<tr><td><center>%s</center></td><td><center>%s</center></td></tr>",cf.configSetting,cf.configMessage);
                   if(feof(fptr))
                   {
                       break;
                   }
               fseek(fptr,2,SEEK_CUR);
               }
               fclose(fptr);
               fclose(fptr1);
               strcat(vmdkFile,".vmdk");
               fptr2=fopen(vmdkFile,"r");
               if(fptr2==NULL)
               {
                   printf("\n error is coming in opeing vmdk file");
               }
               else
               {
                    printf("<tr><th colspan=2><center>Disk Description</center></th></tr>");
                   while(1)
                   {
                       fscanf(fptr2,"%[^\n]s",vmdkData);
                       if(strstr(vmdkData,"ddb")!=NULL)
                       {
                           sscanf(vmdkData,"%[^=]s",cf.configSetting);
                           strcpy(cf.configMessage,strstr(vmdkData,"\""));
                           printf("<tr><td><center>%s</center></td><td><center>%s</center></td></tr>",cf.configSetting,cf.configMessage);
                       }
                       if(feof(fptr2))
                       {
                           break;
                       }
                       fgetc(fptr2);
                      // printf("kya value rhi %d",fseek(fptr2,2,SEEK_CUR)); i dont kow why fseek is not working //here and it is also returning -1 here
                   }
                   fclose(fptr2);
               }
               printf("</table></center></div></body></html>");
           }
    return 0;
}