#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

void readASCIIfiel(TString filePath, TString fileName, 
		   Int_t nnMax, Int_t &nn, 
		   Double_t *xa, Double_t *ya, Double_t *za);

Int_t multigraph(){

  Int_t i =0;
  const Int_t nnMax = 1000;
  TString filePath = "./";
  TString fileName = "" ;
  //---------------------------------------------------------
  Int_t nn1 = 0;
  fileName = "ch1_x.txt";
  Double_t x1[nnMax];
  Double_t y1[nnMax];
  Double_t cur1[nnMax];  
  readASCIIfiel(filePath, fileName, nnMax, nn1, x1, y1, cur1);
  TGraph *gr1 = new TGraph(nn1,x1,cur1);
  gr1->SetName("gr1");
  gr1->SetTitle("Current vs position");
  gr1->SetMarkerStyle(21);
  gr1->SetMarkerColor(kBlack);
  gr1->SetLineColor(kBlack);
  gr1->SetLineWidth(3);
  //---------------------------------------------------------
  Int_t nn2 = 0;
  fileName = "ch2_x.txt";
  Double_t x2[nnMax];
  Double_t y2[nnMax];
  Double_t cur2[nnMax];  
  readASCIIfiel(filePath, fileName, nnMax, nn2, x2, y2, cur2);
  TGraph *gr2 = new TGraph(nn2,x2,cur2);
  gr2->SetName("gr2");
  gr2->SetTitle("Current vs position");
  gr2->SetMarkerStyle(21);
  gr2->SetMarkerColor(kBlue);
  gr2->SetLineColor(kBlue);
  gr2->SetLineWidth(3);
  //---------------------------------------------------------
  Int_t nn3 = 0;
  fileName = "ch3_x.txt";
  Double_t x3[nnMax];
  Double_t y3[nnMax];
  Double_t cur3[nnMax];  
  readASCIIfiel(filePath, fileName, nnMax, nn3, x3, y3, cur3);
  TGraph *gr3 = new TGraph(nn3,x3,cur3);
  gr3->SetName("gr3");
  gr3->SetTitle("Current vs position");
  gr3->SetMarkerStyle(21);
  gr3->SetMarkerColor(kRed);
  gr3->SetLineColor(kRed);
  gr3->SetLineWidth(3);
  //---------------------------------------------------------
  Int_t nn4 = 0;
  fileName = "ch4_x.txt";
  Double_t x4[nnMax];
  Double_t y4[nnMax];
  Double_t cur4[nnMax];  
  readASCIIfiel(filePath, fileName, nnMax, nn4, x4, y4, cur4);
  TGraph *gr4 = new TGraph(nn4,x4,cur4);
  gr4->SetName("gr4");
  gr4->SetTitle("Current vs position");
  gr4->SetMarkerStyle(21);
  gr4->SetMarkerColor(kGreen+3);
  gr4->SetLineColor(kGreen+3);
  gr4->SetLineWidth(3);
  //---------------------------------------------------------

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
  
  // draw a frame to define the range
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr1);
  mg->Add(gr2);
  mg->Add(gr3);
  mg->Add(gr4);

  mg->Draw("APL");

  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr1, "ch1","lp");
  leg->AddEntry(gr2, "ch2","lp");
  leg->AddEntry(gr3, "ch3","lp");
  leg->AddEntry(gr4, "ch4","lp");
  leg->Draw();
}

void readASCIIfiel(TString filePath, TString fileName, 
		   Int_t nnMax, Int_t &nn, 
		   Double_t *xa, Double_t *ya, Double_t *za){
  string mot;
  string line;
  TString fileNameFull = filePath; fileNameFull +="/"; fileNameFull += fileName;
  cout<<"fileNameFull = "<<fileNameFull<<endl;
  ifstream myfile (fileNameFull.Data());
  Int_t i  = 0;
  Double_t x;
  Double_t y;
  Double_t z;
  if(myfile.is_open()){
    myfile>>mot; cout<<setw(10)<<mot;
    myfile>>mot; cout<<setw(10)<<mot;
    myfile>>mot; cout<<setw(10)<<mot<< '\n';
    while(myfile>>x>>y>>z){
      xa[i] = x;
      ya[i] = y;
      za[i] = z;      
      i++;
      if(i>=nnMax){
	cout<<" ---> ERROR : i>=nnMax "<<endl
	    <<"              i = "<<i<<endl
	    <<"          nnMax = "<<nnMax<<endl;
	gSystem->Exit(-1);
      }
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
	<<setw(10)<<za[i]<<endl;
  }
}
