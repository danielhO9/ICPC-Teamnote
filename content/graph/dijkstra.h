/**
 * Author: -
 * Date: -
 * License: -
 * Source: https://www.acmicpc.net/source/share/97a376e28b134aebbfc35322e1893fda 
 * Description: Computes shortest path from a single source vertex to all of the other vertices in a weighted digraph.
 * Time: $O(E\log V)$
 * Status: stress-tested
 */

const int MX = 2e5 + 5;
struct edge {
	int v, w;
	bool operator<(const edge &p) const{
		return w > p.w;
	}
};
vector<edge> adj[MX];
int dist[MX];

void dijkstra(int s) {
    memset(dist, 0x3f, sizeof dist);
	dist[s] = 0;
	priority_queue<edge> pq;
	pq.push({s, 0});
	while(!pq.empty()) {
		auto t = pq.top();
		int v = t.v, w = t.w;
		pq.pop();
		if(w > dist[v]) continue;
		for(auto p: adj[v]) {
			if(dist[p.v] > dist[v]+p.w) {
				dist[p.v] = dist[v]+p.w;
				pq.push({p.v, dist[p.v]});
			}
		}
	}
}