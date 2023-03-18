#include<iostream>
#include<string>
#include<vector>
#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sstream>
#include<algorithm>
#include<cctype>

//simplifying to write less code:
typedef std::vector<std::string> Vector;

//store the initial sentence entered by user:
std::string sentence;

//vector to store tokens in it:
Vector tokens;

std::stringstream ss;
std::string sStorage;

//flags to prevent race condition:
bool isDigit = false;
bool isAlpha = false;

//counter that counts over the elements stored in vector:
int i = 0;

//alpha function to catch alphabetic values:
void* alpha_function(void* type)
{
  //continue iteration until i is not equal to number of elements stored in the vector:
  while(i < tokens.size())
{
  char* message;
  message = (char*) type;

    std::string s = tokens[i];
    if(isalpha(s[0]))
    {
      isAlpha = true;
      isDigit = false;
    }else if(isdigit(s[0]))
    {
      isAlpha = false;
      isDigit = true;
    }

    if(isAlpha)
    {
        std::cout << "_____________________________________________________\n";
      std::cout << message <<":" << s << "\n";
      //once a token is determined as alphabetic value, we increment to the next element in the vector :
      i++;
    }
}

  return NULL;
}

void* numeric_function(void* type)
{
char* message;
message = (char*) type;

while(i < tokens.size())
{
  std::string s = tokens[i];
  if(isdigit(s[0]))
  {
    isDigit = true;
    isAlpha = false;
  }else if(isalpha(s[0]))
  {
    isDigit = false;
    isAlpha = true;
  }

  if(isDigit)
  {
      std::cout << "_____________________________________________________\n";
    std::cout << message <<":" << s << "\n";

    //once a token is determined as numeric value, we increment to the next element in vector:
    i++;
  }
}
  return NULL;
}


int main()
{
  std::cout << "_____________________________________________________\n";
  std::cout << "****Determine if tokens are numeric or alphabetic****\n";
  std::cout << "_____________________________________________________\n\n";
  std::cout << "Please enter a sentece: ";
  getline(std::cin, sentence);


//creating two identifier to pass to thread functions:
char* msg1 = "alpha";
char* msg2 = "numeric";

  //using stringstream to break up the sentence into tokens:
  ss << sentence;
      while(ss)
      {
            ss >> sStorage;
            //storing tokens into tokens vector:
            tokens.push_back(sStorage);
      }
      tokens.pop_back();

//pthread_identifiers;
  pthread_t alpha, numeric;

//creating two threads
  pthread_create(&alpha, NULL, alpha_function, (void*)msg1);
  pthread_create(&numeric, NULL, numeric_function, (void*)msg2);

//wating for threads to exit:
  pthread_join(alpha, NULL);
  pthread_join(numeric, NULL);

    std::cout << "______________________________________________________\n";
    std::cout << "*******************End of Program*****************\n";
    std::cout << "______________________________________________________\n";



  return 0;
}
