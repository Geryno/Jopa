#include <iostream>
#include <vector>

using namespace std;

const int base_n = 7;
const int newV = base_n * 2;

std::vector<std::vector<int>> create2DArray(unsigned height, unsigned width)
{
   return std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
}

std::vector<std::vector<int>> create_base_m(unsigned height, unsigned width)
{
   return std::vector<std::vector<int>>(height, std::vector<int>(width, 1));
}

std::vector<std::vector<int>> createM(std::vector<std::vector<int>> work_m){
    std::vector<std::vector<int>> base_m = create_base_m(base_n, base_n);
    //std::vector<std::vector<int>> work_m = create2DArray(newV, newV);

    int index = 0;
    int b = newV/base_n;

    for (int i = 0; i < b; i++){
        for (int j = 0; j < b; j++){
                for (int i2 = index*base_n; i2 <= (((index+1)*base_n)-1); i2++){                // Получает табл. по диагонали
                    int ind_i = 0;      // Для индексации по изначальной таблице
                    int ind_j = 0;      // 
                        for (int j2 = index*base_n; j2 <= (((index+1)*base_n)-1); j2++){        // Получает табл. по диагонали
                            work_m[i2][j2] = base_m[ind_i][ind_j];
                            ind_i++;
                            ind_j++;
                        }
                }
        }

        index++;

    }

    //cout << sizeof(base_m) / sizeof(base_m[0]);
    return work_m;
}

void print(std::vector<std::vector<int>> matrix){
    for (int i = 0; i < newV; i++){
        for (int j = 0; j < newV; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    std::vector<std::vector<int>> work_m = create2DArray(newV, newV);
    
    work_m = createM(work_m);

    print(work_m);
}
