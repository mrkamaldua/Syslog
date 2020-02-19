#include<stdio.h>
#include<dirent.h>
#include<string.h>
typedef struct
{
    char serialNo[10];
    char tag[25];
    char date[15];
    char time[20];
    char type[20];
    char message[100];
}LogRecord;
LogRecord lr;
int i=0,j=0,k=0;
float avg;
typedef struct
{
  int dd[4];
  int mm[4];
  int yyyy[4];
}LogsDate;
LogsDate ld;
int disk[4];
int uptime[4];
FILE*fptr,*fptr1;
void printPerformanceDetails(FILE*filterFileKaNaam)
{
    if(filterFileKaNaam)
    {
    while(1)
                   {
          
                       fscanf(filterFileKaNaam,"%[^T]s",lr.serialNo);
                       fseek(filterFileKaNaam,1,SEEK_CUR);
                       fscanf(filterFileKaNaam,"%[^T]s",lr.tag);
                       fseek(filterFileKaNaam,1,SEEK_CUR);
                       fscanf(filterFileKaNaam,"%[^T]s",lr.date);
                       fseek(filterFileKaNaam,1,SEEK_CUR);
                       fscanf(filterFileKaNaam,"%[^T]s",lr.time);
                       fseek(filterFileKaNaam,1,SEEK_CUR);
                       fscanf(filterFileKaNaam,"%[^T]s",lr.type);
                       fseek(filterFileKaNaam,1,SEEK_CUR);
                       fscanf(filterFileKaNaam,"%[^\n]s",lr.message);
        if(feof(filterFileKaNaam))
                       {
                           break;
                       }
                       if(strstr(lr.tag,"GeneralOPEN"))
                       {
                           sscanf(lr.date,"%d-%d-%d",&ld.yyyy[k],&ld.mm[k],&ld.dd[k]);
                           k++;
                       }
                       if(strstr(lr.tag,"Perfor")!=NULL)
                       {
                           
                           if(strstr(lr.tag,"PerforDisk"))
                           {
                               sscanf(lr.message," I125: DISK: Opening disks took %d ms.",&disk[i]);
                               i++;
                           }
                           else if(strstr(lr.tag,"PerforUptime"))
                           {
                               sscanf(lr.message," I125: System uptime %6d us",&uptime[j]);
                               j++;
                           }
                       }
                       fseek(filterFileKaNaam,2,SEEK_CUR);
                   }
    }
    else
    {
        printf("\nerror is coming");
    }
}
int main()
{
    char *data;
    char actualMachine[30];
    char machine[30];
    char filePath[30]="d:\\vmdata\\";
    char *tempfilepath="d:\\vmdata\\";
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
    printf(" <html><head>");
           printf("<meta name=viewport content=width=device-width, initial-scale=1><style>body {font-family: Lato, sans-serif;}.sidenav {height: 100%%;width: 350px;position: fixed;z-index: 1;top: 0;left: 0;background-color: #111;overflow-x: hidden;padding-top:20px;}.sidenav a {padding: 6px 8px 6px 16px;text-decoration: none;font-size: 25px;color: #818181;display: block;}.sidenav a:hover {color: #f1f1f1;}.main {margin-left: 350px; font-size: 28px; padding: 0px 10px;}@media screen and (max-height: 450px) {.sidenav {padding-top: 15px;}.sidenav a {font-size: 18px;}}li {color: cyan;}#chartContainer{height:300px;width:500;align-content:center;}#hostUptime{height:300px;width:500;align-content:center;}</style>");
                  printf("</head>");
    
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
    
    
               strcat(filePath,actualMachine);
               strcat(filePath," vmware");
               strcat(filePath,".txt");
               fptr1=fopen(filePath,"r");
               printPerformanceDetails(fptr1);
               fclose(fptr1);
    
    
    
               strcpy(filePath,tempfilepath);
               strcat(filePath,actualMachine);
               strcat(filePath," vmware-0");
               strcat(filePath,".txt");
               fptr1=fopen(filePath,"r");
               printPerformanceDetails(fptr1);
               fclose(fptr1);
    
    
               strcpy(filePath,tempfilepath);
               strcat(filePath,actualMachine);
               strcat(filePath," vmware-1");
               strcat(filePath,".txt");
               fptr1=fopen(filePath,"r");
               printPerformanceDetails(fptr1);
               printf("</table></center>");
               fclose(fptr1);
    
    
               strcpy(filePath,tempfilepath);
               strcat(filePath,actualMachine);
               strcat(filePath," vmware-2");
               strcat(filePath,".txt");
               fptr1=fopen(filePath,"r");
               printPerformanceDetails(fptr1);
               fclose(fptr1);
    
 printf("<center><div id=chartContainer></div></center>");
        printf("<script type=text/javascript src=http://localhost:8080/SYSLOG/canvasjs.min.js></script>");
    printf("<script>window.onload = function () {var chart = new CanvasJS.Chart(\"chartContainer\", {animationEnabled: true,theme: \"light1\",title:{text: \"Disk Access time\"},axisY: {title: \"Time Taken(in ms)\"},data: [{        type: \"column\",  showInLegend: true, legendMarkerColor: \"grey\",legendText: \"ms=miliseconds\",dataPoints: [      { y: %d, label: \"%d-%d-%d\" },{ y: %d,  label: \"%d-%d-%d\" },{ y: %d,  label: \"%d-%d-%d\" },{ y: %d,  label: \"%d-%d-%d\" }]}]});chart.render();",disk[0],ld.yyyy[0],ld.mm[0],ld.dd[0],disk[1],ld.yyyy[1],ld.mm[1],ld.dd[1],disk[2],ld.yyyy[2],ld.mm[2],ld.dd[2],disk[3],ld.yyyy[3],ld.mm[3],ld.dd[3]);
   
    
    
    
    
    printf("var chart = new CanvasJS.Chart(\"hostUptime\", {animationEnabled: true,theme: \"light1\",title:{text: \"Host Uptime\"},axisY: {title: \"Time Taken(in s)\"},data: [{        type: \"area\",  showInLegend: true, legendMarkerColor: \"grey\",legendText: \"s=seconds\",dataPoints: [      { y: %d, label: \"%d-%d-%d\" },{ y: %d,  label: \"%d-%d-%d\" },{ y: %d,  label: \"%d-%d-%d\" },{ y: %d,  label: \"%d-%d-%d\" }]}]});chart.render();}</script>",uptime[0],ld.yyyy[0],ld.mm[0],ld.dd[0],uptime[1],ld.yyyy[1],ld.mm[1],ld.dd[1],uptime[2],ld.yyyy[2],ld.mm[2],ld.dd[2],uptime[3],ld.yyyy[3],ld.mm[3],ld.dd[3]);
    printf("<center><div id=hostUptime></div></center>");
     avg=(float)(disk[0]+disk[1]+disk[2]+disk[3])/4.0;
               printf("<br><center><strong>average disk access time is %f</strong></center>",avg);
        printf("</div>");
               printf("</body></html>");
           
    return 0;
}
