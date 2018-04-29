#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;
string score[5];

bool checkCondition(double a,double b)
{
    return a>b;
}

void sortTheThing(){

    sort(real_scores,real_scores+6,checkCondition);

    for(int i=0;i<5;i++)
      {
          std::cout<<real_scores[i]<<std::endl;
          stringstream sd;
          sd<<real_scores[i];
          score[i]=sd.str();
      }
}


void saveScores()
{

  sortTheThing();

  ofstream myfile("example.txt",ios::out);

  for(int i=0;i<5;i++)
  {
      myfile <<score[i]<<"\n";
  }
  myfile.close();
}




void getTopScores()
{
      string line;
      int counter=0;

      ifstream myfile ("example.txt");
      if (myfile.is_open())
      {
        while ( getline (myfile,line) )
        {
            stringstream ss;
            double score;
            ss<<line;
            ss>>real_scores[counter];

            counter++;
        }
        myfile.close();
      }

      sort(real_scores,real_scores+counter,checkCondition);

      for(int i=0;i<5;i++)
      {
          stringstream sd;
          sd<<real_scores[i];
          score[i]=sd.str();
      }
}
