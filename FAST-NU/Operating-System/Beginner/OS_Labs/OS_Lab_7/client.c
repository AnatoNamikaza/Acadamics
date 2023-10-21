#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

int populationSize; // total population of a particular city

int main(int argc, char const *argv[])
{
  int sock = 0;
  struct sockaddr_in serv_addr;
  char buffer[1024] = {0};
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      printf("\n Socket creation error \n");
      return -1;
    }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
	
  // Convert IPv4 and IPv6 addresses from text to binary form
  if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
      printf("\nInvalid address/ Address not supported \n");
      return -1;
    }

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
      printf("\nConnection Failed \n");
      return -1;
    }

  printf("Client has started\n");
  
  int areaID;
  printf("Dial your area id: ");
  scanf("%d",&areaID);
  
  write(sock,&areaID ,sizeof(int));
  read( sock , &populationSize,sizeof(int));

  if(populationSize != 0){
    for(int i=0; i< populationSize; i++){
      int vote;
      printf("%d/%d is casting vote: ",i+1,populationSize);
      printf("1: Green 2: Blue: ");
      scanf("%d",&vote);
      write(sock,&vote ,sizeof(int));
    }
  }
  else{
    printf("Election is already taking there\n");
  }
  return 0;
}
 
