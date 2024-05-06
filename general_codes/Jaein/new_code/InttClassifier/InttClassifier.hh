#pragma once

//#include <iostream>
#include <cdbobjects/CDBTTree.h>
#include "constant_values.hh"
#include "functions.hh"

// It supposed to be used as a part of ROOT macros
class InttClassifier
{
private:
  /////////////////////////////////////////////////
  // constant values: see constant_values.hh

  /////////////////////////////////////////////////
  // general variables
  int run_num_ = 0;
  double sig_cut_ = 3.0;
  bool Writecsv_ = false;
  int in_sig_ = 0; 

  /////////////////////////////////////////////////
  // File I/O
  std::string hitmap_file_ = ""; // path to the hitmap file

  // for CDB
  std::string output_cdb_dir_ = kIntt_cdb_dir; // path to the output dir of CDB files
  std::string output_cdb_file_ = ""; // path th the file

  // for QA
  std::string output_qa_root_path_ = kIntt_hotmap_dir; // path to the QA ROOT dir
  std::string output_qa_root_file_ = ""; // path to the QA ROOT file
  std::string output_qa_pdf_path_ = kIntt_hotmap_dir; // path to the QA pdf dir
  std::string output_qa_pdf_file_ = ""; // path to the QA pdf file
  std::string output_qa_txt_file_ = "";
  
  // TFile I/O
  TFile* tf_hitmap_; // input
  TTree* tt_runinfo_; // input
  
  // TTree I Branch
  TFile* tf_qa_; // output
  int runnumber_;
  uint32_t total_event_;
  uint32_t merged_event_ = 0;
  /////////////////////////////////////////////////
  // QA hists/outputs
  TH1D* h1_hist_MPV_; // #hit distribution for each channel. 0 count is excluded.
  TH1D* h1_hist_gaus_; // #hit distribution for each channel. 0 count is excluded.
  TH1D* h1_hist_gaus_felix_[8]; // #hit distribution for each channel. 0 count is excluded.
  TH1D* h1_hist_chip_;  
  TH1D* h1_hist_MPV_ladder_;
  int NumberOfFiredChan_[8][14] = { 0 };

  TCanvas *canA_[8];
  TCanvas *canB_[8];

  TTree* tree_output_;
  // variables for the tree_output_
  double ch_entry_;
  double mean_gaus_;
  double sigma_gaus_;
  int felix_;
  int module_;
  int chip_id_;
  int chan_;
  int type_;
  int flag_;

  /////////////////////////////////////////////////
  //
  TH1D *h1_hist_fit_A_[8][14];
  TH1D *h1_hist_fit_B_[8][14];

  TH2D *h2_AllMap_[8][14]; // Original HitMap
  TH2D *h2_ColdMap_[8][14];// 2D histogram for coldmap
  TH2D *h2_HalfMap_[8][14];// 2D histogram for halfmap (half entry chips)
  TH2D *h2_DeadMap_[8][14];// 2D histogram for deadmap
  TH2D *h2_HotMap_[8][14]; // 2D histogram for hotmap

  /////////////////////////////////////////////////
  // not used...
  // double HotChannelCut_A_Fit_[8][14] = {0.};
  // double HotChannelCut_B_Fit_[8][14] = {0.};
  // double ColdChannelCut_A_Fit_[8][14] = {0.};
  // double ColdChannelCut_B_Fit_[8][14] = {0.};
  // double par_meanA_[8][14] = {0.};  // Array to save the mean & sigma value, [0][module] = mean, [1][module] = sigma
  // double par_sigmaA_[8][14] = {0.}; // Array to save the mean & sigma value, [0][module] = mean, [1][module] = sigma
  // double par_meanB_[8][14] = {0.};  // Array to save the mean & sigma value, [0][module] = mean, [1][module] = sigma
  // double par_sigmaB_[8][14] = {0.}; // Array to save the mean & sigma value, [0][module] = mean, [1][module] = sigma

  /////////////////////////////////////////////////
  // Cut variables
  int hot_ch_cut_ = 0;
  double hot_ladder_cut_ = 0.0;
  double hot_ch_cut_gaus_[8] = {0.}; 
  /////////////////////////////////////////////////
  // Init functions
  void Init();
  void InitPaths();
  void InitHists();
  void InitQaTree();

  /////////////////////////////////////////////////
  // misc
  void DrawHists();
  TLine* DrawThreshold( double threshold, bool log_y=false );
  TFitResultPtr DoGaussianFit(TH1* hist); 
  struct Half_Chip
  {
    int _felix_id_;
    int _module_id_;
    int _chip_id_;
  };
  std::vector<Half_Chip> half_Chips_ = // Chip number 0~25
      {
          // Felix 0
          {0, 7, 14},
          // Felix 2
          // Felix 3
          {3, 13, 20},
          {3, 13, 22},
          {3, 13, 24},
          // Felix 7
          {7, 0, 0},
          {7, 0, 1},
          {7, 0, 2},
          {7, 0, 3},
          {7, 0, 4},
          {7, 0, 6},
          {7, 0, 8},
          {7, 0, 10},
          {7, 0, 12},
          {7, 0, 13},
          {7, 0, 14},
          {7, 0, 15},
          {7, 0, 16},
          {7, 0, 17},
          {7, 0, 19},
          {7, 0, 21},
          {7, 0, 23},
          {7, 0, 25},
          {7, 1, 0},
          {7, 1, 1},
  };
  template <class TH>
  int GetMaxBinWithEntry(TH *hist)
  {
    for (int i = hist->GetNbinsX(); i > 0; i--)
    {
      if (hist->GetBinContent(i) > 0)
      {
        return i;
        break;
      }
    }
    return 1;
  }

  template < class TH >
  void HistConfig( TH* hist )
  {
    hist->SetLineColor( kAzure + 1 );
    hist->SetLineWidth( 2 );
    hist->SetFillColorAlpha( hist->GetLineColor(), 0.1 );
    int max_bin = GetMaxBinWithEntry( hist );
    hist->GetXaxis()->SetRange( 1, max_bin );
  }
  
  /////////////////////////////////////////////////
  // Things for print
  bool process_done_ = false;
  bool isbeam_ = false;
  bool ishot_ = false;
  vector < std::string > printed_contents_;
  void PrintLine( std::string head, string contents, string separator = ":" );
  void DumpPrintBuffer();

public:
  /////////////////////////////////////////////////
  // Constructor
  InttClassifier( int run_num , double sig_cut );
  
  /////////////////////////////////////////////////
  // Analysis functions
  void ProcessCosmics();
  void ProcessBeam();
  /////////////////////////////////////////////////
  // Get/Set function to change something inside this class
  void SetCdcOupoutDir( std::string dir ); //output_cdb_dir_
  void SetQaRootOutputDir( std::string dir ); // output_qa_root_path_
  void SetQaPdfOutputDir( std::string dir ); // output_qa_pdf_path_ 

  
  /////////////////////////////////////////////////
  // Print function to show the status
  void Print();
  
  /////////////////////////////////////////////////
  // Output function
  void WriteResults();
};


#ifndef InttClassifier_cc
#include "InttClassifier.cc"
#endif
