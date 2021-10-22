#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<stdlib.h>
#define SERV_TCP_PORT 8080
#define SA struct sockaddr
int main(){
int sockfd,connfd;
struct sockaddr_in serv_addr;
sockfd=socket(AF_INET,SOCK_STREAM,0);
if (sockfd == -1) 
{
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created.....\n");

bzero(&serv_addr, sizeof(serv_addr));
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
serv_addr.sin_port=htons(SERV_TCP_PORT);

if (connect(sockfd, (SA*)&serv_addr, sizeof(serv_addr)) != 0)
{
printf("connection with the server failed......\n");
exit(0);
}
else
printf("connected to the server..\n");

int n[1000],a[1000],b[1000],r[1000],s,i,j,size,c;
printf("\nEnter size of the data:\n");
scanf("%d",&size);
printf("\nEnter data:\n");
for(i=0;i<size;i++){
scanf("%1d",&n[i]);
}
s=size/2;
for(i=0;i<s;i++){
a[i]=n[i];
}
j=0;
for(i=s;i<size;i++){
b[j]=n[i];
j++;
}

i=s-1;c=0;
while(i>=0){
if(a[i]==0 && b[i]==0 && c==0){
r[i]=0;c=0;
}
else if(a[i]==1 && b[i]==1 && c==1){
r[i]=1;c=1;
}
else if(a[i]==0 && b[i]==0 && c==1 ||a[i]==0 && b[i]==1 && c==0 ||a[i]==1 && b[i]==0 && c==0){
r[i]=1;c=0;
}
else{
r[i]=0;c=1;
}
i--;
}

if(c==1){
int r2[s];
while(c==1){
i=s-1;
int d=0;
while(i>=0){
if(r[i]==0 && d==0 && c==1){
r2[i]=1;d=0;c=0;
}
else if(r[i]==1 && d==0 && c==1){
r2[i]=0;d=1;c=0;
}
else if(r[i]==0 && d==1 && c==0 ||r[i]==1 && d==0 && c==0){
r2[i]=1;d=0;
}
else if(r[i]==0 && d==0 && c==0){
r2[i]=0;d=0;
}
else{
r2[i]=0;d=1;
}
i--;
}
}
for(i=0;i<s;i++){
r[i]=r2[i];
}
}

printf("the result is:");
a[0]=size+s;
j=1;
for(i=0;i<s;i++){
if(r[i]==1){
a[j]=0;
}
else{
a[j]=1;
j++;
}
//printf("%ld",r[i]);
}
j=0;
for(i=s+1;i<=3*s;i++){
a[i]=n[j];
j=j+1;
}



for(i=0;i<=3*s;i++){
printf("%d",a[i]);
}
printf("\n");
/*if(a[1]==0){
a[1]=1;
}
else{
a[1]=0;
}
*/
write(sockfd,a,sizeof(a));

close(sockfd);
return 0;
}
