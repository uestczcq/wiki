#include <iostream>
#include <stdlib.h>
using namespace std;

struct min_sum_bord_t
{
    int m;
    int n;
    int *row;
    int *col;
    int *choos_row;
    int *data;
};

void init_data(struct min_sum_bord_t *data)
{
    int i, m, n;
    cin >> m >> n;
    data->m = m;
    data->n = n;
    data->row = (int*)malloc(sizeof(int)*m);
    data->col = (int*)malloc(sizeof(int)*n);
    data->choos_row = (int*)malloc(sizeof(int)*n);
    data->data = (int*)malloc(sizeof(int)*m*n);
    for (i = 0; i < m*n; ++i)
    {
        cin >> data->data[i];
    }
    for (i = 0; i < m; ++i)
    {
        data->row[i] = -1;
    }
    for (i = 0; i < n; ++i)
    {
        data->col[i] = -1;
    }
    for (i = 0; i < n; ++i)
    {
        data->choos_row[i] = 0;
    }
}

void free_data(struct min_sum_bord_t *data)
{
    if(data->row != NULL)
        free(data->row);
    if(data->col != NULL)
        free(data->col);
    if(data->choos_row != NULL)
        free(data->choos_row);
    if(data->data != NULL)
        free(data->data);
}

void show_data(struct min_sum_bord_t *data)
{
    int i, j;
    int m, n;
    m = data->m;
    n = data->n;
    cout << "case is:" << data->m << " " << data->n << endl;
    for (i = 0; i < m; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            cout << data->data[i*n + j] <<" ";
        }
        cout << endl;
    }
    for (i = 0; i < m; ++i)
    {
        cout << data->row[i];
    }
    cout << endl;
    for (i = 0; i < n; ++i)
    {
        cout << data->col[i];
    }
    cout << endl;
}

void get_min_row(struct min_sum_bord_t *data)
{
    int i, j, m, n, min;
    m = data->m;
    n = data->n;
    for (i = 0; i < m; ++i)
    {
        for (j = 0, min = 0; j < n; ++j)
        {
            if (data->data[i*n + j] < data->data[i*n + min])
            {
                min = j;
            }
        }
        data->choos_row[min]++;
        data->row[i] = min;
    }

    for (i = 0; i < n; ++i)
    {
        for (j = 0, min = 0; j < m; ++j)
        {
            if (data->data[j*n +i] < data->data[min*n +i])
            {
                min = j;
            }
        }
        data->col[i] = min;
    }
}

int min_sum(struct min_sum_bord_t *data)
{
    int i, j, t, m, n, sum;
    int tmp;
    int min_col;
    int pmin[n];
    m = data->m;
    n = data->n;
    sum = 0;
    for (i = 0; i < m; ++i)
    {
        sum += data->data[data->row[i] + i*n];
    }
    // add col
    for (i = 0; i < n; ++i)
    {
        if(data->choos_row[i] == 0)
        {
            for (t = 0; t < n; ++t)
            {
                pmin[t] = -1;
            }
            for (j = 0; j < n; ++j)
            {
                if (data->choos_row[j] > 1)
                {
                    for(tmp = 0; tmp < m; tmp++)
                        if (data->row[tmp] == j)
                        {
                            if(pmin[j] < 0)
                                pmin[j] = tmp;
                            else if((data->data[tmp*n + i] - data->data[tmp*n + j]) <
                                    (data->data[pmin[j]*n + i] - data->data[pmin[j]*n +j]))
                                pmin[j] = tmp;
                        }
                }
            }
            for (t = 0, tmp = -1; t < n; ++t)
            {
                if (pmin[t] >= 0)
                {
                    if(tmp < 0)
                        tmp = t;
                    else if((data->data[pmin[t]*n + i] - data->data[pmin[t]*n + t]) <
                                    (data->data[pmin[tmp]*n + i] - data->data[pmin[tmp]*n +tmp]))
                        tmp = t;
                }
            }
            sum += data->data[pmin[tmp]*n + i];
            data->choos_row[tmp]--;
            sum -= data->data[pmin[tmp]*n + tmp];
            data->row[pmin[tmp]] = tmp;
        }
    }

    return sum;
}
int main(int argc, char *argv[])
{
    int i, n;
    struct min_sum_bord_t mycase;
    cin >> n;
    if(n < 1)
        return -1;
    int *res = (int *)malloc(sizeof(int)*n);
    for (i = 0; i < n; ++i)
    {
        init_data(&mycase);
        get_min_row(&mycase);
        //show_data(&mycase);
        res[i] = min_sum(&mycase);
        free_data(&mycase);
    }
    for (i = 0; i < n; ++i)
    {
        cout << "Case " << i + 1 <<": "<< res[i] << endl;
    }
    free(res);
    return 0;
}
