/**
 * Source: https://cp-algorithms.com/string/suffix-array.html
 * Description: Builds suffix array for a string.
 * Note, that this algorithm only sorts the cycle shifts. 
 * We can generate the sorted order of the suffixes by appending a character that is smaller than
 * all other characters of the string, and sorting this resulting string by cycle shifts, 
 * e.g. by sorting the cycle shifts of s + \$.
 * Status: BOJ 9248
 */

vector<int> sort_cyclic_shifts(string &s) {
    int n = s.size();
    const int alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n)), pn(n), cn(n);
    // p[i] = locaction of ith string
    for(int i=0; i<n; i++)
        cnt[s[i]]++;
    for(int i=1; i<alphabet; i++)
        cnt[i] += cnt[i-1];
    for(int i=n-1; i>=0; i--)
        p[--cnt[s[i]]] = i;
    // c[i] = equivalence class of position i
    c[p[0]] = 0;
    int classes = 1;
    for(int i=1; i<n; i++) {
        if(s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }

    for(int h=0; (1<<h) < n; h++) {
        // preprocess pn
        for(int i=0; i<n; i++) {
            pn[i] = p[i] - (1<<h);
            if(pn[i] < 0)
                pn[i] += n;
        }
        
        // find next p by counting sort stably
        fill(cnt.begin(), cnt.end(), 0);
        for(int i=0; i<n; i++)
            cnt[c[i]]++;
        for(int i=1; i<classes; i++)
            cnt[i] += cnt[i-1];
        for(int i=n-1; i>=0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        // find next c
        cn[p[0]] = 0;
        classes = 1;
        for(int i=1; i<n; i++) {
            auto prv = make_pair(c[p[i]], c[(p[i] + (1<<h)) % n]), 
                 nxt = make_pair(c[p[i-1]], c[(p[i-1] + (1<<h)) % n]);
            
            if(prv != nxt)
                classes++;
            cn[p[i]] = classes - 1;
        }
        swap(cn, c);
    }
    return p;
}
vector<int> lcp_construction(string const& s, vector<int> const& p) {
    int n = s.size(), k = 0;
    // rank[i] = order of [string on location i]
    vector<int> rank(n), lcp(n-1);
    for(int i=0; i<n; i++)
        rank[p[i]] = i;
    
    for(int i=0; i<n; i++) {
        if(rank[i] == n-1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while(i+k<n && j+k<n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]] = k;
        if(k)
            k--;
    }
    return lcp;
}