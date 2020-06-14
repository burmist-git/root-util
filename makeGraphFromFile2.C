// reading a text file
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

void makeGraphFromFile2(){
  string mot;
  string line;
  TString filePath = "./";
  TString fileName = "ch6_mapping_x.txt";
  TString rootFileName = fileName; rootFileName += ".root";
  TString fileNameFull = filePath; fileNameFull +="/"; fileNameFull += fileName;
  ifstream myfile (fileNameFull.Data());
  const Int_t nnMax = 10000;
  Double_t xa[nnMax];
  Double_t ya[nnMax];
  Double_t currenta[nnMax];
  Int_t nn = 0;
  Int_t i  = 0;
  Double_t x;
  Double_t y;
  Double_t current;
  if(myfile.is_open()){
    myfile>>mot; cout<<setw(10)<<mot;
    myfile>>mot; cout<<setw(10)<<mot;
    myfile>>mot; cout<<setw(10)<<mot<< '\n';
    while(myfile>>x>>y>>current){
      xa[i] = x;
      ya[i] = y;
      currenta[i] = current;      
      i++;
      //cout << mot << '\n';
    }
    nn = i;
    myfile.close();
  } 
  else{
    cout << "Unable to open file"; 
  }

  for(i = 0;i<nn;i++){
    cout<<setw(10)<<xa[i]
	<<setw(10)<<ya[i]
	<<setw(10)<<currenta[i]<<endl;
  }

  TGraph *gr = new TGraph(nn,xa,currenta);
  gr->SetName("gr");
  gr->SetTitle("Current vs position");
  gr->SetMarkerStyle(21);
  gr->SetMarkerColor(kRed);
  gr->SetLineColor(kBlack);
  gr->SetLineWidth(3);
  gr->GetXaxis()->SetTitle("x, mm");
  gr->GetYaxis()->SetTitle("I, nA");

  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gStyle->SetOptStat(kFALSE);
  
  TCanvas *c1 = new TCanvas("c1","plots",10,10,800,800);
  c1->Clear();
  c1->SetFillColor(kWhite);
  c1->GetPad(0)->SetLeftMargin(0.12);
  c1->GetPad(0)->SetRightMargin(0.02);
  c1->GetPad(0)->SetTopMargin(0.07);
  //c1->GetPad(0)->SetBottomMargin(0.02);

  TFile f(rootFileName.Data(), "recreate");
  f.cd();
  gr->Write();

  //gr->SetMinimum(0);
  
  gr->Draw("APL");
}
