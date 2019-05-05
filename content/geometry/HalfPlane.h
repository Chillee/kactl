
/**
 * Author: chilli
 * Date: 2019-05-05
 * License: CC0
 * Source: https://github.com/zimpha/algorithmic-library/blob/master/computational-geometry/polygon.cc
 * Description: Computes the intersection of a set of half-planes.
 * Time: O(n \log n)
 * Status: fuzz-tested, submitted on https://maps19.kattis.com/problems/marshlandrescues
 * Usage:
 */
#pragma once

#include "Point.h"
#include "sideOf.h"
#include "lineIntersection.h"

typedef Point<double> P;
typedef array<P, 2> Line;
#define sp(a) a[0], a[1]
#define ang(a) atan2((a[1] - a[0]).y, (a[1] - a[0]).x)

int angDiff(Line a, Line b) { return sgn(ang(a) - ang(b)); }
bool cmp(Line a, Line b) {
	auto s = angDiff(a, b);
	return s == 0 ? sideOf(sp(b), a[0]) >= 0 : s < 0;
}
vector<P> halfPlaneIntersection(vector<Line> vs) {
	sort(all(vs), cmp);
	vector<Line> deq(sz(vs) + 5);
	vector<P> ans(sz(vs) + 5);
	deq[0] = vs[0];
	int ah = 0, at = 0;
	for (int i = 1; i < sz(vs); ++i) {
		if (angDiff(vs[i], vs[i - 1]) == 0) continue;
		while (ah<at && sideOf(sp(vs[i]),ans[at-1]) < 0) at--;
		while (ah<at && sideOf(sp(vs[i]),ans[ah]) < 0) ah++;
		ans[at++] = lineInter(sp(deq[at]), sp(vs[i])).second;
		deq[at] = vs[i];
	}
	while (ah<at && sideOf(sp(deq[ah]),ans[at-1]) < 0) at--;
	while (ah<at && sideOf(sp(deq[at]),ans[ah]) < 0) ah++;
	ans[at++] = lineInter(sp(deq[ah]), sp(deq[at])).second;
	return {ans.begin() + ah, ans.begin() + at};
}
