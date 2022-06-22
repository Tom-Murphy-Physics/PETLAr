#include <cmath>
#include <iostream>

void interaction_study(){
  
  float W = 23.6/1000000; 
  float Recombo = 0.4623; //Birk's Model

  cout<<"Please Enter the filename: ";
  string filename;
  cin>>filename;
  
  string infilename = "../build/" + filename;
  string outfilename = "./" + filename;

  ifstream myfile;
  myfile.open(infilename.c_str());
  if (myfile)
    {
      cout<<"file exists"<<endl;
    
  
  TCanvas *c1 = new TCanvas("c1","c1");
  TCanvas *c2 = new TCanvas("c2","c2");
  TCanvas *c3 = new TCanvas("c3","c3");

  TFile *input = new TFile(infilename.c_str());
  TFile *output = new TFile(outfilename.c_str(), "RECREATE");
  TTree *tree = (TTree*)input->Get("Hits;1");
  
  Float_t val[1];
  Int_t entries=(Int_t)tree->GetEntries();

  TH1I *num_e1 = new TH1I("num_e1", "Number of electrons in a given event", 25, 0, 0.55);
  TH1I *num_e2 = new TH1I("num_e2", "Number of electrons in a given event", 25, 0, 0.55);
  TH1I *num_e3 = new TH1I("num_e3", "Number of electrons in a given event", 25, 0, 0.55);
  TH1I *num_e4 = new TH1I("num_e4", "Number of electrons in a given event", 25, 0, 0.55);

  TH1F *num_e_ion1 = new TH1F("num_e_ion1", "Number of electrons in a given event", 25, 0, 10000);
  TH1F *num_e_ion2 = new TH1F("num_e_ion2", "Number of electrons in a given event", 25, 0, 10000);
  TH1F *num_e_ion3 = new TH1F("num_e_ion3", "Number of electrons in a given event", 25, 0, 10000);
  TH1F *num_e_ion4 = new TH1F("num_e_ion4", "Number of electrons in a given event", 25, 0, 10000);
  
  TH1F *pen_depth1 = new TH1F("pen_depth1", "Average Photon Penetration depth", 25, 0, 500);
  TH1F *pen_depth2 = new TH1F("pen_depth2", "Average Photon Penetration depth", 25, 0, 500);
  TH1F *pen_depth3 = new TH1F("pen_depth3", "Average Photon Penetration depth", 25, 0, 500);
  TH1F *pen_depth4 = new TH1F("pen_depth4", "Average Photon Penetration depth", 25, 0, 500);
  
  int scattering_event = 1;
  int initial_event_id = 0;

  float e_position = 0;
  for(int i = 0; i<entries;i++)
    {
      tree->GetEntry(i);
      double eE = tree->GetLeaf("delta_E")->GetValue(0);
      
      val[0] = tree->GetLeaf("event_id")->GetValue(0);
      
      if(val[0] == initial_event_id)
	{
          if(tree->GetLeaf("track_id")->GetValue(0)==1)
  	    {
	      if(tree->GetLeaf("delta_E")->GetValue(0)!=0)
 	        {
		  if (scattering_event == 1)
		    {
		     num_e1->Fill(-1*tree->GetLeaf("delta_E")->GetValue(0));
		     num_e_ion1->Fill(-1*tree->GetLeaf("delta_E")->GetValue(0)/W*Recombo-1);
        	    }
		  if (scattering_event == 2)
		    {
		     num_e2->Fill(-1*tree->GetLeaf("delta_E")->GetValue(0));
		     num_e_ion2->Fill(-1*tree->GetLeaf("delta_E")->GetValue(0)/W*Recombo-1);
        	    }
		  if (scattering_event == 3)
		    {
		     num_e3->Fill(-1*tree->GetLeaf("delta_E")->GetValue(0));
		     num_e_ion3->Fill(-1*tree->GetLeaf("delta_E")->GetValue(0)/W*Recombo-1);
        	    }
		  if (scattering_event == 4)
		    {
		     num_e4->Fill(-1*tree->GetLeaf("delta_E")->GetValue(0));
		     num_e_ion4->Fill(-1*tree->GetLeaf("delta_E")->GetValue(0)/W*Recombo-1);
        	    }
		  scattering_event = scattering_event + 1;
	        }
   	    }

	   if (tree->GetLeaf("track_id")->GetValue(0) == 1)
	    {
	      if (tree->GetLeaf("delta_E")->GetValue(0) == 0)
		{
		  e_position = e_position + tree->GetLeaf("delta_z")->GetValue(0);
		}
	      else
		{
		  e_position = e_position + tree->GetLeaf("delta_z")->GetValue(0);
		  if(scattering_event-1 == 1)
		    {
		      pen_depth1->Fill(e_position);
		    }
		  if(scattering_event-1 == 2)
		    {
		      pen_depth2->Fill(e_position);
		    }
		  if(scattering_event-1 == 3)
		    {
		      pen_depth3->Fill(e_position);
		    }
		  if(scattering_event-1 == 4)
		    {
		      pen_depth4->Fill(e_position);
		    }
		}
	    }
	}
      else
	{
	  
	  
	  scattering_event = 1;
	  initial_event_id = initial_event_id + 1;
	  e_position = 0;
	}
    }
  
  num_e1->SetLineColor(kBlue);
  num_e2->SetLineColor(kRed);
  num_e3->SetLineColor(kGreen);
  num_e4->SetLineColor(kCyan);
  c1->cd();
  num_e1->Draw();
  num_e2->Draw("SAME");
  num_e3->Draw("SAME");
  num_e4->Draw("SAME");

  num_e_ion1->SetLineColor(kBlue);
  num_e_ion2->SetLineColor(kRed);
  num_e_ion3->SetLineColor(kGreen);
  num_e_ion4->SetLineColor(kCyan);
  c2->cd();
  num_e_ion1->Draw();
  num_e_ion2->Draw("SAME");
  num_e_ion3->Draw("SAME");
  num_e_ion4->Draw("SAME");
  
  pen_depth1->SetLineColor(kBlue);
  pen_depth2->SetLineColor(kRed);
  pen_depth3->SetLineColor(kGreen);
  pen_depth4->SetLineColor(kCyan);
  c3->cd();
  pen_depth1->Draw();
  pen_depth2->Draw("SAME");
  pen_depth3->Draw("SAME");
  pen_depth4->Draw("SAME");
  
  output->Write("test.root");
  input->Close();
    }
  else
    {cout<<"Could not find file"<<endl;}
}
