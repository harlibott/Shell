#include<iostream>
#include<unistd.h>
#include<string>
#include<string.h>
#include<sstream>
#include<vector>
#include"shell.h"

using namespace std;

vector <string> args;
bool done = false; // TODO: If command execlp is done, and command is read, delete vector elements

int main(){
  while(true){
    prompt();
    //    exec();
    string input;
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
      i++;
    }// while
    
  }// shell while loop
}// main

void pretendMain(string s){
  args.push_back(s);

}// pretend main

void in(){

}// in

void exec(){
  //execl(args.at(0),args.at(0), args.at(1));  
  execl("/bin/echo", "/bin/echo", "hello");
  
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

void error(int e){


}// error checking method
