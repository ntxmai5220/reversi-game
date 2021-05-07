#include <iostream>
#include <vector>

using namespace std;

typedef struct point
{
    int x; // toa do hang
    int y; // toa do cot
} toa_do;

typedef vector<vector<int>> ban_co;
vector<toa_do> gen_col_and_row(toa_do check, ban_co& bc, int player, int find);
vector<toa_do> gen_xien_phai(toa_do check, ban_co& bc, int player, int find);
vector<toa_do> gen_xien_trai(toa_do check, ban_co& bc, int player, int find);

void print_ban_co(ban_co bc)
{
    int kich_thuoc = bc.size();
    cout << "  " ;
    for(int i = 0; i < kich_thuoc; i++)
        cout << i << " ";
    for(int i = 0; i < kich_thuoc; i++)
    {
        cout << endl;
        cout << i << " ";
        for(int j = 0; j < kich_thuoc; j++)
        {
            if(bc[i][j] == 0)
                cout << "- ";
            else if(bc[i][j] == -1)
                cout << "X ";
            else
                cout << "O ";
        }
    }
    cout << endl;
}

ban_co init_ban_co(int _size) // size la so chan
{
    ban_co bc(_size, vector<int>(_size));
    int i = _size/2 - 1;
    bc[i][i] = -1; bc[i][i+1] = 1;
    bc[i+1][i] = 1; bc[i+1][i+1] = -1;
    return bc;
}


vector<toa_do> generate_valid_moves(ban_co bc, int player)
{
    vector<toa_do> kq;
    //TODO
    int size = bc.size();
    vector<toa_do> player_locations;
    for (int i=0;i<size;i++){
        for (int j=0;j<size;j++){
            if (bc[i][j]==player){
                toa_do tmp;
                tmp.x=i;
                tmp.y=j;
                player_locations.push_back(tmp);
            }
        }
    }
    for (toa_do item : player_locations){
        //cout <<  item.x << ", " << item.y  << endl;
        vector<toa_do> add = gen_col_and_row(item,bc,player,0);
        //print(add);
        kq.insert(kq.end(),add.begin(),add.end());
        add = gen_xien_phai(item,bc,player,0);
        //print(add);
        kq.insert(kq.end(),add.begin(),add.end());
        add = gen_xien_trai(item,bc,player,0);
        //print(add);
        kq.insert(kq.end(),add.begin(),add.end());
    }    
   // print_valid_moves(kq,player);
    return kq;
};

void play_moves(ban_co& bc, int player, toa_do vitri)
{
    //TODO
    ///cout<<"play move ne"<<endl;
    vector<toa_do> check = gen_col_and_row(vitri, bc, player, player);
    check = gen_xien_phai(vitri, bc, player, player);
    check = gen_xien_trai(vitri, bc, player, player);
    //bc[vitri.x][vitri.y] = player;
    return;
}

int main()
{
    ban_co bc = init_ban_co(10);
    print_ban_co(bc);

    vector<toa_do> moves = generate_valid_moves(bc, -1);
    for (toa_do item : moves)
        cout << "(" << item.x << ", " << item.y << ")" << endl;

    return 0;
}


vector<toa_do> gen_col_and_row(toa_do check, ban_co& bc, int player, int find)
{
    int x=check.x;//5
    int y=check.y;//3
    vector<toa_do> kq;
    int size = bc.size();
    if (x>0 && bc[x-1][y] == player * (-1)){//tren
        for(int i=x-1;i>=0;i--){
            if (bc[i][y]==find){
                if(player==find){
                    //cout<< i <<x <<endl;
                    for(int j=i+1;j<=x;j++) bc[j][y]=player;
                }
                else{
                    toa_do a={i,y};
                    kq.push_back(a);
                }
                
                break;
            }
            else if (bc[i][y]==player || (bc[i][y]==0 && player==find)) break;
        }
    }
    if (y>0 && bc[x][y-1] == player * (-1)){//trai
        for(int i=y-1;i>=0;i--){
            if (bc[x][i]==find){
                if(player==find){
                    //cout<< i <<y <<endl;
                    for(int j=i+1;j<=y;j++) bc[x][j]=player;
                }
                else{
                    toa_do a={x,i};
                    kq.push_back(a);
                }
                break;
            }
            else if (bc[x][i]==player || (bc[x][i]==0 && player==find)) break;
        }
    }
    if (x<size-1 && bc[x+1][y] == player * (-1)){//duoi
        for(int i=x+1;i<size;i++){
            if (bc[i][y]==find){
                if(player==find){
                    //cout<< i <<x <<y<<endl;
                    for(int j=i-1;j>=x;j--) bc[j][y]=player;
                }
                else{
                    toa_do a={i,y};
                    kq.push_back(a);
                }
                
                break;
            }
            else if (bc[i][y]==player || (bc[i][y]==0 && player==find)) break;
        }
    }
    if (y<size-1 && bc[x][y+1] == player * (-1)){//phai
        for(int i=y+1;i<size;i++){
            if (bc[x][i]==find){
                if(player==find){
                    //cout<< i <<y <<endl;
                    for(int j=i-1;j>=y;j--) bc[x][j]=player;
                }
                else{
                    toa_do a={x,i};
                    kq.push_back(a);
                }
                break;
            }
            else if (bc[x][i]==player || (bc[x][i]==0 && player==find)) break;
        }
    }
    return kq;
};
/*
    cout << "X "; //-1
    cout << "O "; //1
*/
vector<toa_do> gen_xien_phai(toa_do check, ban_co& bc, int player, int find)
{
    int x=check.x;//5
    int y=check.y;//3
    vector<toa_do> kq;
    int size = bc.size();
    if (x>0 && y > 0 && bc[x-1][y-1]==player*(-1)){
        int i=1;
        do{
            if (bc[x-i][y-i]==find){
                if(player==find){
                
                    for(int j=0;j<=i;j++) bc[x-j][y-j]=player;
                }
                else{
                    toa_do a={x-i,y-i};
                    kq.push_back(a);
                }
                break;
            }
            else if (bc[x-i][y-i]==player || (bc[x-i][y-i]==0 && player==find)) break;
            i++;
        }while(x-i>=0 && y-i>=0);
    }

    if (x<size - 1 && y <size -1 && bc[x+1][y+1]==player*(-1)){
        int i=1;
        do{
            if (bc[x+i][y+i]==find){
                if(player==find){
                  
                    for(int j=0;j<=i;j++) bc[x+j][y+j]=player;
                }
                else{
                    toa_do a={x+i,y+i};
                    kq.push_back(a);
                }
                break;
            }
            else if (bc[x+i][y+i]==player || (bc[x+i][y+i]==0 && player==find)) break;
            i++;
        }while(x+i<size && y+i<size);
    }
    return kq;
};

vector<toa_do> gen_xien_trai(toa_do check, ban_co& bc, int player, int find)
{
    int x=check.x;//5
    int y=check.y;//3
    vector<toa_do> kq;
    int size = bc.size();
    if (x<size-1 && y>0 && bc[x+1][y-1]==player*(-1)){ //goc duoi trai
        int i=1;
        do{
            if (bc[x+i][y-i]==find){
                if(player==find){
                 
                    for(int j=0;j<=i;j++) bc[x+j][y-j]=player;
                }
                else{
                    toa_do a={x+i,y-i};
                    kq.push_back(a);
                }
                break;
            }
            else if (bc[x+i][y-i]==player || (bc[x+i][y-i]==0 && player==find)) break;
            i++;
        }while(x+i<size && y-i >= 0);
    }

    if (x>0 && y <size-1&& bc[x-1][y+1]==player*(-1)){//goc tren phai
        int i=1;
        do{
            if (bc[x-i][y+i]==find){
                if(player==find){
                  
                    for(int j=0;j<=i;j++) bc[x-j][y+j]=player;
                }
                else{
                    toa_do a={x-i,y+i};
                    kq.push_back(a);
                }
                break;
            }
            else if (bc[x-i][y+i]==player || (bc[x-i][y+i]==0 && player==find)) break;
            i++;
        }while(x-i>=0 && y+i<size);
    }
    return kq;
};

