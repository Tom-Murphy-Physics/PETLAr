#include <iostream>
#include <fstream>

void write_2Dsp(){

  fstream files_file;
  files_file.open("file_list.txt", ios::in);
  
  string file_name;

  int n_files = 0;

  ofstream myfile;
  myfile.open("2Dsp_data.txt");

  float multiplier = 25;
  
  while(1)
    {

      files_file >> file_name;
      string path = "./light_detection/Z_data/" + file_name;

      //cout<<path<<endl;
      
      TFile *f = new TFile(path.c_str());
      
      TH1F * h1 = (TH1F*)f->Get("num_sp");
      //cout<<h1->GetMean()<<endl;
      //cout<<h1->GetStdDev()<<endl;

      float x_entry = 6.85354;
       if(files_file.eof()) break;

       for(int i = 0; i <= h1->GetNbinsX(); i ++)
	 {
	   if (h1->GetBinContent(i)!=0)
	     {
	       for (int j = 0; j<=h1->GetBinContent(i);j++)
		 {
		   myfile<<multiplier<<" "<<h1->GetBinCenter(i)<<"\n";
		 }
	     }
	 }
      multiplier = multiplier + 25;

     
    }
  myfile.close();
  files_file.close();
  return 0;
  exit;
}
