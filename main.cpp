#include <iostream>

#include "include/Matrix/matrix_io.h"
#include "include/quaternion.h"
#include "include/quaternion_io.h"
#include "include/Matrix/rectangular_matrix.h"
#include "include/Matrix/square_matrix.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
#endif

  Quaternion first_items[] = {
      Quaternion(1.0, 0.0, 1.0, 0.0),
      Quaternion(2.0, 1.0, 0.0, 0.0),
      Quaternion(0.0, 1.0, 0.0, 1.0),
      Quaternion(3.0, 0.0, 0.0, 1.0)
  };

  Quaternion second_items[] = {
      Quaternion::identity(),
      Quaternion(0.0, 1.0, 0.0, 0.0),
      Quaternion(0.0, 0.0, 1.0, 0.0),
      Quaternion(0.0, 0.0, 0.0, 1.0)
  };

  SquareMatrix<Quaternion> first_matrix(first_items, 2);
  SquareMatrix<Quaternion> second_matrix(second_items, 2);

  SquareMatrix<Quaternion> sum = first_matrix + second_matrix;
  SquareMatrix<Quaternion> scaled = first_matrix * Quaternion(2.0, 0.0, 0.0, 0.0);

  std::cout << "Первая матрица кватернионов:\n" << first_matrix << '\n';
  std::cout << "Вторая матрица кватернионов:\n" << second_matrix << '\n';
  std::cout << "Сумма матриц:\n" << sum << '\n';
  std::cout << "Умножаем первую матрицу на скаляр (2, 0, 0, 0):\n" << scaled << '\n';
  std::cout << "Норма первой матрицы: " << first_matrix.norm() << "\n\n";

  RectangularMatrix<Quaternion> rectangular(first_items, 2, 2);
  rectangular.swap_rows(0, 1);
  rectangular.scale_column(0, Quaternion::identity());

  std::cout << "Прямоугольная матрица после перемещения строк:\n" << rectangular << '\n';

  return 0;
}
