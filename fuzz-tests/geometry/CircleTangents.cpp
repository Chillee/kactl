#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../../content/geometry/circleTangents.h"
#include "../../content/geometry/lineDistance.h"
#include "../utilities/randGeo.h"

typedef Point<double> P;

vector<P> poly;
int N;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    const int lim = 5;
    for (int i = 0; i < 1000000; i++) {
        P c1 = randPt(5), c2 = randPt(5);
        double r1 = rand()%5, r2 = rand()%5;
        for (auto sgn: {-1, 1}) {
            auto tans = tangents(c1, r1, c2, r2);

            if (tans.size() ==1) {
                assert((tans[0].first -tans[0].second).dist() < 1e-8);
                assert(abs((tans[0].first-c1).dist() - r1) < 1e-8);
                assert(abs((tans[0].first-c2).dist() - r2) < 1e-8);
            } else if (tans.size() == 2) {
                for (auto l: tans) {
                    assert(abs(abs(lineDist(l.first, l.second, c1))-r1) < 1e-8);
                    assert(abs(abs(lineDist(l.first, l.second, c2))-r2) < 1e-8);
                }
            }

        }
    }
    cout<<"Tests passed!"<<endl;
}
