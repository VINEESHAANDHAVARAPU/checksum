#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include <unistd.h>
#include<stdlib.h>
#define SERV_TCP_PORT 8080
#define SA struct sockaddr
int main()
{
int sockfd,newsockfd,clength;
struct sockaddr_in serv_addr,cli_addr;
sockfd=socket(AF_INET,SOCK_STREAM,0);

if (sockfd == -1) {
printf("socket creation failed...\n");
exit(0);
}
else
printf("Socket successfully created..\n");

serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=INADDR_ANY;
serv_addr.sin_port=htons(SERV_TCP_PORT);

if ((bind(sockfd, (SA*)&serv_addr, sizeof(serv_addr))) != 0) {
printf("socket bind failed...\n");
exit(0);
}
else
printf("Socket successfully binded..\n");

if ((listen(sockfd, 5)) != 0) {
printf("Listen failed...\n");
exit(0);
}
else
printf("Server listening..\n");

clength=sizeof(cli_addr);
newsockfd=accept(sockfd, (SA*)&cli_addr, &clength);

if (newsockfd< 0) {
printf("server acccept failed...\n");
exit(0);
}
else
printf("server acccept the client...\n");

int n[1000],i,j,a[500],b[500],d[500],r[500],s1=0,c=0,s;
read(newsockfd,n,sizeof(n));
/*for(i=0;i<=n[0];i++){
printf("%ld",n[i]);
}
*/
s=n[0]/3;
j=0;
for(i=1;i<=s;i++)
{
a[j]=n[i];
j+=1;
}
j=0;
for(i=s+1;i<=2*s;i++)
{
b[j]=n[i];
j+=1;
}

j=0;
for(i=2*s+1;i<=3*s;i++)
{
d[j]=n[i];
j+=1;
}

/*
for(i=0;i<s;i++){
printf("%ld",a[i]);
}
for(i=0;i<s;i++){
printf("%ld",b[i]);
}
for(i=0;i<s;i++){
printf("%ld",d[i]);
}
*/


i=s-1;c=0;
while(i>=0){
if(a[i]==0 && b[i]==0 && d[i]==0 && c==0){
r[i]=0;c=0;
}
else if(a[i]==0 && b[i]==0 && d[i]==0 && c==1||a[i]==0 && b[i]==0 && d[i]==1 && c==0||a[i]==0 && b[i]==1 && d[i]==0 && c==0||a[i]==1 && b[i]==0 && d[i]==0 && c==0){
r[i]=1;c=0;
}
else if(a[i]==0 && b[i]==0 && d[i]==1 && c==1||a[i]==0 && b[i]==1 && d[i]==0 && c==1||a[i]==0 && b[i]==1 && d[i]==1 && c==0||a[i]==1 && b[i]==0 && d[i]==0 && c==1||a[i]==1 && b[i]==0 && d[i]==1 && c==0||a[i]==1 && b[i]==1 && d[i]==0 && c==0){
r[i]=0;c=1;
}
else if(a[i]==0 && b[i]==1 && d[i]==1 && c==1||a[i]==1 && b[i]==0 && d[i]==1 && c==1||a[i]==1 && b[i]==1 && d[i]==0 && c==1||a[i]==1 && b[i]==1 && d[i]==1 && c==0){
r[i]=1;c=1;
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
c=d;
}
for(i=0;i<s;i++){
r[i]=r2[i];
}
}

for(i=0;i<s;i++){
if(r[i]==1){
r[i]=0;
}
else{
r[i]=1;
}
}

/*
for(i=0;i<s;i++){
printf("%ld",r[i]);
}*/

for(i=0;i<s;i++)
{
s1+=r[i];
}

printf("The resultant value is:");
for(i=0;i<s;i++)
{
printf("%d",r[i]);
}

if(s1==0){
printf("\ndata received is not corrupted\n");
}
else{
printf("\ndata received is corrupted\n");
}

close(sockfd);
return 0;
}
