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
    vector<int> history[60];

public:
    void initial(){
        successnum=0;totalnum=0;
        for(int i=0;i<60;i++){
            history[i].clear();
        }

    }
    predict(){
        initial();
    }
    bool predictit(int type){
        int cnt=0;
        for(int i=0;i<5&&i<history[type].size();i++){
           cnt+=history[type][i];
        }
        if(cnt<0)return false;
        else return true;
    }
    void record_history(int type,bool result,bool is_suc){
        if(result==true){
            if(history[type].size()<5)history[type].push_back(1);
            else{
                for(int i=1;i<5;i++){
                    history[type][i-1]=history[type][i];
                }
                history[type][4]=1;
            }
        }
        else{
            if(history[type].size()<10)history[type].push_back(-1);
            else{
                for(int i=1;i<5;i++){
                    history[type][i-1]=history[type][i];
                }
                history[type][4]=-1;
            }
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
