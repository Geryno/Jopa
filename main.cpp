#define SCALE_STEP 4

#include <iostream>
#include <vector>
#include <fstream>          // Вывод в .csv

using namespace std;

float global;
const int base_n = 3;       // Размер блока "памяти"
const int newV = base_n * SCALE_STEP;
struct sto
    {
        int D;
        float D_average;
        int C;
        int S;
        float T;
    };

std::vector<std::vector<int>> create2DArray(unsigned height, unsigned width)
{
    return std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
}

std::vector<std::vector<int>> create_base_m()
{
    std::vector<std::vector<int>> base_m;
    return base_m = {\
                { 0, 1, 1 },
                { 1, 0, 1 },
                { 1, 1, 0 }
    };
}

// ===== Создание матриц смежности =====

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

std::vector<std::vector<int>> M_Linear(std::vector<std::vector<int>> work_m){
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

std::vector<std::vector<int>> M_Star(std::vector<std::vector<int>> work_m){
    int star_factor = 1;
    int index = 0;
    int b = newV/base_n-1;

    int i2 = index*base_n;
    int j2 = index*base_n;

    for (int i = 0 ; i < b; i++){

                work_m[i2][(j2+base_n)*star_factor] = 1;
                work_m[(i2+base_n)*star_factor][j2] = 1;

                star_factor++;

    }

    return work_m;
};

std::vector<std::vector<int>> M_Circle(std::vector<std::vector<int>> work_m){
    work_m = M_Linear(work_m);
    int b = newV/base_n;

    if (b > 1){
        work_m[0][(b-1)*base_n] = 1;
        work_m[(b-1)*base_n][0] = 1;
    }

    return work_m;
}

// ===== Просчеты топологических характеристик =====

int dij_algo(std::vector<std::vector<int>> matrix, int q) {   
    int number = 0;
    int MAX_D = 0;
    int num_sum = 0;
    int distance[newV], count, index, i, u;
    bool visited[newV];


        for (i = 0; i < newV; i++) {
            distance[i] = INT_MAX;
            visited[i] = false;
        }

        distance[q] = 0;

        for (count = 0; count < newV - 1; count++) {
            int min = INT_MAX;
            for (i = 0; i < newV; i++)
                if (!visited[i] && distance[i] <= min) {
                    min = distance[i];
                    index = i;
                }

            u = index;
            visited[u] = true;

            for (i = 0; i < newV; i++)
                if (!visited[i] && matrix[u][i] && distance[u] != INT_MAX &&
                    distance[u] + matrix[u][i] < distance[i])
                    distance[i] = distance[u] + matrix[u][i];
        }

        for (i = 0; i < newV; i++)
            if (distance[i] != INT_MAX) {
                if (distance[i] > MAX_D)
                {
                    MAX_D = distance[i];
                }
                number += distance[i];
            }

        global += number;


    return MAX_D;    
}

std::vector<int> calc_CS(std::vector<std::vector<int>> matrix){

    int sum_1 = 0;
    int max_sum = 0;
    //float T = 0;

    for (int i = 0; i < newV; i++) {

        int s_sum = 0;

        for (int j = 0; j < newV; j++) {
            if (matrix[i][j] == 1) {
                sum_1++;
                s_sum++;
            }
        }

        if (max_sum < s_sum) {
            max_sum = s_sum;
        }

    }
    
    std::vector<int> ans = {sum_1/2, max_sum};

    return ans;     // [0] - C; [1] - S
}

vector<sto> calc_all(std::vector<std::vector<int>> m_lin, std::vector<std::vector<int>> m_star, std::vector<std::vector<int>> m_circle){
    sto linear, star, circle;
    int temp;
    std::vector<int> temp2(1);

    // Линейка:
    for (int q = 0; q < newV; q++) {
    temp = dij_algo(m_lin, q);
    }
    temp2 = calc_CS(m_lin);
        linear.D = temp;
        linear.D_average = (global / (newV * (newV - 1)));
        linear.C = temp2[0];
        linear.S = temp2[1];
        linear.T = (2 * linear.D_average) / linear.S;

    // Звезда:
    global = 0;
    for (int q = 0; q < newV; q++) {
        temp = dij_algo(m_star, q);
    }
    temp2 = calc_CS(m_star);
        star.D = temp;
        star.D_average = (global / (newV * (newV - 1)));
        star.C = temp2[0];
        star.S = temp2[1];
        star.T = (2 * star.D_average) / star.S;

    // Круг:
    global = 0;
    for (int q = 0; q < newV; q++) {
        temp = dij_algo(m_circle, q);
    }
    temp2 = calc_CS(m_circle);
        circle.D = temp;
        circle.D_average = (global / (newV * (newV - 1)));
        circle.C = temp2[0];
        circle.S = temp2[1];
        circle.T = (2 * circle.D_average) / circle.S;

    
    vector<sto> ans;
    ans = {linear, star, circle};
    return ans;
}

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
    global = 0.0;
    std::vector<std::vector<int>> work_m = create2DArray(newV, newV);
    std::vector<std::vector<int>> m_lin = create2DArray(newV, newV);
    std::vector<std::vector<int>> m_star = create2DArray(newV, newV);
    std::vector<std::vector<int>> m_circle = create2DArray(newV, newV);
    vector<sto> calc;
    
    work_m = createM(work_m);

    m_lin = M_Linear(work_m);
    m_star = M_Star(work_m);
    m_circle = M_Circle(work_m);

    /*
    m_lin = {
        {0, 1, 1, 0, 0, 0 },
        {1, 0, 1, 0, 0, 0 },
        {1, 1, 0, 1, 0, 0 },
        {0, 0, 1, 0, 1, 1 },
        {0, 0, 0, 1, 0, 1 },
        {0, 0, 0, 1, 1, 0 }
    };
    */



    calc = calc_all(m_lin, m_star, m_circle);


    //cout << endl << "===============" << endl;
    //cout << "BIIIG matrix: " << endl;
    //print(work_m);

    cout  << endl << "===============" << endl;
    cout << "Linear matrix: " << endl;
    print(m_lin);
    cout << endl << "D: " << calc[0].D << ",   D_avg: " << calc[0].D_average << ",   S: " << calc[0].S << ",   C: " << calc[0].C << ",   T: " << calc[0].T;

    cout << endl << endl << "===============" << endl;
    cout << "Star matrix: " << endl;
    print(m_star);
    cout << endl << "D: " << calc[1].D << ",   D_avg: " << calc[1].D_average << ",   S: " << calc[1].S << ",   C: " << calc[1].C << ",   T: " << calc[1].T;

    cout << endl << endl << "===============" << endl;
    cout << "Circle matrix: " << endl;
    print(m_circle);
    cout << endl << "D: " << calc[2].D << ",   D_avg: " << calc[2].D_average << ",   S: " << calc[2].S << ",   C: " << calc[2].C << ",   T: " << calc[2].T << endl << endl;

}
