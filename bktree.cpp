        #include <bits/stdc++.h>
        //#include "levenshtein.cpp" 
        #define int long long
        #define LEN 20
        #define d 2
        using namespace std;
         int get_distance(string s,string h ){
            if(s.empty()||h.empty()){
                return max(s.length(),h.length());
            }
            int n=s.length();
            int m=h.length();
            int dp[n+1][m+1];
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    dp[i][j]=INT_MAX;
                }
            }
            dp[0][0]=(s[0]!=h[0]);
            for(int i=1;i<m;i++){
                if(h[i]==s[0]){
                    dp[0][i]=i;
                }
                else{
                    dp[0][i]=min(i+1,dp[0][i-1]+1);
                }
            }
            for(int i=1;i<n;i++){
                if(s[i]==h[0]){
                    dp[i][0]=i;
                }
                else{
                    dp[i][0]=min(i+1,dp[i-1][0]+1);
                }
            }
            for(int i=1;i<n;i++){
                for(int j=1;j<m;j++){
                    dp[i][j]=min(dp[i-1][j]+1,dp[i][j-1]+1);
                    dp[i][j]=min(dp[i][j],dp[i-1][j-1]+1);
                    if(s[i]==h[j]){
                        dp[i][j]=min(dp[i][j],dp[i-1][j-1]);
                    }
                }
            }
            return dp[n-1][m-1];
        }
        struct Node{
            string word;
            struct Node *next[2*LEN];
            Node(string x):word(x)
            {
                for(int i=0;i<2*LEN;i++){
                    next[i]=0;
                }
            }
            Node() {}
        };
        Node *root=nullptr;
        void insert(Node *node,string s){
            int dis=get_distance(s,node->word);
            if(node->next[dis]==0){
                node->next[dis]=new Node(s);
                return ;
            }
            else{
                insert(node->next[dis],s);
            }
        }
        string search(Node *node,string query){
             if(node==nullptr){
                return "";
            }
            int dis=get_distance(query,node->word);
            if(dis<=d){
                return node->word;
            }
            /*d(node->word,query)=x
             d(node->word,child)=k
            d(query,child)<=d(query,node-word)+d(node-query,child);
            donc d(query,child)<=x+k
            avec une autre inégalité triangulaire renversée on obtient une 
            une borne inféieure
            donc  x-k<=d(query,child)<=x+k*
            donc    x-d<=k<=x+d;
            */
            else{
                int borne_sup=dis+d;
                int borne_inf=dis-d;
                string res="";
                for(int k=borne_inf;k<=borne_sup;k++){
                    if(node->next[k]==0){
                        continue;
                    }
                    string h=search(node->next[k],query);
                    if(h!=""){
                        res=h;
                    }
                }
                return res;
            }

        }
        vector<string>listofwords;
        void get_all_words(Node *node,string query){
             if(node==nullptr){
                return ;
            }
            int dis=get_distance(query,node->word);
            if(dis<=d){
                listofwords.push_back(node->word);
                return ;
            }
            /*d(node->word,query)=x
             d(node->word,child)=k
            d(query,child)<=d(query,node-word)+d(node-query,child);
            donc d(query,child)<=x+k
            avec une autre inégalité triangulaire renversée on obtient une 
            une borne inféieure
            donc  x-k<=d(query,child)<=x+k*
            donc    x-d<=k<=x+d;
            */
            else{
                int borne_sup=dis+d;
                int borne_inf=dis-d;
                for(int k=borne_inf;k<=borne_sup;k++){
                    if(node->next[k]==0){
                        continue;
                    }
                    get_all_words(node->next[k],query);
                    
                }
                return ;
            }

        }
        vector<string> charger(){
            vector<string>mots;
            ifstream fichier("mots.txt");
            if(!fichier){
                cout<<"impossible d'ouvrir"<<endl;
            }
            else{
                string ligne ;
                while(getline(fichier,ligne)){
                    if(!ligne.empty()){
                        mots.push_back(ligne);
                    }
                }
            }
            return mots;
        }
        void construire(vector<string>mots){
            for(auto u:mots){
                if(root==nullptr){
                    root=new Node(u);
                    continue;
                }
                else{
                    insert(root,u);
                }
            }
        }
        int32_t main(){
        ios_base::sync_with_stdio(false);cin.tie(NULL);
        vector<string>mots;
        mots=charger();
        construire(mots);
        string s;cin>>s;
        //cout<<search(root,s)<<endl;
        get_all_words(root,s);
        for(auto u:listofwords){
            cout<<u<<endl;
        }
        return 0;
        }
