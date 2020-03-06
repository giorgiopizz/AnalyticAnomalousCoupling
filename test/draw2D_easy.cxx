void draw2D_easy() {

  int n = 0;
  int n_data = 0;

  TTree* limit = (TTree*) _file0->Get("limit");
  //   n = limit->Draw("2*deltaNLL:r","deltaNLL<10 && deltaNLL>-30","l");
  auto *c1 = new TCanvas("c1","A Zoomed Graph",200,10,700,500);
  limit->Draw("2*deltaNLL:k_my_1:k_my_2>>h(100,-20,20,100,-20,20)","2*deltaNLL<10","prof colz");

  limit->Draw("k_my_1:k_my_2","2*deltaNLL <2.41&& 2*deltaNLL >2.35","P same");
  TGraph *best_fit = (TGraph*)gROOT->FindObject("Graph");
  best_fit->SetMarkerSize(1); best_fit->SetMarkerStyle(34);best_fit->SetMarkerColor(kRed); best_fit->Draw("p same");

  //now let's retrieve some info from the file. First we should calculate the area of 68%
  //this is done by counting how many points are included in this region
  //Secondly, we should calculate correlation, this is done by filling a 2D histogram
  //like a scattering plot. So taking all the points included in the region, we plot them
  //and ask root to calculate the correlation

  Float_t px, py, pz;
  limit->SetBranchAddress("deltaNLL",&pz);
  limit->SetBranchAddress("k_my_1",&px);
  limit->SetBranchAddress("k_my_2",&py);
  Int_t nentries = (Int_t)limit->GetEntries();
  int area=0;
  auto *h12 = new TH2F("h12","x vs y",30,-10,10,30, -10, 10);
  for(int i=0;i<nentries;i++){
      limit->GetEntry(i);
      if(2*pz<2.41){
          area++;
          h12->Fill(py,px);
      }
  }
  auto *c2 = new TCanvas("c2","A Zoomed Graph",200,10,700,500);
  h12->Draw("box1");
  cout << area <<endl;
  cout << h12->GetCorrelationFactor() <<endl;




  /*TF2 *g2D=new TF2("g2d" ,"bigaus",-10,10, -10,10);
  g2D->SetParameters(-2,0,5,0,5,-1);

  limit->Fit("g2d");
g2D->Draw("surf,same");
gStyle->SetPalette(1);*/
  /*std::cout << "Name:" <<std::endl;
  string name;
  std::cin >> name;*/
  string name="prova";
  c1->SaveAs(("W_HW_"+name+".png").c_str());

}
