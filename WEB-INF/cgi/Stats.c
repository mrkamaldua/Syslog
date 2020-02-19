#include<stdio.h>
#include<dirent.h>
#include<string.h>
typedef struct 
{
    int dd;
    int mm;
    int yy;
}Date;
  typedef struct 
  {
      int hh;
      int min;
  }Time;
typedef struct
{
    Date sd;
    Date ed;
    Time st;
    Time et;
}VmTime;
VmTime arr[4];
int finalMinutes[4];
int counter=0;
typedef struct
{
    char serialNo[10];
    char tag[25];
    char date[15];
    char time[20];
    char type[20];
    char message[600];
}LogRecord;
LogRecord lr;
FILE*fptr,*fptr1;

int leapYear(int year)
     {
        if(year%400==0)
        {
            return 1;
        }
        else
        {
            if(year%4==0&&year%100!=0)
            {
             return 1;
            }
        }
        return 0;
        //return (year%400==0)?1:((year%4==0&&year%100!=0)?1:0);
     }
   int noOfLeap(int a,int b)
      {
          int i=0;
          while(a<=b)
          {
              if(leapYear(a))
              {
                  i++;
              }
              a++;
          }
          return i;
      }
   int countNoOfMinutes(Date*d1,Date*d2,Time*t1,Time*t2)
      {
          int no_of_minutes;
       int i;
          int arr[12]={31,28,31,30,31,30,31,31,30,31,30,31};
          int y=d2->yy-d1->yy;
          int no_of_days=0;
          if(y>=1)
          {
              int no_of_leap=noOfLeap(d1->yy,d2->yy-1);
              no_of_days=(y-no_of_leap-1)*365+no_of_leap*366;
              no_of_days=no_of_days+arr[d1->mm-1]-d1->dd;
              if(leapYear(d1->dd+y-1))
              {
                if(d1->mm<=2)
                 {
                  no_of_days=no_of_days+1;
                 }
              }
                for(i=d1->mm;i<12;i++)
                  {
                      no_of_days=no_of_days+arr[i];
                  }
                  for(i=0;i<d2->mm-1;i++)
                    {
                      no_of_days=no_of_days+arr[i];
                    }
                     no_of_days=no_of_days+d2->dd;
                     if(leapYear(d2->yy)&&d2->mm>2)
                     {
                         no_of_days=no_of_days+1;
                     }
          }
          else
          {
              if(d2->mm-d1->mm>0)
              {
                 no_of_days=arr[d1->mm-1]-d1->dd;
                 for(i=d1->mm;i<d2->mm-1;i++)
                 {
                  no_of_days=no_of_days+arr[i];
                 }
                 no_of_days=no_of_days+d2->dd;
                 if(leapYear(d1->yy))
                 {
                     if(d1->mm<=2)
                     {
                         no_of_days=no_of_days+1;
                     }
                 }
              }
              else
              {
                  no_of_days=d2->dd-d1->dd;
              }
          }
         // printf("\n no of days are %d",no_of_days);
          if(no_of_days>=1)
          {
              if(t2->hh>=t1->hh)
              {
                    no_of_minutes=60*t2->hh+t2->min-60*t1->hh-t1->min+no_of_days*24*60;
              }
              else
              {
                  no_of_minutes=no_of_days*24*60-(60*t1->hh+t1->min-60*t2->hh-t2->min);
              }
          }
          else
          {
              no_of_minutes=60*t2->hh+t2->min-60*t1->hh-t1->min;
          }
        //  printf("\n no of minutes are %d",no_of_minutes);
          return no_of_minutes;
      }
void storeUsageDetails(FILE*filterFileKaNaam)
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
                       if(strstr(lr.tag,"GeneralOPEN")!=NULL)
                       {
                            sscanf(lr.date,"%d-%d-%d",&(arr[counter].sd.yy),&(arr[counter].sd.mm),&(arr[counter].sd.dd));
                           //printf("<br>%d-%d-%d",(arr[counter].sd.yy),(arr[counter].sd.mm),(arr[counter].sd.dd));
                           sscanf(lr.time,"%d:%d",&(arr[counter].st.hh),&(arr[counter].st.min));
                           //printf("<br>%d:%d",(arr[counter].st.hh),(arr[counter].st.min));
                       }
                       if(strstr(lr.tag,"GeneralCLOSE")!=NULL)
                       {
                           sscanf(lr.date,"%d-%d-%d",&(arr[counter].ed.yy),&(arr[counter].ed.mm),&(arr[counter].ed.dd));
                           //printf("<br>%d-%d-%d",(arr[counter].ed.yy),(arr[counter].ed.mm),(arr[counter].ed.dd));
                           
                          sscanf(lr.time,"%d:%d",&(arr[counter].et.hh),&(arr[counter].et.min));
                           //printf("<br>%d:%d",(arr[counter].et.hh),(arr[counter].et.min));
                       }
                       if(feof(filterFileKaNaam))
                       {
                           break;
                       }
                       fseek(filterFileKaNaam,2,SEEK_CUR);
                       
                   }
        counter++;
    }
    else
    {
        printf("\nerror is coming");
        printf("\n kaha yaha par aaya");
    }
}
int main()
{
    char *data;
    char actualMachine[30];
    char machine[30];
    char filePath[60]="d:\\vmdata\\";
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
    printf(" <html><head><meta charset=utf-8  name=viewport content-width=device-width, initial-scale=1><style>body {font-family: Lato, sans-serif;}.sidenav {height: 100%%;width: 350px;position: fixed;z-index: 1;top: 0;left: 0;background-color: #111;overflow-x: hidden;padding-top:20px;}.sidenav a {padding: 6px 8px 6px 16px;text-decoration: none;font-size: 25px;color: #818181;display: block;}.sidenav a:hover {color: #f1f1f1;}.main {margin-left: 350px; font-size: 28px; padding: 0px 10px;}@media screen and (max-height: 450px) {.sidenav {padding-top: 15px;}.sidenav a {font-size: 18px;}}li {color: cyan;} </style></head>");
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
           printf("<center><b><h2>%s</h2></b></center>",actualMachine);
               
    
    
                   strcat(filePath,actualMachine);
               strcat(filePath," vmware");
               strcat(filePath,".txt");
               fptr1=fopen(filePath,"r");
               storeUsageDetails(fptr1);
               fclose(fptr1);
                  
                  
                  
               strcpy(filePath,tempfilepath);
               strcat(filePath,actualMachine);
               strcat(filePath," vmware-0");
               strcat(filePath,".txt");
               fptr1=fopen(filePath,"r");
               storeUsageDetails(fptr1);
               fclose(fptr1);
    
    
    
               strcpy(filePath,tempfilepath);
               strcat(filePath,actualMachine);
               strcat(filePath," vmware-1");
               strcat(filePath,".txt");
               fptr1=fopen(filePath,"r");
               storeUsageDetails(fptr1);
               fclose(fptr1);
    
               strcpy(filePath,tempfilepath);
               strcat(filePath,actualMachine);
               strcat(filePath," vmware-2");
               strcat(filePath,".txt");
               fptr1=fopen(filePath,"r");
               storeUsageDetails(fptr1);
               fclose(fptr1);
                       int f=0;
                           while(f<4)
                                    {
                                   finalMinutes[f]=countNoOfMinutes(&(arr[f].sd),&(arr[f].ed),&(arr[f].st),&(arr[f].et));
                                     f++;
                                     }
    
                      printf("<center><div id=chartContainer></div></ceactualMter>");
                      printf("<script type=text/javascript src=http://localhost:8080/SYSLOG/canvasjs.min.js></script>");
                      printf("<script>window.onload = function () {var chart = new CanvasJS.Chart(\"chartContainer\", {animationEnabled: true,title:{text: \"Usage Statistics\"},	axisX: {valueFormatString: \"DD MMM,YY\"	},	axisY: {		title: \"Usage Time (in min)\",		suffix: \" min\"	},	legend:{		cursor: \"pointer\",		fontSize: 16,		itemclick: toggleDataSeries	},	toolTip:{		shared: true	},	data: [");
    
                      printf("{name: \"%s\",type: \"line\",yValueFormatString: \"#0.## min\",showInLegend: true,dataPoints: [{ x: new Date(%d,%d,%d), y: %d },{ x: new Date(%d,%d,%d), y: %d },{ x: new Date(%d,%d,%d), y: %d },{ x: new Date(%d,%d,%d), y: %d }]}]});chart.render();function toggleDataSeries(e){if (typeof(e.dataSeries.visible) === \"undefined\" || e.dataSeries.visible) {e.dataSeries.visible = false;}else{e.dataSeries.visible = true;}chart.render();}}</script>",actualMachine,arr[3].sd.yy,arr[3].sd.mm-1,arr[3].sd.dd,finalMinutes[3],arr[2].sd.yy,arr[2].sd.mm-1,arr[2].sd.dd,finalMinutes[2],arr[1].sd.yy,arr[1].sd.mm-1,arr[1].sd.dd,finalMinutes[1],arr[0].sd.yy,arr[0].sd.mm-1,arr[0].sd.dd,finalMinutes[0]); 
                  
    
        printf("</div></body></html>");      
    return 0;
}