#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
//-----States-----
enum class State { kOpen,kObstacle,kClosed  };
//------Directions_in_INT------
int delta[4][2]={{-1,0},{1,0},{0,1},{0,-1}};
//--------Direction_in_Char-----
string delta_char[4]={"W","E","S","N"};
//--------toString--------
string toString(int x,int y){
    string s;
    s=to_string(x);
    s+=" ";
    s+=to_string(y);
    return s;
}
//-------------CheckCell------------
    bool CheckCell(int row,int col,vector<vector<State>>&grid){
       bool col_on_map= col>=0&&col<grid[0].size();
       bool row_on_map= row>=0&&row<grid.size();
       //if(grid[x2+1][y2-1]==State::kObstacle){cerr<<"1"<<'\n';}
       if(col_on_map&&row_on_map&&grid[row][col]==State::kOpen){
          cerr<<row<<" "<<col<<'\n';
        return true;         
       }
       else return false;
    }
//-------------Starting_Location-------------    
    string starting_point(vector<vector<State>>&grid){
       for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(CheckCell(i,j,grid)){
                    grid[i][j]=State::kClosed;
                    return toString(i,j);
                }
            }
        }
    }
//-----------Order------------
    string order(string opponentOrders){
        istringstream order(opponentOrders);
        string move,direction,AND,action;
        while(order>>action){
         if(action=="MOVE"){
            order>>direction;
            return direction;
          }
        }
    }
//-----------Directions------------
    //void direct(string opponentOrders){
     //   string enemy_move=order(opponentOrders);
        
        //cerr<<direction<<'\n';
   // }
    string initial_move(int col,int row,vector<vector<State>>&grid,
        string opponentOrders,vector<vector<State>>&clean_grid){
        //grid[x][y]=State::kClosed;
        if(opponentOrders=="NA"){
         for(int i=0;i<4;i++){
          int col2=col+delta[i][0];
          int row2=row+delta[i][1];         
          if(CheckCell(row2,col2,grid)) {             
             //cerr<<x2<<" "<<y2<<endl;
             return "MOVE " + delta_char[i]; }
          }
        }
        else{         
          for(int i=0;i<4;i++){
           int col2=col+delta[i][0];
           int row2=row+delta[i][1];           
           if(CheckCell(row2,col2,grid)){
             //cerr<<x2<<" "<<y2<<endl;
             return "MOVE " + delta_char[i]; 
             }
          }        
            //if(i==4)            
        }
        grid=clean_grid;
        return "SURFACE";
    }
//-------------MAIN------------------    
int main()
{
    int width;
    int height;
    int myId;
    vector<vector<int>> coords;
    vector<vector<State>> grid{};
    cin >> width >> height >> myId; cin.ignore();
    for (int i = 0; i < height; i++) {
        string line;
        getline(cin, line);
        //cerr<<line<<'\n';
        istringstream row(line);
        char x;
        vector<int>points;
        vector<State> state;
        
        while(row>>x){
            //cerr<<x<<'\n';                         
            if(x=='.'){
             points.push_back(0);
             state.push_back(State::kOpen);
            }
            else{
             points.push_back(1);             
             state.push_back(State::kObstacle);
            }
        }
        coords.push_back(points); 
        grid.push_back(state);
        points.clear();
        state.clear();
    }

   /*       
//------Print_Map--------
    for(auto i : coords){
     for(auto j:i){
        cerr<<j;
     }
    cerr<<"\n";
    }
    
//    --------Print Grid--------- 
    for(auto i : grid){
     for(auto j:i){
        if(j==State::kObstacle)
         cerr<<1;
        else
         cerr<<0;
     }
    cerr<<"\n";
    }    
    cerr<<coords[0].size();
    */   
    vector<vector<State>>clean_grid=grid;
    if(coords[7][7]==0){
     cout<<"7 7"<<endl;
     grid[7][7]=State::kClosed;
    }
    else{
     cout<<starting_point(grid)<<endl;
    }
    
    // game loop
    while (1) {
        int x;
        int y;
        int myLife;
        int oppLife;
        int torpedoCooldown;
        int sonarCooldown;
        int silenceCooldown;
        int mineCooldown;
        cin >> x >> y >> myLife >> oppLife >> torpedoCooldown >> sonarCooldown >> silenceCooldown >> mineCooldown; 
        cin.ignore();
        string sonarResult;
        cin >> sonarResult; cin.ignore();
        string opponentOrders;
        getline(cin, opponentOrders);        
        cout<<initial_move(x,y,grid,opponentOrders,clean_grid)<<endl;
        grid[y][x]=State::kClosed;
    }
}
