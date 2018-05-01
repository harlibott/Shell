#include<iostream>
#include<unistd.h>
#include<string>
#include<string.h>
#include<sstream>
#include<vector>
#include<cstdio>
#include<sys/types.h>
#include<sys/wait.h>
#include<cstdlib>
#include"shell.h"

using namespace std;

int main(){


  while(true){ // program loop
    prompt(); // prompts the user 
  
    char str[1042];
    cin.getline(str, 1042);
    int fileIn, fileOut;
    char * tokes [1042];
    char * token;
    int i = 0;
    token = strtok(str, " ");

    if(strcmp(token, "exit") == 0 || strcmp(token, "quit") == 0){
	return EXIT_SUCCESS;
      }
      if(strcmp(token, "<") == 0 || strcmp(token, ">") == 0 || strcmp(token, ">>") == 0){
	io(token);
      }
      //potential strcmp or !strcmp mistake above

      while(token != NULL){
	tokes[i] = token;
	token = strtok(NULL, " ");
	i++;
	
	int pid = fork();
	if(pid == 0){
	  if(execvp(tokes[0], tokes) < 0){
	    continue;
	  }
	}else{
	  wait(nullptr);
	}
      }// while   
  }// shell while loop
}// main

void io(char * token){

  if(!strcmp(token, "<")){

    fileIn = open(token+1, O_RDONLY);
    dup2(fileIn, 0);
    close(fileIn);
    //break;
 
  }else if(!strcmp(token, ">")){

    fileOut = open(token+1, O_WRONLY);
    dup2(fileOut, 1);
    close(fileOut);
    //break;

  }else if(!strcmp(token, ">>")){

  }  
}// io redirection method

/*
  int f = open(argv[1], O_RDONLY);
  int copy = dup(0);

  if (f<0){
  cout << "\nError opening file\n" << endl;
  return 1;
  }
  //check for proper usage, expecting one argument -- file to read from
 
  read();
  // redirect standard input from file
 
  dup2(f,0);
  read();
  close(f);
  // revert back from actual standard input

  dup2(copy,0);
  read();
}
 */


void prompt(){
  // gets the cwd and prints it out as a prompt to the screen
  string prompt = "1730sh:";
  char buf[4096];
  getcwd(buf, 4096);

  string current = buf;
  const char * home;
  home = getenv("HOME");

  int length = strlen(home);
  string subs = current.substr(0, length);
  const char * comp = subs.c_str();

  if(strcmp(comp, home) == 0){
    prompt += "~";
    prompt += current.substr(length);
  }else{
    prompt += current;
  }
  prompt += "$ ";
  cout << prompt;
}// prompt

void error(int e){
  switch(e){

  case 1:
    cout << "\nYou cannot have more than 10 commands...\nEXIT FAILURE\n" << endl;
    exit(EXIT_FAILURE);

  case 2:
    cout << "\nInvalid arguments...\nEXIT FAILURE\n" << endl;
    exit(EXIT_FAILURE);
   
  default: 
    cout << "\nThere was an error...\nEXIT FAILURE\n" << endl;
    exit(EXIT_FAILURE);
  }
}// error checking method
