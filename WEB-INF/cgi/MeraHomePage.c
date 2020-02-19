#include <stdio.h>
#include<string.h>
#include<dirent.h>
decode(char*src,char*last,char*uname,char*pass)
    {
     int a;
       while(src!=last+1)
          {   
             if(*src=='+')
                 {
                    *uname=' ';  
                  } 
            else if(*src=='%')
                 {    
                     sscanf(src+1,"%2x",&a);
                     *uname=a;
                      src=src+2;
                  }
            else if(*src=='&')
                {
                   break;
                }
               else
                {
                  *uname=*src;
                }
              src++;
              uname++;
           }
      *uname='\0';
       src++;
       while(src!=last+1)
          {   
             if(*src=='+')
                 {
                    *pass=' ';  
                  } 
            else if(*src=='%')
                 {    
                     sscanf(src+1,"%2x",&a);
                     *pass=a;
                      src=src+2;
                  }
            else if(*src=='&')
                {
                   break;
                }
               else
                {
                  *pass=*src;
                }
              src++;
              pass++;
           }
         *pass='\0';
      
    } 
int main()
{
  int totbyte,a,b;
  char*totalbyte;
  char inputstring[50];
  char uname[50];
    char machine[20];
  char pass[50];
  printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
  totalbyte=getenv("CONTENT_LENGTH");
     totbyte=atoi(totalbyte);
        fgets(inputstring,totbyte+1,stdin);
        decode(inputstring,inputstring+totbyte-1,uname,pass);        
          int p=(sscanf(uname,"uname=%s",uname)&&sscanf(pass,"pass=%s",pass));
        if(p!=1)
           {
             printf("<br>fields can not be empty "); 
           }
       else if(strcmp(uname,"mrkamaldua")==0&&strcmp(pass,"kamaldua")==0)
              {
             printf(" <html><head><meta name=viewport content=width=device-width, initial-scale=1><style>body {font-family: Lato, sans-serif;}.sidenav {height: 100%%;width: 350px;position: fixed;z-index: 1;top: 0;left: 0;background-color: #111;overflow-x: hidden;padding-top:20px;}.sidenav a {padding: 6px 8px 6px 16px;text-decoration: none;font-size: 25px;color: #818181;display: block;}.sidenav a:hover {color: #f1f1f1;}.main {margin-left: 350px; font-size: 28px; padding: 0px 10px;}@media screen and (max-height: 450px) {.sidenav {padding-top: 15px;}.sidenav a {font-size: 18px;}}li {color: cyan;}</style></head>");
            printf("<body>");
           printf("<div class=sidenav>");
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
              printf("<li><a href=Vm.cgi?machine=%s>%s</a></li>",machine,de->d_name);
              }
           }
           closedir(dr);  
           printf("</ul></div>");
           printf("<div class=main><center><h2>Welcome to your Virtual Machine<br><br><br>Choose your Virtual Machines from left side</h2></center></div></body></html>");
           
              }
         else
           {
              printf("<br> you have entered incorrect password and details");
              printf("<br><a href=http://localhost:8080/SYSLOG> login again</a>");
           }
return 0;
}