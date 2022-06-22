void plot_2Dsp()
{
  // SCINTILLATION DATA
  TCanvas *c1 = new TCanvas();

  TH2F *gr = new TH2F("gr", "SP", 26, 25, 650, 25, 0, 20000); 

  gr->SetStats(0);
  
  fstream file;
  file.open("../Z_data_txt/2Dsp_data.txt", ios::in);

  double xs,ys;

  int ns = 0;
  
  while(1)
    {
      file >> xs >> ys;

      //ns = gr->GetN();

      double Recombination_factor = 1;
      double Scaling_factor = 1;
      
      gr->Fill(xs,ys);
      //gr->SetPointError(ns, exs, eys);

      if(file.eof()) break;
    }
  gr->GetXaxis()->SetRangeUser(4,23);
  gr->Draw("colz");
  gr->SetTitle("Number of Scintillation Photons;Drift Length (mm);Number of Photons Produced (MC Truth)");
  c1->SaveAs("2Dsp_plt.png");
}
