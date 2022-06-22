void plot_enum()
{
  // SCINTILLATION DATA
  TCanvas *c1 = new TCanvas();

  TGraphErrors *gr = new TGraphErrors();

  gr->SetMarkerStyle(4);
  gr->SetMarkerSize(0.2);
  
  fstream file;
  file.open("enum_data.txt", ios::in);

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
  gr->GetYaxis()->SetRangeUser(0,3.5);
  gr->Draw("AP");
  gr->SetTitle("Number of Scattered Electrons;Radius of Detector (in); Number of Electrons Scattered by Incident Gamma");

}
