        #include <bits/stdc++.h>
        #define int long long
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
            for(int i=0;i<m;i++){
                if(h[i]==s[0]){
                    dp[0][i]=i;
                }
                else{
                    dp[0][i]=min(i+1,dp[0][i-1]+1);
                }
            }
            for(int i=0;i<n;i++){
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
        int32_t main(){
        ios_base::sync_with_stdio(false);cin.tie(NULL);
        string s;cin>>s;
        string h;cin>>h;
        cout<<get_distance(s,h)<<endl;

        return 0;
        }
