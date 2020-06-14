//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>

//root
#include <TROOT.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h>
#include <TVector3.h>

using namespace std;

Int_t readFile( TString fname, Double_t *x1, Double_t *x2, Double_t *x3, Double_t *x4);

const Int_t nnMax = 1000;
Int_t verboseLevel = 0;

Int_t makeHistFromFile(){
  Int_t n = 0;
  Int_t i = 0;
  Double_t x1[nnMax];
  Double_t x2[nnMax];
  Double_t x3[nnMax];
  Double_t x4[nnMax];
  //[INFO] Version = 2 serial = A001 id = CAu1-1 n = 1.0435 transmLength = 5.6 thickness = 2.03
  TString fname = "./aerogelInfo.out"; 
  TString fnameroot = fname; fnameroot += ".root";

  // --> READING FILE <--
  n = readFile(fname,x1,x2,x3,x4);

  // --> HISTOGRAMING <--
  TH1D *h1_Version = new TH1D("h1_Version","Version",100,0,4);
  TH1D *h1_n = new TH1D("h1_n","n",100,1.04,1.06);
  TH1D *h1_transmLength = new TH1D("h1_transmLength","transmLength",20,3.0,6.0);
  TH1D *h1_thickness = new TH1D("h1_thickness","thickness",100,1.95,2.1);
  TH1D *h1_n_A = new TH1D("h1_n_A","n A",100,1.04,1.06);
  TH1D *h1_transmLength_A = new TH1D("h1_transmLength_A","transmLength A",20,3.0,6.0);
  TH1D *h1_thickness_A = new TH1D("h1_thickness_A","thickness A",100,1.95,2.1);
  TH2D *h2_n_vs_transmLength_A = new TH2D("h2_n_vs_transmLength_A","n vs transmLength A",100,1.04,1.06,20,3.0,6.0);
  TProfile *pr_n_vs_transmLength_A = new TProfile("pr_n_vs_transmLength_A","n vs transmLength A",100,1.04,1.06);
  TH1D *h1_n_B = new TH1D("h1_n_B","n B",100,1.04,1.06);
  TH1D *h1_transmLength_B = new TH1D("h1_transmLength_B","transmLength B",20,3.0,6.0);
  TH1D *h1_thickness_B = new TH1D("h1_thickness_B","thickness B",100,1.95,2.1);
  TH2D *h2_n_vs_transmLength_B = new TH2D("h2_n_vs_transmLength_B","n vs transmLength B",100,1.04,1.06,20,3.0,6.0);
  TProfile *pr_n_vs_transmLength_B = new TProfile("pr_n_vs_transmLength_B","n vs transmLength B",100,1.04,1.06);

  for(i = 0;i<n;i++){
    h1_Version->Fill(x1[i]);
    h1_n->Fill(x2[i]);
    h1_transmLength->Fill(x3[i]);
    h1_thickness->Fill(x4[i]);
    if(i<170){
      h1_n_A->Fill(x2[i]);
      h1_transmLength_A->Fill(x3[i]);
      h1_thickness_A->Fill(x4[i]);
      h2_n_vs_transmLength_A->Fill(x2[i],x3[i]);
      pr_n_vs_transmLength_A->Fill(x2[i],x3[i]);
    }
    if(i>=170){
      h1_n_B->Fill(x2[i]);
      h1_transmLength_B->Fill(x3[i]);
      h1_thickness_B->Fill(x4[i]);
      h2_n_vs_transmLength_B->Fill(x2[i],x3[i]);
      pr_n_vs_transmLength_B->Fill(x2[i],x3[i]);
    }
  }
  
# ifdef __CINT__
  // --> DISPLAY <--
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);  
  TCanvas *c1 = new TCanvas("c1","plots",10,10,800,800);
  c1->Clear();
  c1->SetFillColor(kWhite);
  c1->GetPad(0)->SetLeftMargin(0.12);
  c1->GetPad(0)->SetRightMargin(0.02);
  c1->GetPad(0)->SetTopMargin(0.07);
  c1->GetPad(0)->SetBottomMargin(0.02);
# endif

  // --> SAVING <--
  TFile f(fnameroot.Data(), "recreate");
  f.cd();
  h1_Version->Write();
  h1_n->Write();
  h1_transmLength->Write();
  h1_thickness->Write();
  h1_n_A->Write();
  h1_transmLength_A->Write();
  h1_thickness_A->Write();
  h2_n_vs_transmLength_A->Write();
  pr_n_vs_transmLength_A->Write();
  h1_n_B->Write();
  h1_transmLength_B->Write();
  h1_thickness_B->Write();
  h2_n_vs_transmLength_B->Write();
  pr_n_vs_transmLength_B->Write();

  return 0;
}

Int_t readFile( TString fname, Double_t *x1, Double_t *x2, Double_t *x3, Double_t *x4){
  string mot;
  string mot1;
  string mot2;
  string mot3;
  ifstream myfile(fname.Data());
  Int_t nn = 0;
  Double_t x1v, x2v, x3v, x4v;
  //[INFO] Version = 2 serial = A001 id = CAu1-1 n = 1.0435 transmLength = 5.6 thickness = 2.03
  if(myfile.is_open()){
    while(myfile>>mot1>>mot2>>mot3>>x1v){
      //cout<<mot1<<endl;
      myfile>>mot>>mot>>mot>>mot>>mot>>mot>>mot>>mot>>x2v;
      myfile>>mot>>mot>>x3v;
      myfile>>mot>>mot>>x4v;
      x1[nn] = x1v;
      x2[nn] = x2v;
      x3[nn] = x3v;
      x4[nn] = x4v;
      nn++;
      if(verboseLevel>0)
	cout<<setw(10)<<x1v<<setw(10)<<x2v<<setw(10)<<x3v<<setw(10)<<x4v<<endl;
    }
    myfile.close();
  } 
  else{
    cout << "Unable to open file"; 
  }
  return nn;
}

# ifndef __CINT__
int main(int argc, char *argv[]){
  makeHistFromFile();
  return 0;
}
# endif
