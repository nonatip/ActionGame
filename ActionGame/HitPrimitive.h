#ifndef __HIT_PRIMITIVE_H__
#define __HIT_PRIMITIVE_H__

#include <math.h>

#define _OX_EPSILON_	0.000001f	// 誤差

// 3成分float
struct Float3 {
	float x, y, z;

	Float3() {}
	Float3(float x, float y, float z) : x(x), y(y), z(z) {}
	~Float3() {}

	Float3 operator +(const Float3 &r) const {
		return Float3(x + r.x, y + r.y, z + r.z);
	}

	Float3 operator -(const Float3 &r) const {
		return Float3(x - r.x, y - r.y, z - r.z);
	}

	Float3 operator -() const {
		return Float3(x * -1.0f, y * -1.0f, z * -1.0f);
	}

	Float3 operator *(const Float3 &r) const {
		return Float3(x * r.x, y * r.y, z * r.z);
	}

	Float3 operator /(const Float3 &r) const {
		return Float3(x / r.x, y / r.y, z / r.z);
	}

	Float3 operator *(float r) const {
		return Float3(x * r, y * r, z * r);
	}

	Float3 operator /(float r) const {
		return Float3(x / r, y / r, z / r);
	}

	friend Float3 operator *(float l, const Float3 &r) {
		return Float3(r.x * l, r.y * l, r.z * l);
	}

	friend Float3 operator /(float l, const Float3 &r) {
		return Float3(r.x / l, r.y / l, r.z / l);
	}

	float dot(const Float3 &r) const {
		return x * r.x + y * r.y + z * r.z;
	}

	Float3 cross(const Float3 &r) const {
		return Float3(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.x);
	}

	float length() const {
		return sqrtf(lengthSq());
	}

	float lengthSq() const {
		return x * x + y * y + z * z;
	}

	void norm() {
		const float len = length();
		if (len > 0.0f) {
			x /= len;
			y /= len;
			z /= len;
		}
	}

	Float3 getNorm() const {
		const float len = length();
		if (len > 0.0f) {
			return Float3(x / len, y / len, z / len);
		}
		return Float3(0.0f, 0.0f, 0.0f);
	}

	// ∠p1p2p3は鋭角？
	bool isSharpAngle(const Float3 &r) {
		return (dot(r) >= 0.0f);
	}
};


// 点
typedef Float3 Point;

// ベクトル
struct Vec3 : public Float3 {
	Vec3() {}
	Vec3(float x, float y, float z) : Float3(x, y, z) {}
	Vec3(const Float3 &r) : Float3(r) {}
	~Vec3() {}

	Vec3& operator =(const Float3 &r) {
		x = r.x;
		y = r.y;
		z = r.z;
		return *this;
	}

	// 標準化
	void norm() {
		const float len = length();
		if (len > 0.0f) {
			x /= len;
			y /= len;
			z /= len;
		}
	}

	// 垂直関係にある？
	bool isVertical(const Vec3 &r) const {
		float d = dot(r);
		return (-_OX_EPSILON_ < d && d < _OX_EPSILON_);	// 誤差範囲内なら垂直と判定
	}

	// 平行関係にある？
	bool isParallel(const Vec3 &r) const {
		float d = cross(r).lengthSq();
		return (-_OX_EPSILON_ < d && d < _OX_EPSILON_);	// 誤差範囲内なら平行と判定
	}

	// 鋭角関係？
	bool isSharpAngle(const Vec3 &r) const {
		return (dot(r) >= 0.0f);
	}
};


// 直線
struct Line {
	Point p;
	Vec3 v;		// 方向ベクトル
	Line() : p(0.0f, 0.0f, 0.0f), v(1.0f, 0.0f, 0.0f) {}
	Line(const Point &p, const Vec3 &v) : p(p), v(v) {}
	~Line() {}

	// 点上の座標を取得
	//  ベクトルに掛け算する係数
	Point getPoint(float t) const {
		return p + t * v;
	}

	// 点と直線の最短距離
	// p : 点
	// l : 直線
	// h : 点から下ろした垂線の足（戻り値）
	// t :ベクトル係数（戻り値）
	// 戻り値: 最短距離
	float calcPointLineDist(const Point &p, const Line &l, Point &h, float &t) {

		float lenSqV = l.v.lengthSq();
		t = 0.0f;
		if (lenSqV > 0.0f)
			t = l.v.dot(p - l.p) / lenSqV;

		h = l.p + t * l.v;
		return (h - p).length();
	}

	// 2直線の最短距離
	// l1 : L1
	// l2 : L2
	// p1 : L1側の垂線の足（戻り値）
	// p2 : L2側の垂線の足（戻り値）
	// t1 : L1側のベクトル係数（戻り値）
	// t2 : L2側のベクトル係数（戻り値）
	// 戻り値: 最短距離
	float calcLineLineDist(const Line &l1, const Line &l2, Point &p1, Point &p2, float &t1, float &t2) {

		// 2直線が平行？
		if (l1.v.isParallel(l2.v) == true) {

			// 点P11と直線L2の最短距離の問題に帰着
			float len = calcPointLineDist(l1.p, l2, p2, t2);
			p1 = l1.p;
			t1 = 0.0f;

			return len;
		}

		// 2直線はねじれ関係
		float DV1V2 = l1.v.dot(l2.v);
		float DV1V1 = l1.v.lengthSq();
		float DV2V2 = l2.v.lengthSq();
		Vec3 P21P11 = l1.p - l2.p;
		t1 = (DV1V2 * l2.v.dot(P21P11) - DV2V2 * l1.v.dot(P21P11)) / (DV1V1 * DV2V2 - DV1V2 * DV1V2);
		p1 = l1.getPoint(t1);
		t2 = l2.v.dot(p1 - l2.p) / DV2V2;
		p2 = l2.getPoint(t2);

		return (p2 - p1).length();
	}

	// ∠p1p2p3は鋭角？
	bool isSharpAngle(const Point &p1, const Point &p2, const Point &p3) {
		return (p1 - p2).isSharpAngle(p3 - p2);
	}
};


// 線分
struct Segment : public Line {

	Segment() {}
	Segment(const Point &p, const Vec3 &v) : Line(p, v) {}
	Segment(const Point &p1, const Point &p2) : Line(p1, p2 - p1) {}

	// 終点を取得
	Float3 getEndPoint() const {
		return p + v;
	}

	// 点と線分の最短距離
	// p : 点
	// seg : 線分
	// h : 最短距離となる端点（戻り値）
	// t : 端点位置（ t < 0: 始点の外, 0 <= t <= 1: 線分内, t > 1: 終点の外 ）
	// 戻り値: 最短距離
	float calcPointSegmentDist(const Point &p, const Segment &seg, Point &h, float &t) {

		const Point e = seg.getEndPoint();

		// 垂線の長さ、垂線の足の座標及びtを算出
		float len = calcPointLineDist(p, Line(seg.p, e - seg.p), h, t);

		if (isSharpAngle(p, seg.p, e) == false) {
			// 始点側の外側
			h = seg.p;
			return (seg.p - p).length();
		}
		else if (isSharpAngle(p, e, seg.p) == false) {
			// 終点側の外側
			h = e;
			return (e - p).length();
		}

		return len;
	}

	// 0～1の間にクランプ
	void clamp01(float &v) {
		if (v < 0.0f)
			v = 0.0f;
		else if (v > 1.0f)
			v = 1.0f;
	}

	// 2線分の最短距離
	// s1 : S1(線分1)
	// s2 : S2(線分2)
	// p1 : S1側の垂線の足（戻り値）
	// p2 : S2側の垂線の足（戻り値）
	// t1 : S1側のベクトル係数（戻り値）
	// t2 : S2側のベクトル係数（戻り値）
	// 戻り値: 最短距離
	float calcSegmentSegmentDist(const Segment &s1, const Segment &s2, Point &p1, Point &p2, float &t1, float &t2) {

		// S1が縮退している？
		if (s1.v.lengthSq() < _OX_EPSILON_) {
			// S2も縮退？
			if (s2.v.lengthSq() < _OX_EPSILON_) {
				// 点と点の距離の問題に帰着
				float len = (s2.p - s1.p).length();
				p1 = s1.p;
				p2 = s2.p;
				t1 = t2 = 0.0f;
				return len;
			}
			else {
				// S1の始点とS2の最短問題に帰着
				float len = calcPointSegmentDist(s1.p, s2, p2, t2);
				p1 = s1.p;
				t1 = 0.0f;
				clamp01(t2);
				return len;
			}
		}

		// S2が縮退している？
		else if (s2.v.lengthSq() < _OX_EPSILON_) {
			// S2の始点とS1の最短問題に帰着
			float len = calcPointSegmentDist(s2.p, s1, p1, t1);
			p2 = s2.p;
			clamp01(t1);
			t2 = 0.0f;
			return len;
		}

		/* 線分同士 */

		// 2線分が平行だったら垂線の端点の一つをP1に仮決定
		if (s1.v.isParallel(s2.v) == true) {
			t1 = 0.0f;
			p1 = s1.p;
			float len = calcPointSegmentDist(s1.p, s2, p2, t2);
			if (0.0f <= t2 && t2 <= 1.0f)
				return len;
		}
		else {
			// 線分はねじれの関係
			// 2直線間の最短距離を求めて仮のt1,t2を求める
			float len = calcLineLineDist(s1, s2, p1, p2, t1, t2);
			if (
				0.0f <= t1 && t1 <= 1.0f &&
				0.0f <= t2 && t2 <= 1.0f
				) {
				return len;
			}
		}

		// 垂線の足が外にある事が判明
		// S1側のt1を0～1の間にクランプして垂線を降ろす
		clamp01(t1);
		p1 = s1.getPoint(t1);
		float len = calcPointSegmentDist(p1, s2, p2, t2);
		if (0.0f <= t2 && t2 <= 1.0f)
			return len;

		// S2側が外だったのでS2側をクランプ、S1に垂線を降ろす
		clamp01(t2);
		p2 = s2.getPoint(t2);
		len = calcPointSegmentDist(p2, s1, p1, t1);
		if (0.0f <= t1 && t1 <= 1.0f)
			return len;

		// 双方の端点が最短と判明
		clamp01(t1);
		p1 = s1.getPoint(t1);
		return (p2 - p1).length();
	}
};

// 球
struct Sphere {
	Point p;
	float r;	// 半径
	Sphere() : p(0.0f, 0.0f, 0.0f), r(0.5f) {}
	Sphere(const Point &p, float r) : p(p), r(r) {}
	~Sphere() {}

	// 球同士の当たり判定
	// s1：p1(中心点1)
	// s2：p2(中心点2)
	// 戻り値：衝突していたらtrue
	bool colSphereSphere(const Sphere &s1, const Sphere &s2)
	{
		float d = (s1.p - s2.p).length();
		return (d <= s1.r + s2.r);
	}
};

// カプセル
struct Capsule :public Segment {
	Segment s;
	float r;	// 半径
	Capsule() : r(0.5f) {}
	Capsule(const Segment &s, float r) : s(s), r(r) {}
	Capsule(const Point &p1, const Point &p2, float r) : s(p1, p2), r(r) {}
	~Capsule() {}

	// カプセル同士の衝突判定
	// c1 : S1(線分1)
	// c2 : S2(線分2)
	// 戻り値：衝突していたらtrue
	bool colCapsuleCapsule(const Capsule &c1, const Capsule &c2) {
		Point p1, p2;
		float t1, t2;
		float d = calcSegmentSegmentDist(c1.s, c2.s, p1, p2, t1, t2);
		return (d <= c1.r + c2.r);
	}
};

// AABB
struct AABB {
	Point p;	// 中心点
	Float3 hl;	// 各軸の辺の長さの半分
	AABB() {}
	AABB(const Point &p, const Float3 &hl) : p(p), hl(hl) {}

	// 辺の長さを取得
	float lenX() const { return hl.x * 2.0f; };
	float lenY() const { return hl.y * 2.0f; };
	float lenZ() const { return hl.z * 2.0f; };
	float len(int i) {
		return *((&hl.x) + i) * 2.0f;
	}
};

#endif