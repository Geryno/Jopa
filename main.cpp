#define SCALE_STEP 3

#include <iostream>
#include <vector>
#include <fstream>          // Вывод в .csv

using namespace std;

const int base_n = 3;       // Размер блока "памяти"
const int newV = base_n * SCALE_STEP;

std::vector<std::vector<int>> create2DArray(unsigned height, unsigned width)
{
    return std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
}

std::vector<std::vector<int>> create_base_m()
{
    std::vector<std::vector<int>> base_m;
    return base_m = {
                { 1, 2, 3 },
                { 4, 5, 6 },
                { 7, 8, 9 }
    };
}

std::vector<std::vector<int>> createM(std::vector<std::vector<int>> work_m){
    std::vector<std::vector<int>> base_m = create_base_m();

    int index = 0;
    int b = newV/base_n;

    for (int i = 0; i < b; i++){
        for (int j = 0; j < b; j++){

                int ind_i = 0;      // Для индексации по изначальной таблице

                for (int i2 = index*base_n; i2 <= (((index+1)*base_n)-1); i2++){                // Получает индекс начала блока "памяти"

                        int ind_j = 0;      // Для индексации по изначальной таблице

                        for (int j2 = index*base_n; j2 <= (((index+1)*base_n)-1); j2++){        // Получает индекс начала блока "памяти"

                            work_m[i2][j2] = base_m[ind_i][ind_j];
                            ind_j++;

                        }

                    ind_i++;
                }
        }

        index++;

    }

    return work_m;
}

// Linear, Star, Circle

std::vector<std::vector<int>> M_linear(std::vector<std::vector<int>> work_m){

    int index = 0;
    int b = newV/base_n;

    for (int i = 0; i < b-1; i++){
        for (int j = 0; j < b-1; j++){

                    int i2 = index*base_n;
                    int j2 = index*base_n;

                            work_m[i2][j2+base_n] = 1;
                            work_m[i2+base_n][j2] = 1;

        }

        index++;

    }

    return work_m;

};

void print(std::vector<std::vector<int>> matrix){
    for (int i = 0; i < newV; i++){
        for (int j = 0; j < newV; j++){
            cout << matrix[i][j] << " ";   // Обычный вывод
        }
        cout << endl;
    }
}

void print_csv(std::vector<std::vector<int>> matrix){

    std::ofstream file;
    file.open("output.csv");

    file << "SCALE_STEP: " << SCALE_STEP << "; Linear (probably)" << endl;

    for (int i = 0; i < newV; i++){
        for (int j = 0; j < newV; j++){
            file << matrix[i][j] << "; ";  
        }
        file << endl;
    }

    file.close();
}

int main(){
    std::vector<std::vector<int>> work_m = create2DArray(newV, newV);
    std::vector<std::vector<int>> m_lin = create2DArray(newV, newV);

    
    work_m = createM(work_m);
    m_lin = M_linear(work_m);

    cout << endl << "===============" << endl;
    cout << "BIIIG matrix: " << endl;
    print(work_m);

    cout << endl << "===============" << endl;
    cout << "Linear matrix: " << endl;
    print(m_lin);
}
