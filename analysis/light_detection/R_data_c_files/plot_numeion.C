void plot_numeion()
{
  // SCINTILLATION DATA
  TCanvas *c1 = new TCanvas();

  TGraphErrors *gr = new TGraphErrors();

  gr->SetMarkerStyle(4);
  gr->SetMarkerSize(0.2);
  
  fstream file;
  file.open("../R_data_txt/numeion_data.txt", ios::in);
  cout<<"file opened"<<endl;
  double xs,ys,exs,eys;

  int ns = 0;
  
  while(1)
    {
      file >> xs >> ys >> exs >> eys;

      ns = gr->GetN();

      double Recombination_factor = 0.7455; //Birks Model
      
      gr->SetPoint(ns, xs, ys*Recombination_factor);
      gr->SetPointError(ns, exs, eys*Recombination_factor);

      if(file.eof()) break;
    }
  cout<<"done with plotting"<<endl;
  gr->GetYaxis()->SetRangeUser(0,1000*10);
  gr->Draw("AP");
  gr->SetTitle("Number of Ionized Electrons;Radius of Detector (mm); Number of Ionization Electrons Produced");
  c1->SaveAs("Number_of_Ionized_e-_plt.png");
}
