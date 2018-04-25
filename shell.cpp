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
const char * conv;
int main(){
  while(true){
    prompt();
  
    //  string input = "Hello, World";

    string input; 
    getline(cin, input);

    conv = input.c_str();

    cout << conv;
    exec();
    /*    string input;
    getline(cin, input);
    istringstream iss(input);
    string word;
    int i = 0;
    
    while(iss >> word){
      if(i >= 10){
	error(1);
      }// if
      if(word.compare("exit") == 0){
	return EXIT_SUCCESS;
      }
      pretendMain(word);
      exec();
      i++;
    }// while
    */

  }// shell while loop
    
}// main

void pretendMain(string s){
  args.push_back(s);

}// pretend main

void in(){

}// in

void exec(){

  int pid = fork();
  if(pid == 0){
    // child
    cout << "in child" << endl;
    execl("/bin/ls", "/bin/ls", "-a", "-l", (char*)0);   
  }else{
    // parent
    wait(nullptr);
    //    wait(nullptr);
    // cout << "Parent done" << endl;
  }

}// exec

void prompt(){
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

int error(int e){

  switch(e){

  case 1:
    cout << "\nYou cannot have more than 10 commands..." << endl;
    return 1;
    break;

  default: 
    cout << "\nThere was an error..." << endl;
    return 1;
  }
}// error checking method
