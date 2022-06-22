#include <string>
#include <cmath>

void plot_cloud()
{
  // SCINTILLATION DATA
  TCanvas *c1 = new TCanvas();
  TMultiGraph *mg = new TMultiGraph();

  int i = 1;
  for (double lambda = 0.2; lambda <=3.0; lambda = lambda + 0.4)
  {
    TGraphErrors *gr = new TGraphErrors();

    string label = "lambda = " + std::to_string(lambda);
    
    gr->SetMarkerStyle(8);
    gr->SetMarkerColor(i);
    gr->SetTitle(label.c_str());
    gr->SetMarkerSize(1);
  
    fstream file;
    file.open("../A_data_txt/cloud_data.txt", ios::in);

    fstream filepen;
    filepen.open("../A_data_txt/pen_depth.txt", ios::in);

    double xs,ys,exs,eys;
    double xsd,ysd,exsd,eysd;
  
    int ns = 0;
  
    while(1)
      {
	file >> xs >> ys >> exs >> eys;
	filepen >> xsd >> ysd >> exsd >> eysd;
      
	ns = gr->GetN();

	double Recombination_factor = 0.7455; //Birks Model
	double Dt = 1695.62;
	double V = 2175000;

	gr->SetPoint(ns, xs, ys + 4*sqrt((2*Dt*(150-ysd))/V));
	gr->SetPointError(ns, exs, eys+4*sqrt((2*Dt*(eysd))/V));

	if(file.eof()) break;
      }
    gr->GetYaxis()->SetRangeUser(0,500*10);
    gr->Draw("AP");
    mg->Add(gr);
    i++;
  }
  mg->Draw("AP");
  mg->SetTitle("Track Length at Pixel Plane (96CL);Radius of PMT (mm);Length of Track (mm)");
   mg->GetYaxis()->SetRangeUser(0,6);
  c1->BuildLegend();
  c1->SaveAs("Cloud_Size_plt.png");
}


