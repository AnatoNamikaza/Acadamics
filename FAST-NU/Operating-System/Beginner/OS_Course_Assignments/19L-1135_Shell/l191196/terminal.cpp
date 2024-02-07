// g++ terminal.cpp -o t; ./t
#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <string>
#include<sstream>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
using namespace std;

char *current_dir = new char [100];

void get_all_path(string pathenv, char *pathlist[]);
int get_no_of_paths(string pathenv);
string concate(string str1,string str2);
string look_up_command(char *paths[],int size,string current_dir,string command);
bool contains(string command, char x);
string drop(string command,char x);
bool is_shell_command(string command);
string read_command();
void output_redirection();
void split(string command, char x, string &left, string &right);
bool has_pipe(string command);
void remove_trailing_spaces(string &command);
string get_first_word(string command);
string extract_path(string command);
void handle_redirection(string left_command,string file_name,char action,int counter);
// whether to read from file or to write to a file

struct command_t{
  char *name;
  int argc;
  char *argv[];
};

void parse_command(command_t *argv,string command);
int execute_command(string command, bool pipe_exits,int cmd_number);
int var_pipe[2];
int fd[2];
int fd2[2];
int std_output;
int main(){
  pipe(var_pipe); // this pipe will share local variabl etc
  getcwd(current_dir,100);

    
  string command;
  while(command != "exit"){
    
    command = read_command();

    string first_word=get_first_word(command);
    if(first_word == "cd"){
      // cd is special only which parent executes
      // to keep the path updated
      string cd_path = extract_path(command);
      chdir(cd_path.c_str());
      getcwd(current_dir,100);
    }
    else{
      pipe(fd);
      pipe(fd2);
      int init_pipe_val=0; // output is not piped
      write(var_pipe[1],&init_pipe_val,sizeof(int));

      int cmd_counter=0;
      string left; //command on left side of pipe
      while(has_pipe(command)){
	split(command,'|',left,command); //reduce command
	//cout << "reduced command <" << command << ">\n";
	if(contains(left,'<')){
	  // e.g wc -l < file.txt
	  string left_command;
	  string file_name;
	  split(left,'<',left_command,file_name);
	  handle_redirection(left_command,file_name,'r',cmd_counter); // read flag
	}
	else if(contains(left,'>')){
	  // e.g echo hello > file.txt
	  string left_command;
	  string file_name;
	  split(left,'>',left_command,file_name);
	  cout << left_command << endl;
	  handle_redirection(left_command,file_name,'w',cmd_counter); // write flage
	}
	else{
	  // simple command without < and > 
	  // ls|wc -l
	execute_command(left,true,cmd_counter);
	}
	if(cmd_counter %2 ==0){
	  close(fd[1]); //-================
	  pipe(fd2);
	}
	if(cmd_counter == 1) {
	  close(fd2[1]);

	  // close(fd[0]);
	  // close(fd[1]);

	  pipe(fd);
	}
	cmd_counter++;
      }
      //wait(NULL);
      if(command !=""){      
	if(contains(command,'<')){
	  // e.g wc -l < file.txt
	  string left_command;
	  string file_name;
	  split(command,'<',left_command,file_name);
	  handle_redirection(left_command,file_name,'r',cmd_counter); // read flag
	}
	else if(contains(command,'>')){
	  // e.g echo hello > file.txt
	  string left_command;
	  string file_name;
	  split(command,'>',left_command,file_name);
	  //cout << left_command << endl;
	  handle_redirection(left_command,file_name,'w',cmd_counter); // write flage
	}
	else{
	  execute_command(command,false,cmd_counter);
	}
	  //cout << "exited normally\n";
	close(fd[1]);
	close(fd[0]);
	close(fd2[0]);
	close(fd2[1]);

	//cout << "exited normally\n";
      }
    
    }    
  }
  //wait(NULL);  
  return 0;
}



void get_all_path(string pathenv, char*pathlist[]){
  //transform : into space
  int i=0;
  int path_counter =0;
  while(pathenv[i]){
    if(pathenv[i] == ':') pathenv[i] = ' ';
    i++;
  }
  istringstream iss(pathenv);
  int index=0;
  do{
    char *buffer = new char[50];
    iss >> buffer;
    pathlist[index++] = buffer;
  }
  while(iss);
}

int get_no_of_paths(string pathenv){
  //transform : into space
  int i=0;
  int path_counter =0;
  while(pathenv[i]){
    if(pathenv[i] == ':') path_counter++;
    i++;
  }
  return path_counter+1;
}

string concate(string str1,string str2){
  string result = str1+str2;
  return result;
}

string look_up_command(char *paths[],int size, string current_dir,string command){
  // its looks 'command e.g gcc' in all 'paths' e.g ["/usr/bin",...]
  // of 'size'
  //   it returns the complete path of command
  // ============== first of all look in relative path
  if(contains(command,'/')){
    //it is externel command with reletive or absolute path
    if(command[0] == '/'){
      // if first char is '/' then no need to make file path
      // it will be users responsibility to provide full path
      if(!access(command.c_str(),F_OK)) return command;
    }
    else{
      // it is relative path
      // first word of command
      istringstream cmd(command);
      cmd >> command;

      if(command[0] == '.') command = drop(command,'.');
      string file = current_dir + command;
      //cout << file << endl;
      if(!access(file.c_str(),F_OK)) return file;
      else{return "";}

      
    }
  }
  else{
    //first word of command
    istringstream cmd(command);
    cmd >> command;
      
    command = "/"+command;
    for(int i=0; i< size; i++) {
      string file = concate(string(paths[i]),command);      
      if(!access(file.c_str(),F_OK)) {
	//cout << "found in bin\n";
	return file;
      }      
    }
  }
  return "";
}

bool contains(string command,char x){
  for(int i=0; i< command.length(); i++){
    if(command[i] == x) return true;
  }
  return false;
}

string drop(string command,char x){
  //it removes the unwanted char from a string 
  string result;
  for(int i=1; i< command.length(); i++){
    result=result+command[i];
  }
  return result;
}

void parse_command(command_t *argv,string command){
  istringstream iss(command);
  string cmd_name;
  iss >> cmd_name;
  argv->name = new char[cmd_name.length()+1];
  strcpy(argv->name,cmd_name.c_str());

  int i=0;
  int arg_counter =0;
  while(command[i]){
    if(command[i] == ' ') arg_counter++;
    i++;
  }
  arg_counter += 1;
  argv->argc = arg_counter;
  istringstream rss(command); // reset head
  
  //argv->argv = new char*[arg_counter];
  for(int i=0; i< arg_counter; i++){
    string arg;
    rss >> arg;
    argv->argv[i] = new char[arg.length()+1];
    strcpy(argv->argv[i],arg.c_str());
  }
  argv->argv[arg_counter] = NULL;
}

bool is_shell_command(string command){
  istringstream iss(command);
  string name;
  iss >> name;
  string shell_commands[] = {"cd","help"};
  for(int i=0; i< 2; i++){
    for(int i=0; i< sizeof(shell_commands)/sizeof(string); i++){
      //    cout << "-----------" << shell_commands[i] << endl;
      if(name == shell_commands[i]) return true;
    
    }
  }
  return false;    
}

string read_command(){
  string command;
  char hostname[50];
  gethostname(hostname,50);  
  cout << getenv("USER") << "@" << hostname << ":" << current_dir << "$ ";
  getline(cin, command);
  return command;
  
}

void split(string command, char x, string &left, string &right){
  int index=0;
  left="";
  right="";
  while(index < command.length() && command[index] != x){
    left = left+command[index];
    index++;
  }
  left=left+'\0';

  index=index+1;
  while(index < command.length()){
    right = right+command[index];
    index++;
  }
  right=right+'\0';
}


int execute_command(string command, bool pipe_exits,int cmd_number){
  int status;
  remove_trailing_spaces(command);
  int npaths = get_no_of_paths(getenv("PATH"));
  char *paths[npaths];
  get_all_path(getenv("PATH"),paths);
  //string command;
  getcwd(current_dir,100);

  int pid = fork();
  if(pid == -1){cout << "child process was not cretaed \n";}
  else if(pid ==0){
    // child process created successfully
    string file = look_up_command(paths,npaths,current_dir,command);

    //cout << file << "-----------\n";
    if(file != "" || !is_shell_command(command)){      
      //cout << "executed by execv\n";
      command_t *command_set = new command_t;
      parse_command(command_set,command);
      int piped;
      read(var_pipe[0],&piped,sizeof(int));
      if(pipe_exits == false && piped == 0){
      	// no need to modify either input or output redirection
      	// command is either single
      	//cout << "no pipe\n";
      }
	
      else if(pipe_exits && piped == 1 && cmd_number%2==0 && cmd_number > 0) {	
      	// redirect input and output
      	// may be middle command	
      	// cout << "setting out redirection to pipe fd2\n";
      	// cout << "setting in redirection from pipe fd\n";
      	piped=1;
      	write(var_pipe[1], &piped,sizeof(int));
      	//close(var_pipe[0]);
      	// above line signals next process that previous output was piped
      	// hence read from pipe
      	dup2(fd2[0],0);
      	// and further more output of this process should also be piped
      	//dup2(fd[1],1); //============
	dup2(fd[1],1);
	
      }
      else if(pipe_exits && piped == 1 && cmd_number%2==1 && cmd_number > 0) {
      	// redirect input and output
      	// may be middle command	
      	// cout << "setting out redirection to pipe fd2 mid case\n";
      	// cout << "setting in redirection from pipe fd mid case\n";
      	piped=1;
      	write(var_pipe[1], &piped,sizeof(int));
      	//close(var_pipe[0]);
      	// above line signals next process that previous output was piped
      	// hence read from pipe
      	dup2(fd[0],0); //============
      	// and further more output of this process should also be piped
      	//dup2(fd[1],1); //============
	dup2(fd2[1],1);
	
      }
      
      //parse_command(command_set,command);
      else if(pipe_exits == true && piped == 0 && cmd_number==0) {
      	// redirect output only
      	// may first command
      	//cout << "setting out redirection to pipe fd\n";
      	//*piped=1;
      	piped=1;
      	write(var_pipe[1], &piped,sizeof(int));
      	// output of this process should  be piped
      	dup2(fd[1],1);
      }
      else if(pipe_exits == false && piped==1 && cmd_number%2 ==0){
      	//cout << "redirect input from pipe only many pipe last case\n";
      	// redirect input only
      	// may last command	
	//============
	close(fd2[1]);
	//============
      	dup2(fd2[0],0);
	//close(fd[1]); //+===========
	// close(fd[0]);
	// close(fd2[1]);
	// close(fd2[0]);      	//close(fd[0]);
      	//cout << "redirection from pipe has been done\n";
      }

      else if(pipe_exits == false && piped==1 && cmd_number%2==1){
      	//cout << "redirect input from pipe last case\n";
      	// redirect input only
      	// may last command	
	close(fd[1]);
      	dup2(fd[0],0);
      	//cout << "redirection from pipe has been done\n";
      }

      else{
	cout << "this case is not handled \n";
      }

      //cout << "----- <" << file << " " << command_set->argv[1] << " >---------\n";
      execv(file.c_str(), command_set->argv);
      exit(0);
    }
  }
  else{
    //parent is waiting for child to finish
    if(command[command.length()-1] != '&'){
      waitpid(pid,&status,0);}
    else{
      cout << "child with pid = " << pid << " is running in background\n";
    }
  }
}

bool has_pipe(string command){
  return(contains(command,'|'));
}

void remove_trailing_spaces(string &command){
  // remove spaces from front
  string refined=""; // no spaces at frong
  int index=0;
  while(command[index] == ' ') index++;

  int last_index=index; // from where trailing spaces may start
  int start_index=index;
  while(index < command.length() ){
    if(command[index] != ' ' && command[index] != '\0') last_index = index;    
    refined = refined+command[index];
    index++;
  }
  // refined may contain spaces at the end
  string pure="";
  for(int i=0; i <=last_index-start_index; i++) pure+=refined[i];
  pure[last_index+1] = '\0';
  //cout << "pure <" << pure << ">\n";
  command=pure;
  //cout << start_index << " " << last_index << endl;
}

string get_first_word(string command){
  string first;
  istringstream cmd(command);
  cmd >> first;
  return first;
}

string extract_path(string command){
  string second;
  istringstream cmd(command);
  cmd >> second;
  cmd >> second;
  return second;
}

void handle_redirection(string command,string file_name,char action,int cmd_counter){
  int status;
  remove_trailing_spaces(command);
  remove_trailing_spaces(file_name);
  int pid=fork();
  if(pid==0 && (action == 'w' || action == 'r')){
    remove_trailing_spaces(command);
    int npaths = get_no_of_paths(getenv("PATH"));
    char *paths[npaths];
    get_all_path(getenv("PATH"),paths);
    //string command;
    getcwd(current_dir,100);

    string file = look_up_command(paths,npaths,current_dir,command);

    //cout << file << "-----------\n";
    if(file != "" || !is_shell_command(command)){      
      //cout << "executed by execv\n";
      command_t *command_set = new command_t;
      parse_command(command_set,command);
      //---------------------------
      if(action == 'r'){
	//open file
	// set redirection
	// execute execv
	int in = open(file_name.c_str(), O_RDONLY);
	dup2(in, 0);
	close(in);
      }
      else if(action == 'w'){
          int out = open(file_name.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	//===============
	if(cmd_counter %2 == 1)
	  dup2(fd[0],0);
	else{
	  dup2(fd2[0],0);
	}
	//===============
	dup2(out,1);
	close(out);
      }
      else{
	cout << "wrong flag\n";
      }
      //---------------------------
      execv(file.c_str(), command_set->argv);
      exit(0);
    }
  
  }
  else{
    if(command[command.length()-1] != '&')
      waitpid(pid,&status,0);
    else{
      cout << "child with pid = " << pid << " is running in background\n";
    }
  }
}
