void plotsFast(){
  
  TString fileN;
  fileN = "./ARICHEvents.root";
  TFile *f1 = new TFile(fileN.Data());
  TTree *tree = (TTree*)f1->Get("arich");
    
  TH1F *h1_nphot = new TH1F("h1_nphot","nphot",20,0.0,20);
  TH2F *h2_y_vs_x_hit = new TH2F("h2_y_vs_x_hit","y vs x hit",200,-200.0,200.0,200,-200.0,200.0);

  tree->Draw("nrec>>h1_nphot");

  tree->Draw("mcHit.x:mcHit.y>>h2_y_vs_x_hit");

  //likelihood distributions for efficiency calculation 
  //h_pi = new TH2F("h_pi","h_pi",pbin,pstart,pstop,50000,-200,200);
  //h_K = new TH2F("h_K","h_K",pbin,pstart,pstop,50000,-200,200); 
  //ch->Draw("(logL.pi-logL.K):mcHit.p>>h_pi","abs(mcHit.PDG)==211 && primary==1");
  //ch->Draw("(logL.pi-logL.K):mcHit.p>>h_K","abs(mcHit.PDG)==321 && primary==1");
  
  // 2D histogram of K efficiency vs. pi fake rate vs. momentum (to je faca)
  //hh = new TH2F("hh","K id. efficiency;Momentum [GeV];#pi missid. prob.",pbin,pstart,pstop,100,0.005,0.10);
 
  // 1D histograms of K efficiency vs. momentum for 3 different pion fake rates
  //TH1F* h_eff1 = new TH1F("h_eff1","Kaon id. efficiency at 2% pion fake rate;momentum [GeV]",pbin,pstart,pstop); 
  //TH1F* h_eff2 = new TH1F("h_eff2","Kaon id. efficiency at 4% pion fake rate;momentum [GeV]",pbin,pstart,pstop); 
  //TH1F* h_eff3 = new TH1F("h_eff3","Kaon id. efficiency at 2%,4%,6% pion fake rate;momentum [GeV]",pbin,pstart,pstop); 

 TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,600,600);

  c1->SetRightMargin(0.03);
  c1->SetLeftMargin(0.09);
  c1->SetTopMargin(0.03);
  c1->SetBottomMargin(0.09);


  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);

  //h1_nphot->Draw();

  h2_y_vs_x_hit->Draw("ZCOLOR");
}
