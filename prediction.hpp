//
// Created by admin on 2019/7/11.
//

#ifndef RISCV5_PREDICTION_HPP
#define RISCV5_PREDICTION_HPP

#include <cstring>
#include <vector>


class predict{
private:
    int successnum,totalnum;
    vector<int> BEQ_his;
    vector<int> BNE_his;
    vector<int> BLT_his;
    vector<int> BGE_his;
    vector<int> BLTU_his;
    vector<int> BGEU_his;     //histories
public:

    predict(){
        successnum=0;totalnum=0;
        BEQ_his.clear();
        BNE_his.clear();
        BLT_his.clear();
        BGE_his.clear();
        BLTU_his.clear();
        BGEU_his.clear();
    }
    bool predictit(int type){
        int cnt=0;
        switch (type){
            case BEQ:
                for(int i=0;i<5&&i<BEQ_his.size();i++){
                    cnt+=BEQ_his[i];
                }
                if(cnt<0)return false;
                else return true;
            case BNE:
                for(int i=0;i<5&&i<BNE_his.size();i++){
                    cnt+=BNE_his[i];
                }
                if(cnt<0)return false;
                else return true;
            case BLT:
                for(int i=0;i<5&&i<BLT_his.size();i++){
                    cnt+=BLT_his[i];
                }
                if(cnt<0)return false;
                else return true;
            case BGE:
                for(int i=0;i<5&&i<BGE_his.size();i++){
                    cnt+=BGE_his[i];
                }
                if(cnt<0)return false;
                else return true;
            case BLTU:
                for(int i=0;i<5&&i<BLTU_his.size();i++){
                    cnt+=BLTU_his[i];
                }
                if(cnt<0)return false;
                else return true;
            case BGEU:
                for(int i=0;i<5&&i<BGEU_his.size();i++){
                    cnt+=BGEU_his[i];
                }
                if(cnt<0)return false;
                else return true;
        }
    }
    void record_history(int type,bool result,bool is_suc){
        switch(type){
            case BEQ:
                if(result==true){
                    if(BEQ_his.size()<5)BEQ_his.push_back(1);
                    else{
                        for(int i=1;i<5;i++)
                            BEQ_his[i-1]=BEQ_his[i];
                        BEQ_his[4]=1;
                    }
                }
                else{
                    if(BEQ_his.size()<5)BEQ_his.push_back(-1);
                    else{
                        for(int i=1;i<5;i++)
                            BEQ_his[i-1]=BEQ_his[i];
                        BEQ_his[4]=-1;
                    }
                }
                break;
            case BNE:
                if(result==true){
                    if(BNE_his.size()<5)BNE_his.push_back(1);
                    else{
                        for(int i=1;i<5;i++)
                            BNE_his[i-1]=BNE_his[i];
                        BNE_his[4]=1;
                    }
                }
                else{
                    if(BNE_his.size()<5)BNE_his.push_back(-1);
                    else{
                        for(int i=1;i<5;i++)
                            BNE_his[i-1]=BNE_his[i];
                        BNE_his[4]=-1;
                    }
                }
                break;
            case BLT:
                if(result==true){
                    if(BLT_his.size()<5)BLT_his.push_back(1);
                    else{
                        for(int i=1;i<5;i++)
                            BLT_his[i-1]=BLT_his[i];
                        BLT_his[4]=1;
                    }
                }
                else{
                    if(BLT_his.size()<5)BLT_his.push_back(-1);
                    else{
                        for(int i=1;i<5;i++)
                            BLT_his[i-1]=BLT_his[i];
                        BLT_his[4]=-1;
                    }
                }
                break;
            case BGE:
                if(result==true){
                    if(BGE_his.size()<5)BGE_his.push_back(1);
                    else{
                        for(int i=1;i<5;i++)
                            BGE_his[i-1]=BGE_his[i];
                        BGE_his[4]=1;
                    }
                }
                else{
                    if(BGE_his.size()<5)BGE_his.push_back(-1);
                    else{
                        for(int i=1;i<5;i++)
                            BGE_his[i-1]=BGE_his[i];
                        BGE_his[4]=-1;
                    }
                }
                break;
            case BLTU:
                if(result==true){
                    if(BLTU_his.size()<5)BLTU_his.push_back(1);
                    else{
                        for(int i=1;i<5;i++)
                            BLTU_his[i-1]=BLTU_his[i];
                        BLTU_his[4]=1;
                    }
                }
                else{
                    if(BLTU_his.size()<5)BLTU_his.push_back(-1);
                    else{
                        for(int i=1;i<5;i++)
                            BLTU_his[i-1]=BLTU_his[i];
                        BLTU_his[4]=-1;
                    }
                }
                break;
            case BGEU:
                if(result==true){
                    if(BGEU_his.size()<5)BGEU_his.push_back(1);
                    else{
                        for(int i=1;i<5;i++)
                            BGEU_his[i-1]=BGEU_his[i];
                        BGEU_his[4]=1;
                    }
                }
                else{
                    if(BGEU_his.size()<5)BGEU_his.push_back(-1);
                    else{
                        for(int i=1;i<5;i++)
                            BGEU_his[i-1]=BGEU_his[i];
                        BGEU_his[4]=-1;
                    }
                }
                break;

        }
        if(is_suc)
            ++successnum;
        ++totalnum;
    }
    void printpre(){
        cout<<"successnum= "<<successnum<<" totalnum= "<<totalnum<<'\n';
        cout<<" rate= "<< static_cast<double>(successnum)/totalnum<<'\n';
    }


};
#endif //RISCV5_PREDICTION_HPP
