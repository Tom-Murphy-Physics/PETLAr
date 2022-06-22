void plot_2Ddetsp()
{
  // SCINTILLATION DATA
  TCanvas *c1 = new TCanvas();

  TH2F *gr = new TH2F("gr", "Detected SP", 11, 10, 65, 25, 0, 5000); 

  gr->SetStats(0);
  
  fstream file;
  file.open("../A_data_txt/det_2Dsp_data.txt", ios::in);

  double xs,ys;

  int ns = 0;
  
  while(1)
    {
      file >> xs >> ys;

      //ns = gr->GetN();

      double Recombination_factor = 1;
      double Scaling_factor = 100;
      
      gr->Fill(xs,ys*100);
      //gr->SetPointError(ns, exs, eys);

      if(file.eof()) break;
    }
  //gr->GetXaxis()->SetRangeUser(4,23);
  gr->Draw("colz");
  gr->SetTitle("Number of Scintillation Photons Detected;PMT radius (mm);Number of Photons Detected by PMT");
  c1->SaveAs("2DDetected_sp_plt.png");
}
