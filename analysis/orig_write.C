#include <iostream>
#include <fstream>

void orig_write(){

  fstream files_file;
  files_file.open("./each_interaction/total_data/file_list.txt", ios::in);
  
  string file_name;

  int n_files = 0;

  ofstream myfile;
  myfile.open("numeion4_data.txt");

  float multiplier = 0.50;
  
  while(1)
    {

      files_file >> file_name;
      string path = "./" + file_name;

      //cout<<path<<endl;
      
      TFile *f = new TFile(path.c_str());
      
      TH1F * h1 = (TH1F*)f->Get("num_e_ion4");
      //cout<<h1->GetMean()<<endl;
      //cout<<h1->GetStdDev()<<endl;

      float x_entry = 1.0;
       if(files_file.eof()) break;
      
      myfile<<multiplier*x_entry<<" "<<h1->GetMean()<<" 0 "<<h1->GetMeanError()<<"\n";

      multiplier = multiplier + 0.05;

     
    }
  myfile.close();
  files_file.close();
  return 0;
}
