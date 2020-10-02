#include<iostream>
#include<set>
#include<string>
#include<map>
#include<functional>
#include<algorithm>

using namespace std;

#define ll long long int
#define pb push_back

class Hexagon
{
public:
    string m_strName;   // stores the name of the hexagon
    pair<int,int> m_paCoordinates; // stores the x,y coordinates of the head vertex

    Hexagon()
    {}

    Hexagon(string strtemp, int xCo, int yCo)
    {
        m_strName = strtemp;
        m_paCoordinates.first = xCo;
        m_paCoordinates.second = yCo;
    }
    
    // Overloading operators as they will be needed in set data structure manipulation
    bool operator<(const Hexagon& a) const  // for insertion in set
    {
        if( (this->m_paCoordinates).first<a.m_paCoordinates.first)
            return true;
        else if((this->m_paCoordinates).first==a.m_paCoordinates.first)
        {
            if((this->m_paCoordinates).second<a.m_paCoordinates.second)
                return true;
            else
                return false;
        }
        else
            return false;    
    }
    bool operator<(const pair<int,int>& paTemp) const
    {
        if( (this->m_paCoordinates).first<paTemp.first)
            return true;
        else if((this->m_paCoordinates).first==paTemp.first)
        {
            if((this->m_paCoordinates).second<paTemp.second)
                return true;
            else
                return false;
        }
        else
            return false;    
    }
    bool operator==(const Hexagon& a) const
    {
        if(this->m_paCoordinates.first == a.m_paCoordinates.first &&
            this->m_paCoordinates.second == a.m_paCoordinates.second)
            return true;
        else return false;
    }

    bool operator==(const string& strTemp) const
    {
        if(this->m_strName == strTemp)
            return true;
        else return false;
    }

    bool operator==(const pair<int,int>& paTemp) const
    {
        if( (this->m_paCoordinates).first == paTemp.first &&
            (this->m_paCoordinates).second == paTemp.second )
            return true;
        else return false;
    }

    pair<int,int> getCounterHexCo(int Bor)
    {
        int x = m_paCoordinates.first;
        int y = m_paCoordinates.second;
        // Pattern of coordinates of neighbor's heads according to the border shared.
        if(Bor == 0)
            return {x,y+2};
        else if(Bor == 1)
            return {x+2,y+1};
        else if(Bor == 2)
            return {x+2,y-1};
        else if(Bor == 3)
            return {x,y-2};
        else if(Bor == 4)
            return {x-2,y-1};
        else
            return {x-2,y+1};
    }
};

class Cluster
{
public:
    Hexagon hexNULL;
    set<Hexagon> m_stHex;
    map<string, int> visited;

    bool CoorComp(Hexagon & hexTemp, pair<int,int> paTemp)
    {
        if(hexTemp.m_paCoordinates.first == paTemp.first &&
           hexTemp.m_paCoordinates.second == paTemp.second )
            return true;
        else return false;
    }
    Cluster()
    {
        hexNULL.m_strName = "NULL";
        (hexNULL.m_paCoordinates).first = -1e7; //initializing a NULL hexagon.
        (hexNULL.m_paCoordinates).second = -1e7;
        Hexagon firstHex("A", 0, 0);
        m_stHex.insert(firstHex);
    }

    // Returns Hexagon object with the specified name
    Hexagon getHexFromName(string strName)
    {
        auto it = m_stHex.begin();
        for(;it!=m_stHex.end();it++)
        {
            if((*it) == strName)
                break;
        }
        if(it == m_stHex.end())
            return hexNULL;
        else
            return (*it);
    }

    // Returns Hexagon object with the specified coordinates.
    Hexagon getHexFromCo(int xCo, int yCo)
    {
        pair<int,int> toFind = make_pair(xCo,yCo);
        auto it = find_if(m_stHex.begin(),m_stHex.end(), [&toFind](const Hexagon& x){ return ((x.m_paCoordinates.first == toFind.first) && (x.m_paCoordinates.second == toFind.second));});

        if( it != m_stHex.end() )
            return *it;
        else return hexNULL;
    }

    // Adds new Hexagon to the cluster
    void addNewHexagon(string strAlrPre, int Bor, string newHexName)
    {
        Hexagon hexAp = getHexFromName(strAlrPre);
        pair<int,int> newHexCo = hexAp.getCounterHexCo(Bor);
        Hexagon newHex(newHexName, newHexCo.first, newHexCo.second);
        m_stHex.insert(newHex);
        cout << "Hexagon " << newHexName << " added." << endl;
    }

    // Prints the name of the neighbors of a particular hexagon
    void getNeighborNames(string strCentre)
    {
        Hexagon hexCentre = getHexFromName(strCentre);
        Hexagon hexTemp;
        pair<int,int> tempNbrCo;
        cout << "Neighbors of " << strCentre << " are - " << endl;
        for(int i=0;i<6;i++)
        {
            tempNbrCo = hexCentre.getCounterHexCo(i);
            hexTemp = getHexFromCo(tempNbrCo.first, tempNbrCo.second);
            if(!(hexTemp==hexNULL))
            {
                cout << i << " " << hexTemp.m_strName << endl;
            }
        }
    }

    // Dfs to find whether all the hexagons are reachable from 1 node
    void dfs(Hexagon root)
    {
        visited[root.m_strName] = 1;
        pair<int,int> tempNbrCo;
        Hexagon hexTemp;
        for(int i=0;i<6;i++)
        {
            tempNbrCo = root.getCounterHexCo(i);
            hexTemp = getHexFromCo(tempNbrCo.first, tempNbrCo.second);
            if(visited[hexTemp.m_strName] == 0)
                dfs(hexTemp);
        }
    }

    // Checks whether all the hexagons are connected or not.
    bool IsConnected()
    {
        auto it = m_stHex.begin();
        Hexagon hexTemp, hexRoot;
        visited.clear();

        hexRoot = *it;

        for(;it!=m_stHex.end();it++)
        {
            hexTemp = *it;
            visited[hexTemp.m_strName] = 0; // initializing the visited map. 0 means not visited, 1 means visited.
        }

        
        dfs(hexRoot);

        bool ans = true;
        for(it=m_stHex.begin();it!=m_stHex.end();it++)
        {
            hexTemp = *it;
            if(visited[hexTemp.m_strName] == 0)
            {
                ans = false;
                break;
            }
        }

        return ans;
    }

    void RemoveHex(string strToRem) // removes the hexagon from the cluster
    {
        Hexagon hexToRem = getHexFromName(strToRem);
        m_stHex.erase(hexToRem);
        if(!IsConnected()){
            // case where cluster gets divided so we do not remove the hexagon
            m_stHex.insert(hexToRem);
            cout << "Hexagon " << strToRem << " did not get removed as it connects two hotspots." << endl;
        }
        else
            cout << "Hexagon " << strToRem << " got removed." << endl;
    }

};


int main()
{
    //freopen("in.txt","r",stdin);freopen("out.txt","w",stdout);
    
    Cluster clus;
    int type;

    cout << "Select the type of action you want to perform - " << endl
         << "1. Query the neighbors of a hexagon." << endl
         << "2. Add a hexagon to your cluster." << endl
         << "3. Remove a hexagon from your cluster." << endl
         << "4. Stop this program." << endl;
    while(true)
    {
        cin >> type;
        if(type == 1)
        {
            cout << "Please provide the hexagon of which you want the find the neighbors." << endl;
            string strCentre;
            cin >> strCentre;
            clus.getNeighborNames(strCentre);
        }
        else if(type == 2)
        {
            cout << "Please provide the name of the already present hexagon, it's connecting border and the name of the new hexagon." << endl;
            string strApHex,strNewHex;
            int Bor;
            cin >> strApHex >> Bor >> strNewHex;
            clus.addNewHexagon(strApHex,Bor,strNewHex);
        }
        else if(type == 3)
        {
            cout << "Please provide the name of the already present hexagon that you want to delete." << endl;
            string strToRem;
            cin >> strToRem;
            clus.RemoveHex(strToRem);
        }
        else break;
    }

    return 0;
}
