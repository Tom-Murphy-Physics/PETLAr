#include <string>
#include <cmath>

void plot_chargepp()
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
    file.open("../R_data_txt/numeion_data.txt", ios::in);

    fstream filepen;
    filepen.open("../R_data_txt/pen_depth.txt", ios::in);

    fstream file2;
    file2.open("../R_data_txt/enum_data.txt", ios::in);
    
    double ixs,iys,iexs,ieys;
    double xsd,ysd,exsd,eysd;
    double exs,eys,eexs,eeys;
  
    int ns = 0;
  
    while(1)
      {
	file >> ixs >> iys >> iexs >> ieys;
	filepen >> xsd >> ysd >> exsd >> eysd;
	file2 >> exs >> eys >> eexs >> eeys;
      
	ns = gr->GetN();

	double Recombination_factor = 0.7455; //Birks Model
      
	//cout<<exp(-lambda*(ixs*150-ysd)/1000)<<endl;
      
	gr->SetPoint(ns, ixs, iys/eys*Recombination_factor*exp(-lambda*(150-ysd)/1000));
	gr->SetPointError(ns, iexs,sqrt(ieys*ieys + eeys*eeys)*Recombination_factor*exp(-lambda*(150-ysd)/1000));

	if(file.eof()) break;
      }
    gr->GetYaxis()->SetRangeUser(0,500*10);
    gr->Draw("AP");
    mg->Add(gr);
    i++;
  }
  mg->Draw("AP");
  mg->SetTitle("Charge at Pixels per Electron Scattering;Radius of Detector (mm);Number of Ionization Electrons at Pixels");
  mg->GetYaxis()->SetRangeUser(0,200*10);
  c1->BuildLegend();
  c1->SaveAs("Chargepp_plt.png");
}


