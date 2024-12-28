double fitfunc(double* x, double* par){
    //return par[0]*exp(-x[0]) + par[1] * exp(-0.5*pow((x[0] - par[3]), 2)/(pow(par[2],2)));
    return par[0]*exp(-x[0]) + par[1]*TMath::Landau(x[0], par[2], par[3], false);
}

void readfromfile(std::string filename, TH1D *hist)
{
    std::ifstream file(filename, std::ios::in);
    double x;
    while (file >> x) {hist->Fill(x);}
}

void fitting(){    
    TH1D* hist = new TH1D("h1", "title.png", 100, 0, 10);
    
    readfromfile("./data.dat", hist);

    TF1* fitcurve = new TF1("fitcurve", "fitfunc", 0, 10, 4);
    
    fitcurve->SetParLimits(0, 10, 35);    
    fitcurve->SetParLimits(1, 70, 120);    
    fitcurve->SetParLimits(2, 2, 8);  
    fitcurve->SetParLimits(3, 0.3, 1.9);

    // fitcurve->SetParLimits(0, 20, 25);    
    // fitcurve->SetParLimits(1, 10, 20);    
    // fitcurve->SetParLimits(2, 1, 3);  
    // fitcurve->SetParLimits(3, 4, 6);


    hist->Fit(fitcurve, "P");
    gStyle->SetOptFit(1100);

    auto canvas = new TCanvas("canvas", "title.png");

    hist->Draw();
    fitcurve->Draw("same");

}