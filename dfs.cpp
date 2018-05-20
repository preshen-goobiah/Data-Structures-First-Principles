#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <tuple>
#include <utility>

using namespace std;



class World
{
public:
    int rows, cols;
    vector<string> data;
    pair<int,int> start;
    pair<int,int> goal;
    vector< vector<pair<int,int>>> parent;
    
    vector<vector<bool>> visited;
    vector<string> dataCopy;
    
    //(rows, vector<pair<int,int>>(cols));
    
    
    
    /*
     World(istream &in){
     string line;
     // Read rows and cols
     in >> rows >> cols;
     // Throw away remaining \n
     getline(in, line);
     
     for(int r = 0; r < rows; r++){
     // Read the line
     getline(in, line);
     data.push_back(line);
     
     // Check for the start
     auto tmp = line.find('1');
     if(tmp != line.npos){
     start.first  = r;
     start.second = tmp;
     }
     // Check for the goal
     tmp = line.find('0');
     if(tmp != line.npos){
     goal.first  = r;
     goal.second = tmp;
     }
     }*/
    
    World(istream &in)
    {
        string line;
        in>>rows>>cols;
        
        
        getline(in,line);
        
        for (int i =0; i <rows; i++)
        {
            getline(in,line);
            data.push_back(line);
            
            auto tmp = line.find('1');
            if(tmp != line.npos)
            {
                start.first  = i;
                start.second = tmp;
            }
            
            tmp = line.find('0');
            if(tmp != line.npos)
            {
                goal.first  = i;
                goal.second = tmp;
            }
        }
        
        dataCopy = data;
        
        
    }
    
    
    int isValid(pair<int,int> coord)
    {
        int valid = 0;
        
        if(coord.first ==  rows-1)
        {
            valid = 1; // cant go down
        }
        else if (coord.second == 0 )
        {
            valid = 2; //cant go left
            
            
        }
        else if(coord.first == 0)
        {
            valid = 3; //cant go up
            
        }
        else if(coord.second == cols-1)
        {
            valid = 4; // cant go right
        }
        
        if (coord.first == 0 && coord.second == 0 )
        {
            valid = 5;
           
        }
        
        //test for rest of the corners for global implementation
        return valid;
    }
    
 
    
    
    
    void DFS()
    {
       
        vector< vector<pair<int,int>>> parent(rows, vector<pair<int,int>>(cols));
       
       
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                parent[i][j].first = -1;
                parent[i][j].second = -1;
            }
           
        }
 
       parent[start.first][start.second] = start;
    
        pair<int,int> curr;
        
        pair<int,int> down;
        pair<int,int> left;
        pair<int,int> up;
        pair<int,int> right;
        
        curr = start;
        bool noPath = false;
       
        
        while (curr != goal)
        {
            
            down.first = curr.first+1;
            down.second = curr.second;
            
            left.first = curr.first;
            left.second = curr.second-1;
            
            up.first = curr.first-1;
            up.second = curr.second;
            
            right.first = curr.first;
            right.second = curr.second+1;
            int newV = isValid(curr);
            
                if (data[down.first][down.second] != 'x' && parent[down.first][down.second].first == -1 &&
                    newV != 1)
                {
                    parent[down.first][down.second] = curr;
                    curr = down;
                    counter++;
                }
                else if(newV != 2 && newV != 5 && data[left.first][left.second] != 'x' && parent[left.first][left.second].first == -1)
                {
                    
                    
                    parent[left.first][left.second] = curr;
                    curr = left;
                    counter++;
                    
                    
                }
                
                else if(newV !=3 && newV!=5 && data[up.first][up.second] != 'x' && parent[up.first][up.second].first == -1)
                {
                    
                    parent[up.first][up.second] = curr;
                    curr = up;
                    counter++;
                    
                }
                
                else if(data[right.first][right.second] != 'x' && parent[right.first][right.second].first == -1 && newV !=4 )
                {
                    parent[right.first][right.second] = curr;
                    curr = right;
                    counter++;
                    
                }
                
                else
                {
                    //"Cornered in"
                    pair<int,int> tmp = parent[curr.first][curr.second];
                    parent[ curr.first][curr.second].second = -2;
                    curr = tmp;
                }
            
            if (curr.second == -2)
            {
                noPath = true;
                break;

            }
        }
    
      if (noPath == false)
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (parent[i][j].first != -1 && parent[i][j].second != -2)
                    {
                        data[i][j] = '*';
                    }
                    
                }
            }
            data[goal.first][goal.second] = '0';
             data[start.first][start.second] = '1';
                
                for (int j = 0; j < rows; j++)
                {
                     cout << data[j] << endl;
                    
                }
        }
        else
        {
            cout<<"No Path" << endl;
        }
        
    }
};

int main()
{
    
    World w(cin);
    w.DFS();
    
    return 0;
}

