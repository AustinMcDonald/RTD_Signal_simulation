// g++ -std=c++11 readtxt.cc 
// reading a text file
#include <iostream>
#include <fstream>
//#include <string>
//#include <stdlib.h>
#include <vector>

std::vector<double> convertStringVectortoDoubleVector(const std::vector<std::string>& stringVector)
{
  std::vector<double> doubleVector(stringVector.size());
  std::transform(stringVector.begin(), stringVector.end(), doubleVector.begin(), [](const std::string& val)
  {
    return std::stod(val);
  });
return doubleVector;
}


void DataFileParser2(std::string FILE, std::vector<std::vector<double>>& RawDataVector, std::vector<int>& EventLengths)
{
  //std::vector<std::vector<double>> RawDataVector;
  std::ifstream file(FILE);
  //std::vector<int> EventLengths;
  EventLengths.push_back(0);
  int count = 0;
  int runner = 0;

  while (!file.eof()) 
  {    
    std::vector<std::string> tmpVec;
    std::vector<double> tmpVecD;
    std::string tmpString;

    for (int j = 0; j < 5; j++)
    {
      file  >> tmpString;
      if(tmpString.empty())
      {
        EventLengths.push_back(runner);
        goto endloop;
      }
      tmpVec.push_back(tmpString);
    }
    tmpVecD = convertStringVectortoDoubleVector(tmpVec);
    if (count == tmpVecD[0]){runner+=1;}
    else{count+=1;  EventLengths.push_back(runner); runner+=1;}

    RawDataVector.push_back(tmpVecD);
  }
  endloop:
  return ;
  //return RawDataVector;
}

std::vector<std::vector<double>> GetEventVector(int Event, std::vector<int> EventLengths, std::vector<std::vector<double>> data)
{
  std::vector<std::vector<double>> event;
  int start = EventLengths[Event];
  int end   = EventLengths[Event+1];

  for (int i = start; i < end; i++) 
  {
    std::vector<double> tmpVec;
    for (int j = 1; j < data[i].size(); j++)
    {
      tmpVec.push_back(data[i][j]);
    }
    event.push_back(tmpVec);
  }
  return event;
}

int main ()
{
  
  std::vector<std::vector<double>> RawDataVector2;
  std::vector<int> EventLengths2;
  DataFileParser2("test.txt", RawDataVector2, EventLengths2);

  int Event = 5;

  std::vector<std::vector<double>> eventt2;
  eventt2 =  GetEventVector(Event ,  EventLengths2,  RawDataVector2);

  std::cout << "test" << std::endl;
  for (int i = 0; i < eventt2.size(); i++) 
  { 
    for (int j = 0; j < eventt2[i].size(); j++)
    {
      std::cout << eventt2[i][j]  << " ";   
    }
    std::cout << std::endl; 
    }
  std::cout << "test over" << std::endl;
  std::cout << "\n" << std::endl;

}