#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

void initElectionData();
void *HandleVotes(void *ptr);
int getPopulation(int id);
void announceResult();

int greenVotes = 0;
int blueVotes = 0;
int done[5];
int completedRegion;
int began[5];
int totalBegan;
int population[5];

void initElectionData(){
  for(int i=0; i< 5; i++){
    population[i] = (i+1)*5;
  }
}

int getPopulation(int id){
    for(int i=0; i< 5; i++){
      if(began[i] == id || done[i] == id) return 0;
    }  
      began[id-1] = id;
      return population[id-1];
    return 0;
  }
 
void announceResult(){
      printf("<<<------------------------>>>\n");
      printf("Election Result of Blue and Green party\n");
      printf("Total Votes to Green party: %d\n", greenVotes);
      printf("Total Votes to Blue party: %d\n", blueVotes);

      if(greenVotes > blueVotes){
	printf("winner party is Green\n");
      }
      else if(greenVotes < blueVotes){
	printf("winner party is Blue\n");
      }
      else{
	printf("Election Draw\n");
      }
  }

int main(int argc, char const *argv[])  
{
  initElectionData();
  int server_fd, new_socket, valread;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
  char buffer[1024] = {0};
  // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
      perror("socket failed");
      exit(EXIT_FAILURE);
    }
	
  // Forcefully attaching socket to the port 8080
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
    {
      perror("setsockopt");
      exit(EXIT_FAILURE);
    }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons( PORT );
	
  // Forcefully attaching socket to the port 8080
  if (bind(server_fd, (struct sockaddr *)&address,
	   sizeof(address))<0)
    {
      perror("bind failed");
      exit(EXIT_FAILURE);
    }
  if (listen(server_fd, 3) < 0)
    {
      perror("listen");
      exit(EXIT_FAILURE);
    }

  pthread_t *threads[5];
  int index=0;
  while(index < 5){
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0)
      {
	perror("accept");
	exit(EXIT_FAILURE);
      }
    int * pollingStation = (int *)malloc(sizeof(int));
    * pollingStation = new_socket;
    pthread_t *t = (pthread_t *)malloc(sizeof(pthread_t));
    threads[index++] = t;
    pthread_create(t,NULL,&HandleVotes, pollingStation);  
  }
  for(int i=0; i< index; i++){
    pthread_join(*threads[i],NULL);
  }
   announceResult();  
  return 0;
}

void *HandleVotes(void *_pollings){
  int pollingStation = *(int *)_pollings;
  int areaID;
  read( pollingStation , &areaID, sizeof(int)); 
  int psize =  getPopulation(areaID);
  write( pollingStation , &psize, sizeof(int));
  if(psize > 0){
    for(int i=0; i< psize; i++){
      int vote;
      read( pollingStation , &vote, sizeof(int));
      if(vote == 1) greenVotes++;
      else
	blueVotes++;
    }
  }
  close( pollingStation);
  return NULL;
}
