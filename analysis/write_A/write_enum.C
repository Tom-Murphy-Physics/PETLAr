#include <iostream>
#include <fstream>

void write_enum(){

  fstream files_file;
  files_file.open("file_list.txt", ios::in);
  
  string file_name;

  int n_files = 0;

  ofstream myfile;
  myfile.open("enum_data.txt");

  float multiplier = 10;
  
  while(1)
    {

      files_file >> file_name;
      string path = "./light_detection/A_data/" + file_name;

      //cout<<path<<endl;
      
      TFile *f = new TFile(path.c_str());
      
      TH1F * h1 = (TH1F*)f->Get("num_e");
      //cout<<h1->GetMean()<<endl;
      //cout<<h1->GetStdDev()<<endl;

      float x_entry = 0.393701;
       if(files_file.eof()) break;
      
      myfile<<multiplier<<" "<<h1->GetMean()<<" 0 "<<h1->GetMeanError()<<"\n";

      multiplier = multiplier + 5;

     
    }
  myfile.close();
  files_file.close();
  return 0;
}
