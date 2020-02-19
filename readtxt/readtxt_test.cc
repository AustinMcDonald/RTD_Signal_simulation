// g++ -std=c++11 readtxt.cc 
// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
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

  //int Event = 0;
  int start = EventLengths[Event];
  int end   = EventLengths[Event+1];
  //std::cout << start << std::endl;
  //std::cout << end << std::endl;

  for (int i = start; i < end; i++) 
  {
    std::vector<double> tmpVec;
    for (int j = 1; j < data[i].size(); j++)
    {
      tmpVec.push_back(data[i][j]);
      std::cout << data[i][j]  << " " ;
    }
    event.push_back(tmpVec);
    std::cout << std::endl;
  }
  return event;
}

int main ()
{
  std::vector<int> EventLengths;
  EventLengths.push_back(0);
  std::vector<std::vector<double>> data;
  int count = 0;
  int runner = 0;

  std::ifstream file("test.txt");
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

    data.push_back(tmpVecD);
  }
  endloop:

  std::cout << "\n" << std::endl;
  for (int i = 0; i < EventLengths.size(); i++) { std::cout << EventLengths[i]  << " ";}
  std::cout << "\n" << std::endl;
  std::cout << "\n" << std::endl;
  //std::vector<std::vector<double>> data;
  //data = DataFileParser("test.txt");

  std::vector<std::vector<double>> eventt;
  int Event = 5;
  int start = EventLengths[Event];
  int end   = EventLengths[Event+1];
  //std::cout << start << std::endl;
  //std::cout << end << std::endl;

  for (int i = start; i < end; i++) 
  {
    std::vector<double> tmpVec2;
    for (int j = 1; j < data[i].size(); j++)
    {
      tmpVec2.push_back(data[i][j]);
      std::cout << data[i][j]  << " " ;
    }
    eventt.push_back(tmpVec2);
    std::cout << std::endl;
  }
  std::cout << "\n" << std::endl;
  std::cout << "\n" << std::endl;


  // testing]


  std::vector<std::vector<double>> eventt2;
  eventt2 =  GetEventVector(Event ,  EventLengths,  data);


  std::cout << "test" << std::endl;
  for (int i = 0; i < eventt.size(); i++) 
  { 
    for (int j = 0; j < eventt[i].size(); j++)
    {
      std::cout << eventt[i][j]-eventt2[i][j]  << " ";   
    }
    std::cout << std::endl; 
    }
  std::cout << "test over" << std::endl;
  std::cout << "\n" << std::endl;
  std::cout << "\n" << std::endl;
  std::cout << EventLengths.size() << std::endl;
  std::cout << "\n" << std::endl;






  std::vector<std::vector<double>> RawDataVector2;
  std::vector<int> EventLengths2;
  DataFileParser2("test.txt", RawDataVector2, EventLengths2);
  Event = 1;
  start = EventLengths2[Event];
  end   = EventLengths2[Event+1];

  for (int i = start; i < end; i++) 
  {
    for (int j = 0; j < RawDataVector2[i].size(); j++)
    {
      std::cout << RawDataVector2[i][j] -data[i][j]  << " " ;
    }
    std::cout << std::endl;
  }


  //std::cout << data[i+1] << std::endl;


  /* for (int i = 0; i < data.size(); i++) { 
        for (int j = 0; j < data[i].size(); j++) 
            std::cout << data[i][j]  << " "; 
            if (std::count(EventLengths.begin(), EventLengths.end(), i))
		          std::cout << "\n" << std::endl;   
        std::cout << std::endl; 
    } */

  /* std::cout << "test" << std::endl;
  std::cout << data[20][0] << std::endl;
  std::cout << data[80][0] << std::endl;
  std::cout << data[80][0]+data[20][0] << std::endl; */
  
  //std::cout << stod(data[0][2]) << std::endl;


}
