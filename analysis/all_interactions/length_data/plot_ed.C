void plot_ed()
{
  // SCINTILLATION DATA
  TCanvas *c1 = new TCanvas();

  TGraphErrors *gr = new TGraphErrors();

  gr->SetMarkerStyle(4);
  gr->SetMarkerSize(0.2);
  
  fstream file;
  file.open("edep_data.txt", ios::in);

  double xs,ys,exs,eys;

  int ns = 0;
  
  while(1)
    {
      file >> xs >> ys >> exs >> eys;

      ns = gr->GetN();

      gr->SetPoint(ns, xs, ys);
      gr->SetPointError(ns, exs, eys);

      if(file.eof()) break;
    }
  gr->GetYaxis()->SetRangeUser(0,0.6);
  gr->Draw("AP");
  gr->SetTitle("Energy Deposition per Event;Length of Detector (in); Energy Deposition inside Detector (MeV)");
}
