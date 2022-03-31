#include "QuadMatrix.h"
#include "AutoVectorizedQuadMatrixService.h"
#include "NotVectorizedQuadMatrixService.h"
#include "AVXVectorizedQuadMatrixService.h"



#define GREEN 0x02
#define RED 0x0C
#define WHITE 0x07
#define YELLOW 0x06

void changeConsoleColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | color));
}

int main() {
	srand(time(0));
	changeConsoleColor(WHITE);
	using namespace std::chrono;
	AutoVectorizedQuadMatrixService<double> autoVectorizedService = AutoVectorizedQuadMatrixService<double>();
	NotVectorizedQuadMatrixService<double> notVectorizedService = NotVectorizedQuadMatrixService<double>();
	AVXVectorizedQuadMatrixService<double> avxVectorizedService = AVXVectorizedQuadMatrixService<double>();

	QuadMatrix<double> a = QuadMatrix<double>(2, 2, 1, 1);
	QuadMatrix<double> b = QuadMatrix<double>(2, 2, 1, 1);
	QuadMatrix<double>* c = new QuadMatrix<double>(a.lines, b.columns, a.includedLines, b.includedColumns);
	QuadMatrix<double>* d = new QuadMatrix<double>(a.lines, b.columns, a.includedLines, b.includedColumns);
	a.fillWithRandomNumbers();
	b.fillWithRandomNumbers();	

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	c = notVectorizedService.multiplyMatrices(a, b);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	std::cout << "Without vectorization: ";
	changeConsoleColor(RED);
	std::cout << time_span.count() << " seconds.";
	std::cout << std::endl;

	changeConsoleColor(WHITE);
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	c = autoVectorizedService.multiplyMatrices(a, b);
	high_resolution_clock::time_point t4 = high_resolution_clock::now();
	duration<double> time_span2 = duration_cast<duration<double>>(t4 - t3);
	std::cout << "Auto vectorization: ";
	changeConsoleColor(YELLOW);
	std::cout << time_span2.count() << " seconds.";
	std::cout << std::endl;
	//c->printToConsole();

	changeConsoleColor(WHITE);
	high_resolution_clock::time_point t5 = high_resolution_clock::now();
	d = avxVectorizedService.multiplyMatrices(a, b);
	high_resolution_clock::time_point t6 = high_resolution_clock::now();
	duration<double> time_span3 = duration_cast<duration<double>>(t6 - t5);
	std::cout << "SSE vectorization: ";
	changeConsoleColor(GREEN);
	std::cout << time_span3.count() << " seconds.";
	std::cout << std::endl << std::endl;

	
	/*std::cout << std::endl;
	d->printToConsole();*/


	if (c->equals(d) != true) {
		changeConsoleColor(RED);
		std::cout << "Matrices are not the same :(" << std::endl;
	} else {
		changeConsoleColor(GREEN);
		std::cout << "Matrices are the same :)" << std::endl;
	}
	changeConsoleColor(WHITE);

	return 0;
}