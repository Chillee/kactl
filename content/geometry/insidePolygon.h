/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Returns true if p lies within the polygon. If p is on the edge
 * of the polygon, it returns false when strict is true. Answer is calculated
 * by counting the number of intersections between the polygon and a line going
 * from p to infinity in the positive x-direction. The algorithm uses products
 * in intermediate steps so watch out for overflow.
 * Time: O(n)
 * Status: fuzz-tested and Kattis problem pointinpolygon
 * Usage:
 * vector<P> v= {P{4,4}, P{1,2}, P{2,1}};
 * bool in = inPolygon(v, P{3, 3}, false);
 */
#pragma once

#include "Point.h"
#include "onSegment.h"
#include "SegmentDistance.h"

template<class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
	int cnt = 0, n = sz(p);
	rep(i,0,n) {
		P q = p[(i + 1) % n];
		if (onSegment(p[i], q, a)) return !strict;
		//or: if (segDist(p[i], q, a) <= eps) return !strict;
		cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * a.cross(p[i], q) > 0;
	}
	return cnt;
}
