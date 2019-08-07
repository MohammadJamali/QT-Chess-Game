#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <stdexcept>

template<typename T>
class Matrix
{
    private:
        T** data_;
        int rows_;
        int cols_;

    public:
        Matrix(int rows, int cols, T initialize):
            rows_ (rows),
            cols_ (cols)
        {
            if (rows == 0 || cols == 0)
            {
                printf("Matrix constructor has 0 size");
                throw std::out_of_range("Matrix constructor has 0 size");
            }

            data_ = new T*[rows];

            for (int row = 0; row < rows; ++row)
            {
                data_[row] = new T[cols];

                for (int col = 0; col < cols; ++col)
                {
                    data_[row][col] = initialize;
                }
            }
        }

        void print()
        {
            printf("\n");

            for (int i = 0; i < 8; ++i)
            {
                for (int j = 0; j < 8; ++j)
                {
                    printf("%3d ", this->operator()(i, j));
                }

                printf("\n");
            }

            printf("\n");
        }

        //        ~Matrix()
        //        {
        //            if(data_ != 0 && data_ != nullptr)
        //                delete[] data_;
        //        }

        inline
        T& operator() (int row, int col)
        {
            if (row >= rows_ || col >= cols_)
                throw std::out_of_range(
                    std::to_string(rows_) + "," + std::to_string(cols_) + " " +
                    std::to_string(row) + "," + std::to_string(col) + " " +
                    " Matrix subscript out of bounds");

            return data_[row][col];
        }

        inline
        T operator() (int row, int col) const
        {
            if (row >= rows_ || col >= cols_)
            {
                printf("const Matrix subscript out of bounds");
                throw std::out_of_range(std::to_string(row) + "," + std::to_string(col) + " const Matrix subscript out of bounds");
            }

            return data_[row][col];
        }
};

#endif // MATRIX_H
