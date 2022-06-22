#include <string>

void plot_ed()
{
  // SCINTILLATION DATA
  TCanvas *c1 = new TCanvas();
  TMultiGraph *mg = new TMultiGraph();

  int i = 1;
  for (float lambda = 3.0; lambda <=3.0; lambda = lambda + 3)
  {
    TGraphErrors *gr1 = new TGraphErrors();
    TGraphErrors *gr2 = new TGraphErrors();
    TGraphErrors *gr3 = new TGraphErrors();
    TGraphErrors *gr4 = new TGraphErrors();
    
    string label = "n = 1";
    
    gr1->SetMarkerStyle(8);
    gr1->SetMarkerColor(1);
    gr1->SetTitle(label.c_str());
    gr1->SetMarkerSize(1);

    label = "n = 2";
    
    gr2->SetMarkerStyle(8);
    gr2->SetMarkerColor(2);
    gr2->SetTitle(label.c_str());
    gr2->SetMarkerSize(1);

    label = "n = 3";
    
    gr3->SetMarkerStyle(8);
    gr3->SetMarkerColor(3);
    gr3->SetTitle(label.c_str());
    gr3->SetMarkerSize(1);

    label = "n = 4";
    
    gr4->SetMarkerStyle(8);
    gr4->SetMarkerColor(4);
    gr4->SetTitle(label.c_str());
    gr4->SetMarkerSize(1);
    
    fstream file1;
    file1.open("edep1_data.txt", ios::in);

    double xs1,ys1,exs1,eys1;
    //////////////////////////////////////////////////
    fstream file2;
    file2.open("edep2_data.txt", ios::in);

    double xs2,ys2,exs2,eys2;
    //////////////////////////////////////////////////
    fstream file3;
    file3.open("edep3_data.txt", ios::in);

    double xs3,ys3,exs3,eys3;
    //////////////////////////////////////////////////
    fstream file4;
    file4.open("edep4_data.txt", ios::in);

    double xs4,ys4,exs4,eys4;
 
    int ns1 = 0;
    int ns2 = 0;
    int ns3 = 0;
    int ns4 = 0;
  
    while(1)
      {
	file1 >> xs1 >> ys1 >> exs1 >> eys1;
       
	ns1 = gr1->GetN();

	gr1->SetPoint(ns1, xs1, ys1);
	gr1->SetPointError(ns1, exs1, eys1);

	///////////////////////////////////

	file2 >> xs2 >> ys2 >> exs2 >> eys2;
       
	ns2 = gr2->GetN();

	gr2->SetPoint(ns2, xs2, ys2);
	gr2->SetPointError(ns2, exs2, eys2);
	
	////////////////////////////////////

	file3 >> xs3 >> ys3 >> exs3 >> eys3;
       
	ns3 = gr3->GetN();

	gr3->SetPoint(ns3, xs3, ys3);
	gr3->SetPointError(ns3, exs3, eys3);

	////////////////////////////////////
	
	file4 >> xs4 >> ys4 >> exs4 >> eys4;
       
	ns4 = gr4->GetN();

	gr4->SetPoint(ns4, xs4, ys4);
	gr4->SetPointError(ns4, exs4, eys4);
	cout<<ns4<<endl;

	if(file1.eof()) break;
      }

    gr1->GetYaxis()->SetRangeUser(0,500*10);
    gr1->Draw("AP");
    mg->Add(gr1);
    
    gr2->GetYaxis()->SetRangeUser(0,500*10);
    gr2->Draw("AP");
    mg->Add(gr2);
    
    gr3->GetYaxis()->SetRangeUser(0,500*10);
    gr3->Draw("AP");
    mg->Add(gr3);

    gr4->GetYaxis()->SetRangeUser(0,500*10);
    gr4->Draw("AP");
    mg->Add(gr4);
    
    i++;
  }
  mg->Draw("AP");
  mg->SetTitle("Energy Deposition per Event;Size Multiplier of Detector;Energy Deposition (MeV)");
  mg->GetYaxis()->SetRangeUser(0,0.2);
  //mg->GetXaxis()->SetRangeUser();
  c1->BuildLegend();
  c1->SaveAs("Energy_Deposition_plt.png");
}


