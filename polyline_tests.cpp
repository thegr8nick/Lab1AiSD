#include <gtest/gtest.h>
#include "polyline.cpp"
#include <stdexcept>
#include <cmath>
#include <iostream>

using namespace polyline;


TEST(FunctionsTests, PointTest) {
	Point<int> x;
	Point<int> y(1, 1);
	Point<int> z(x);
	Point<int> a = x;
	EXPECT_TRUE(x == z);
	EXPECT_TRUE(x == a);
}

TEST(FunctionsTests, Point2Test) {
	Point<double> point1(-2.2, 2.2);
	Point<double> point2(-1.1, 1.1);
	EXPECT_NEAR(len(point1, point2), 1.5, 0.1);
}

TEST(FunctionsTests, Point3Test) {
	Point<std::complex<double>> point1({1,1}, {2,2});
	Point<std::complex<double>> point2({1,7}, {7,1});
	EXPECT_NEAR(len(point1, point2), 5, 0.001);
}

TEST(FunctionsTests, PolylineTest) {
	Point<double> point1(1.1, 1.1);
	Polyline<double> line2(point1);
	Polyline<double> line3(5);
	Polyline<double> line4(line2);
	Polyline<double> line5(point1);
	Point<double> point2(2.2, 2.2);
	Point<double> point3(3.3, 3.3);
	line5.push_back(point2);
	line5.push_front(point3);
	line4 = line2;
	Polyline<double> line6 = line4 + line2;
	EXPECT_TRUE(line5[0] == point3);
	EXPECT_TRUE(line5[line5.get_size() - 1] == point2);
}
