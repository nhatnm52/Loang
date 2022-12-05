#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <vector>
#include <time.h>

using namespace std;
using namespace cv;

int main() {

	std::cout << "Image: ";
	string name;
	cin >> name;

	std::cout << "\nNum of round: ";
	int maxRound;
	cin >> maxRound;

	string namefile = "E:/Working/Loang/Input/" + name;

	Mat img = imread(namefile, IMREAD_ANYDEPTH);

	int col = img.cols;
	int row = img.rows;

	clock_t start = clock();

	int hull[60000];
	int hullIndex = 0;
	//<40k
	int newHull[80000];
	int newIndex = 0;
	//<60k
	int common[32768];
	int commonIndex = 0;
	//<20k

	//cout << "\n1\n";
	//First step
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (img.at<unsigned short>(Point(i, j)) == 0) {

				bool status = false; // beside not zero points or not
				bool conflict = false; //conflict or not
				unsigned short cur = 0; //current value of beside point

				if (i == 0) {
					if (j == 0) {
						//(0, 1)
						int m = i;
						int n = j + 1;
						unsigned short value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(1, 1)
						m += 1;
						//n += 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(1, 0)
						//m += 1;
						n -= 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}

					}
					else if (j == col - 1) {
						//(0, -1)
						int m = i;
						int n = j - 1;
						unsigned short value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(1, -1)
						m += 1;
						//n -= 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(1, 0)
						//m += 1;
						n += 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}

					}
					else {
						//(0, -1)
						int m = i;
						int n = j - 1;
						unsigned short value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(0, 1)
						//m -= 1;
						n += 2;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(1, 0)
						m += 1;
						n -= 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}

						//(1, 1)
						//m += 1;
						n += 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(1, -1)
						//m += 1;
						n -= 2;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
					}
				}
				else if (i == row - 1) {
					if (j == 0) {
						// (-1, 0)
						int m = i - 1;
						int n = j;
						unsigned short value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(-1, 1)
						//m = x - 1;
						n += 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(0, 1)
						m += 1;
						//n = y + 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}

					}
					else if (j == col - 1) {
						// (-1, 0)
						int m = i - 1;
						int n = j;
						unsigned short value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(-1, -1)
						//m = x - 1;
						n -= 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(0, -1)
						m += 1;
						//n = y - 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}

					}
					else {
						// (-1, 0)
						int m = i - 1;
						int n = j;
						unsigned short value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(0, 1)
						m += 1;
						n += 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(0, -1)
						//m = x;
						n -= 2;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}

						//(-1, -1)
						m -= 1;
						//n = y - 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(-1, 1)
						//m = x - 1;
						n += 2;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
					}
				}
				else {
					if (j == 0) {
						// (-1, 0)
						int m = i - 1;
						int n = j;
						unsigned short value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(1, 0)
						m += 2;
						//n = y;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(1, 1)
						//m = x + 1;
						n += 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(0, 1)
						m -= 1;
						//n = y + 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}

						//(-1, 1)
						m -= 1;
						//n = y + 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
					}
					else if (j == col - 1) {
						// (-1, 0)
						int m = i - 1;
						int n = j;
						unsigned short value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(1, 0)
						m += 2;
						//n = y;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(1, -1)
						//m = x + 1;
						n -= 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(0, -1)
						m -= 1;
						//n = y - 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(-1, -1)
						m -= 1;
						//n = y - 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}

					}
					else {
						// (-1, 0)
						int m = i - 1;
						int n = j;
						unsigned short value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(1, 0)
						m += 2;
						//n = y;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(0, 1)
						m -= 1;
						n += 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(0, -1)
						//m = x;
						n -= 2;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}

						//(-1, -1)
						m -= 1;
						//n = y - 1;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(1, 1)
						m += 2;
						n += 2;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(1, -1)
						//m = x + 1;
						n -= 2;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
						//(-1, 1)
						m -= 2;
						n += 2;
						value = img.at<unsigned short>(Point(m, n));
						if (value != 0) {
							status = true;
							if (cur == 0) {
								cur = value;
							}
							else {
								if (cur != value) {
									conflict = true;
									goto check;
								}
							}
						}
					}
				}

			check:
				if (conflict) {
					//add to common
					common[commonIndex++] = i;
					common[commonIndex++] = j;
				}
				else {
					if (status) {
						//add to change
						newHull[newIndex++] = i;
						newHull[newIndex++] = j;
						newHull[newIndex++] = cur;
						//changeIndex += 3;
						//add to hull
						hull[hullIndex++] = i;
						hull[hullIndex++] = j;
						//hullIndex += 2;
					}
				}
			}
		}
	}

	//std::cout << "\nRuning Time: " << (double)(clock() - start) / CLOCKS_PER_SEC;

	for (int i = 0; i < commonIndex; i += 2) {
		img.at<unsigned short>(Point(common[i], common[i + 1])) = 65535;
	}

	for (int i = 0; i < newIndex; i += 3) {
		img.at<unsigned short>(Point(newHull[i], newHull[i + 1])) = newHull[i + 2];
	}

	newIndex = 0;

	//Splash
	for (int k = 1; k < maxRound; k++) {
		//cout << k + 1 << "\n";
		for (int i = 0; i < hullIndex; i += 2) {
			int x = hull[i];
			int y = hull[i + 1];

			unsigned short value = img.at<unsigned short>(Point(x, y));
			unsigned short cur;

			if (x == 0) {
				if (y == 0) {
					//(0, 1)
					int m = x;
					int n = y + 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(1, 1)
					m += 1;
					//n += 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(1, 0)
					//m += 1;
					n -= 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
				}
				else if (y == col - 1) {
					//(0, -1)
					int m = x;
					int n = y - 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(1, -1)
					m += 1;
					//n -= 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(1, 0)
					//m += 1;
					n += 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
				}
				else {
					//(0, -1)
					int m = x;
					int n = y - 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(0, 1)
					//m -= 1;
					n += 2;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(1, 0)
					m += 1;
					n -= 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(1, 1)
					//m += 1;
					n += 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(1, -1)
					//m += 1;
					n -= 2;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
				}
			}
			else if (x == row - 1) {
				if (y == 0) {
					// (-1, 0)
					int m = x - 1;
					int n = y;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(-1, 1)
					//m = x - 1;
					n += 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(0, 1)
					m += 1;
					//n = y + 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
				}
				else if (y == col - 1) {
					// (-1, 0)
					int m = x - 1;
					int n = y;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(-1, -1)
					//m = x - 1;
					n -= 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(0, -1)
					m += 1;
					//n = y - 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
				}
				else {
					// (-1, 0)
					int m = x - 1;
					int n = y;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(0, 1)
					m += 1;
					n += 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(0, -1)
					//m = x;
					n -= 2;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(-1, -1)
					m -= 1;
					//n = y - 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(-1, 1)
					//m = x - 1;
					n += 2;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
				}
			}
			else {
				if (y == 0) {
					// (-1, 0)
					int m = x - 1;
					int n = y;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(1, 0)
					m += 2;
					//n = y;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(1, 1)
					//m = x + 1;
					n += 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(0, 1)
					m -= 1;
					//n = y + 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(-1, 1)
					m -= 1;
					//n = y + 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
				}
				else if (y == col - 1) {
					// (-1, 0)
					int m = x - 1;
					int n = y;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(1, 0)
					m += 2;
					//n = y;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(1, -1)
					//m = x + 1;
					n -= 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(0, -1)
					m -= 1;
					//n = y - 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(-1, -1)
					m -= 1;
					//n = y - 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
				}
				else {
					// (-1, 0)
					int m = x - 1;
					int n = y;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(1, 0)
					m += 2;
					//n = y;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(0, 1)
					m -= 1;
					n += 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(0, -1)
					//m = x;
					n -= 2;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(-1, -1)
					m -= 1;
					//n = y - 1;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(1, 1)
					m += 2;
					n += 2;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(1, -1)
					//m = x + 1;
					n -= 2;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
					//(-1, 1)
					m -= 2;
					n += 2;
					cur = img.at<unsigned short>(Point(m, n));
					if (cur == 0) {
						newHull[newIndex++] = m;
						newHull[newIndex++] = n;
						img.at<unsigned short>(Point(m, n)) = 65535 - value;
						//newIndex += 3;
					}
					else {
						if (cur > 32768) {
							if (cur != 65535 - value) {
								img.at<unsigned short>(Point(m, n)) = 65535;
							}
						}
					}
				}
			}

		}
		hullIndex = 0;

		for (int i = 0; i < newIndex; i += 2) {
			int m = newHull[i];
			int n = newHull[i + 1];
			unsigned short value = img.at<unsigned short>(Point(m, n));
			if (value == 65535) {
				common[commonIndex++] = m;
				common[commonIndex++] = n;
			}
			else {
				hull[hullIndex++] = m;
				hull[hullIndex++] = n;
				img.at<unsigned short>(Point(m, n)) = 65535 - value;
			}
		}

		newIndex = 0;

		if (hullIndex == 0) {
			break;
		}
	}

	for (int i = 0; i < commonIndex; i += 2) {
		img.at<unsigned short>(Point(common[i], common[i + 1])) = 0;
	}

	clock_t end = clock();

	std::cout << "\nRuning Time: " << (double)(end - start) / CLOCKS_PER_SEC;

	//string output = namefile + "_output.tif";

	//imwrite(output, img);

	Mat img2 = imread("E:/Working/Loang/Input/output" + name, IMREAD_ANYDEPTH);

	int count = 0;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (img.at<unsigned short>(Point(i, j)) != (img2.at<unsigned short>(Point(i, j)))) count++;
		}
	}

	std::cout << "\nDiffirences: " << count;

	imshow("Result: ", img);
	waitKey(0);

	return 0;
}