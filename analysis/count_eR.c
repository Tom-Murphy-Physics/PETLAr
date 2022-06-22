#include <cmath>
#include <iostream>

void count_eR(){
  
  float W = 23.6/1000000; 
  float Recombo = 0.4623; //Birk's Model
  
  fstream files_file;
  files_file.open("./files_file.txt", ios::in);
  
  string filename;
  
  int n_files = 0;
  while(1)
    {
      files_file >> filename;
      cout<<filename<<endl;
       string infilename = "./../build/R_data/" + filename;
       string outfilename = "./" + filename;
  
       ifstream myfile;
        myfile.open(infilename.c_str());
	if (myfile)
	  {
	    cout<<"file exists"<<endl;
	     
	    cout<<infilename.c_str()<<endl;;
	    
	    if(files_file.eof()) break;
	    TCanvas *c1 = new TCanvas("c1","c1");
	    TCanvas *c2 = new TCanvas("c2","c2");
	    TCanvas *c3 = new TCanvas("c3","c3");
	    TCanvas *c4 = new TCanvas("c4","c4");
	    TCanvas *c5 = new TCanvas("c5","c5");
	    TCanvas *c6 = new TCanvas("c6","c6");
	    TCanvas *c7 = new TCanvas("c7","c7");
	    TCanvas *c8 = new TCanvas("c8","c8");
	      
	    TFile *input = new TFile(infilename.c_str());
	    TFile *output = new TFile(outfilename.c_str(), "RECREATE");
	    TTree *tree = (TTree*)input->Get("Hits;1");
  
	    Float_t val[1];
	    Int_t entries=(Int_t)tree->GetEntries();

	    TH1F *Es = new TH1F("Es", "Electron Energy", 25, 0, 0.55);
	    TH1I *num_e = new TH1I("num_e", "Number of electrons in a given event", 20, 0, 20);
	    TH1I *num_sp = new TH1I("num_sp", "Number of Scintilation photons", 25000, 0, 25000);
	    TH1F *Edep = new TH1F("Edep", "Energy Deposition per Event", 25, 0, 0.55);
	    TH1F *num_e_ion = new TH1F("num_e_ion", "Number of ionization electrons per track", 20, 0, 11000);
	    TH1F *pen_depth = new TH1F("pen_depth", "Average Photon Penetration depth", 20, 0, 1000);
	    TH1I *det_sp = new TH1I("det_sp", "Number of Detected Scintillation Photons", 2000, 0, 2000);
	    TH1F *drift_d = new TH1F("drift_d", "Electrion drift length", 25, 0, 50);
	    
	    int initial_event_id = 0;
	    int number_of_tracks = 0;
	    int number_of_scintilation_photons = 0;
	    float energy_dep = 0;
	    float E_ionization = 0;
	    float e_position = 0;
	    int ndet_sp = 0;
	    float drifted = 0;
	    
	    for(int i = 0; i<entries;i++)
	      {
		tree->GetEntry(i);
		double eE = tree->GetLeaf("delta_E")->GetValue(0);
      
		val[0] = tree->GetLeaf("event_id")->GetValue(0);
		//cout<<val[0]<<"\t"<<tree->GetLeaf("track_id")->GetValue(0)<<"\t"<<tree->GetLeaf("type")->GetValue(0)<<"\t"<<eE<<"\t"<<tree->GetLeaf("fdetected_sp")->GetValue(0)<<endl;
      
		if(val[0] == initial_event_id)
		  {
		    if (tree->GetLeaf("track_id")->GetValue(0)==1)
		      {
			if (tree->GetLeaf("delta_E")->GetValue(0) != 0)
			  {
			    Es->Fill(-1*tree->GetLeaf("delta_E")->GetValue(0));
			    number_of_tracks++;
			  }
			energy_dep = energy_dep + tree->GetLeaf("delta_E")->GetValue(0);
		      }

		    // Energy deposited by each electron (note this does double count if
		    // an electron produces another electron)
		    if (tree->GetLeaf("track_id")->GetValue(0)>1 && tree->GetLeaf("type")->GetValue(0) == 1)
		      {
			//energy_dep = energy_dep - tree->GetLeaf("delta_E")->GetValue(0);
		      }

		    // Finds the number of optical photons
		    if (tree->GetLeaf("type")->GetValue(0) == 2)
		      {
			number_of_scintilation_photons ++;
		      }

		    // Finds the number of electrons released from ionization 
		    if (tree->GetLeaf("track_id")->GetValue(0) == 1)
		      {
			E_ionization = E_ionization - tree->GetLeaf("delta_E")->GetValue(0);
		      }
		    if (val[0] == 35 )
		      {
			// cout<<val[0]<<"\t"<<tree->GetLeaf("track_id")->GetValue(0)<<"\t"<<tree->GetLeaf("type")->GetValue(0)<<"\t"<<eE<<endl;
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
			    pen_depth->Fill(e_position);
			  }
		      }/*
		    if (tree->GetLeaf("fdetected_sp")->GetValue(0) != 0)
		      {
			ndet_sp = ndet_sp + 1;
			//cout<<ndet_sp<<endl;
			}*/
		    if (tree->GetLeaf("type")->GetValue(0) == 1)
		      {
			drifted = drifted + tree->GetLeaf("mx_y")->GetValue(0);
		      }
		    if (tree->GetLeaf("type")->GetValue(0) == 3)
		      {
			ndet_sp = ndet_sp + 1;
		      }
		  }
		else
		  {
		    //cout<<number_of_scintilation_photons<<endl;
		    float num_e_ionization = E_ionization/W*Recombo;
		    //cout<<num_e_ionization<<endl;
		    num_e->Fill(number_of_tracks);
		    num_e_ion -> Fill(num_e_ionization);
		    num_sp->Fill(number_of_scintilation_photons);
		    Edep->Fill(-energy_dep);
		    if (ndet_sp != 0){
		      det_sp->Fill(ndet_sp);}
		    drift_d->Fill(drifted/number_of_tracks);
	  
		    number_of_tracks = 0;
		    number_of_scintilation_photons = 0;
		    initial_event_id = initial_event_id + 1;
		    energy_dep = 0;
		    energy_dep = energy_dep + tree->GetLeaf("delta_E")->GetValue(0);
		    E_ionization = 0;
		    e_position = 0;
		    ndet_sp = 0;
		    drifted = 0;
		  }
	      }
  
	    num_e->SetFillStyle(3001);
	    num_e->SetFillColor(kBlue);
	    num_sp->SetFillStyle(3001);
	    num_sp->SetFillColor(kRed);
	    c1->cd();
	    num_e->Draw();
	    c2->cd();
	    Es->Draw();
	    c3->cd();
	    num_sp->Draw();
	    c4->cd();
	    c4->SetLogy();
	    Edep->Draw();
	    c5->cd();
	    num_e_ion->Draw();
	    c6->cd();
	    pen_depth->Draw();
	    c7->cd();
	    det_sp->Draw();
	    c8->cd();
	    drift_d->Draw();
	    output->Write("./root_files");
	    input->Close();
	  }
	else{cout<<"couldnt find"<<endl;}
	
    }
}
