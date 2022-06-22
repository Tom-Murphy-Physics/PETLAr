void plot_sp()
{
  // SCINTILLATION DATA
  TCanvas *c1 = new TCanvas();

  TGraphErrors *gr = new TGraphErrors();

  gr->SetMarkerStyle(4);
  gr->SetMarkerSize(0.2);
  
  fstream file;
  file.open("size_data.txt", ios::in);

  double xs,ys,exs,eys;

  int ns = 0;
  
  while(1)
    {
      file >> xs >> ys >> exs >> eys;

      ns = gr->GetN();

      double Recombination_factor = 0.4103;
      double Scaling_factor = 16.77;
      
      gr->SetPoint(ns, xs, ys*Scaling_factor*Recombination_factor);
      gr->SetPointError(ns, exs, eys*Scaling_factor*1.10*Recombination_factor);

      if(file.eof()) break;
    }
  gr->GetYaxis()->SetRangeUser(0,3000);
  gr->Draw("AP");
  gr->SetTitle("Number of Scintillation Photons;Size Multipler of Detector;Number of Photons Produced by Scintillation");
}
