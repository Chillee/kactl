/**
 * Author: Oleksandr Bacherikov, chilli
 * Date: 2019-05-05
 * License: CC0
 * Source: https://codeforces.com/blog/entry/48868
 * Description: Returns the two points with max distance on a convex hull (no duplicate/collinear points).
 * If input isn't a convex hull, call "convexHull" first.
 * Works with integers.
 * Status: Fuzz-tested, submitted on kattis roberthood
 */
#pragma once

array<P, 2> hullDiameter(vector<P> S) {
	int n = sz(S), j = n < 2 ? 0 : 1;
	pair<ll, array<P, 2>> res;
	rep(i,0,j)
		for (;; j = (j + 1) % n) {
			res = max(res, {(S[i] - S[j]).dist2(), {S[i], S[j]}});
			if ((S[(j + 1) % n] - S[j]).cross(S[i + 1] - S[i]) >= 0)
				break;
		}
	return res.second;
}
