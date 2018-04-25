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

vector <string> args;
bool done = false; // TODO: If command execlp is done, and command is read, delete vector elements

int main(){
  while(true){ // program loop
    prompt(); // prompts the user 
   
    // takes in input and reads the whole line
    string input;
    getline(cin, input);
    istringstream iss(input);
    string word;
    int i = 0;
    
    while(iss >> word){ // error checking for more than 10 args
      if(i >= 10){
	error(1);
      }// if
      
      // handles exiting
      if(word.compare("exit") == 0 || word.compare("quit") == 0){
	return EXIT_SUCCESS;
      }

      pretendMain(word); // calls the shell main to put every word into a vector
      i++; // incraments each args
    }// while

    // checks for io redirection input. If not io, exec is called immediatley
    if(io()){

    }else{
      exec();
    }

    if(done){ // handles removing vector to start over a new command string
      breakDown();
    }// breakdown
  }// shell while loop
}// main

bool io(){
  bool returnVal = true;

  if(args.at(1).compare("<") == 0){
    cout << "<" << endl;
   }else if(args.at(1).compare(">") == 0){
    cout << ">" << endl;
   }else if(args.at(1).compare(">>") == 0){
    cout << ">>" << endl;
  }else{
    returnVal = false;
  }
  return returnVal;
}// io redirection method

void exec(){

  if(args.size() == 0){
    return;
  }// if there is nothing in trhe vector, run loop again
 
 for(uint i = 0; i < args.size(); i++){
    if(args.at(i).empty()){
      error(2); // handles if it is trying to access a null element
    }     
  }// for
  
 // TODO : exec stuff
  bool finished = false;
  string arg1 = "/bin/";
  arg1 += args.at(0);

  const char * temp = arg1.c_str();
  const char * flags = args.at(1).c_str();
 
  // forks 
  int pid = fork();
  
  if(pid == 0){
    // child
    cout << "in child" << endl;
    execl(temp, temp, flags, (char*)0); // handles exec   
  }else{
    // parent
    wait(nullptr);
    finished = true;
  }
  if(finished){ // if  command is finished, run a new iteration
    done = true;
  }
}// exec

void breakDown(){
  args.clear(); // erases all elements after command has been executed
  done = false;
}// shell

void pretendMain(string s){
  args.push_back(s); // loads vector up with each word in commmand stream
}// pretend main

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
